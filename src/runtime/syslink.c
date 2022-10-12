/**
 *    ||          ____  _ __
 * +------+      / __ )(_) /_______________ _____  ___
 * | 0xBC |     / __  / / __/ ___/ ___/ __ `/_  / / _ \
 * +------+    / /_/ / / /_/ /__/ /  / /_/ / / /_/  __/
 *  ||  ||    /_____/_/\__/\___/_/   \__,_/ /___/\___/
 *
 * Crazyflie 2.0 NRF Firmware
 * Copyright (c) 2014, Bitcraze AB, All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3.0 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.
 */

/* Standard libraries includes. */
#include <stdbool.h>
#include <stdint.h>

/* Crazyradio-HSA includes. */
#include "arch/crazyradio_uart.h"
#include "syslink.h"

/* Frame format:
 * +----+-----+------+-----+=============+-----+-----+
 * |  START   | TYPE | LEN | DATA        |   CKSUM   |
 * +----+-----+------+-----+=============+-----+-----+
 *
 * - Start is 2 bytes constant, defined bellow
 * - Length and type are uint8_t
 * - Length define the data length
 * - CKSUM is 2 bytes Fletcher 8 bit checksum. See rfc1146.
 *   Checksum is calculated with TYPE, LEN and DATA
 */


#define START "\xbc\xcf"
#define START_BYTE1 0xBC
#define START_BYTE2 0xCF

static enum {state_first_start, state_second_start, state_length, state_type, state_data, state_cksum1, state_cksum2, state_done} state = state_first_start;

void syslinkReset() {
	state = state_first_start;
}

bool syslinkReceive(SyslinkPacket *packet)
{
	static int step=0;
	static int length=0;
	static uint8_t cksum_a=0, cksum_b=0;
	uint8_t byte;

	packet->length = 0;

	if (state == state_done)
	{
		state = state_first_start;
		step = 0;
	}

	while (isCrazyradioUartRx() && (state != state_done))
	{
		byte = rxCrazyradioUart();

		switch(state)
		{
		case state_first_start:
			state = (byte == START_BYTE1) ? state_second_start : state_first_start;
			break;
		case state_second_start:
			state = (byte == START_BYTE2) ? state_type : state_first_start;
			break;
		case state_type:
			packet->type = byte;
			cksum_a = byte;
			cksum_b = cksum_a;
			state = state_length;
			break;
		case state_length:
			length = byte;
			cksum_a += byte;
			cksum_b += cksum_a;
			step = 0;
			if (length > 0 && length <= SYSLINK_MTU)
				state = state_data;
			else if (length > SYSLINK_MTU)
				state = state_first_start;
			else
				state = state_cksum1;
			break;
		case state_data:
			if (step < SYSLINK_MTU)
			{
				packet->data[step] = byte;
				cksum_a += byte;
				cksum_b += cksum_a;
			}
			step++;
			if(step >= length) {
				state = state_cksum1;
			}
			break;
		case state_cksum1:
			if (byte == cksum_a)
			{
				state = state_cksum2;
			}
			else
			{  // Wrong checksum
				state = state_first_start;
			}
			break;
		case state_cksum2:
			if (byte == cksum_b)
			{
				packet->length = length;
				state = state_done;
			}
			else
			{  // Wrong checksum
				state = state_first_start;
				step = 0;
			}
			break;
		case state_done:
			break;
		}
	}

	return (state == state_done);
}

bool syslinkSend(SyslinkPacket *packet)
{
	uint8_t cksum_a=0;
	uint8_t cksum_b=0;
	int i;

	txCrazyradioUart(START_BYTE1);
	txCrazyradioUart(START_BYTE2);

	txCrazyradioUart(packet->type);
	cksum_a += packet->type;
	cksum_b += cksum_a;

	txCrazyradioUart(packet->length);
	cksum_a += packet->length;
	cksum_b += cksum_a;

	for (i=0; i < packet->length; i++)
	{
		txCrazyradioUart(packet->data[i]);
		cksum_a += packet->data[i];
		cksum_b += cksum_a;
	}

	txCrazyradioUart(cksum_a);
	txCrazyradioUart(cksum_b);

	return true;
}
