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
#ifndef __PACKET_H__
#define __PACKET_H__

/* Standard libraries includes. */
#include <stdbool.h>
#include <stdint.h>

#define SYSLINK_STARTUP_DELAY_TIME_MS 1000
#define SYSLINK_SEND_PERIOD_MS 10

#define SYSLINK_MTU 64

typedef struct syslinkPacket_s {
	uint8_t type;
	uint8_t length;
	uint8_t data[SYSLINK_MTU];
} SyslinkPacket;

bool syslinkReceive(SyslinkPacket *packet);

bool syslinkSend(SyslinkPacket *packet);
void syslinkReset();


// Defined packet types
#define SYSLINK_CRTP_PACKET          0x00
#define SYSLINK_PING                 0x01
#define SYSLINK_BOARD_RADIO_INFO     0x02
#define SYSLINK_CRAZYFLIE_RADIO_INFO 0x03
#define SYSLINK_START_COMMUNICATION  0x04

#endif
