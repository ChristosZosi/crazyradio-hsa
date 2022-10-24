/*
 * MIT License
 *
 * Copyright (c) 2022 Christos Zosimidis
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *
 * crazyradio_uart.c
 *
 *  Created on: 12.10.2022
 *      Author: Christos Zosimidis
 */

/* Crazyradio-HSA includes. */
#include "crazyradio_uart.h"

/* Nordic Semiconductors includes. */
#include <nrf.h>
#include <boards.h>

#define CRAZYRADIO_UART_BAUDRATE                   UART_BAUDRATE_BAUDRATE_Baud115200
#define CRAZYRADIO_UART_INTERRUPT_PRIORITY         2
#define CRAZYRADIO_UART_RX_QUEUE_SIZE              512

static volatile uint8_t rxQueue[CRAZYRADIO_UART_RX_QUEUE_SIZE];
static volatile uint8_t rxQueueWritePos = 0;
static volatile uint8_t rxQueueReadPos = 0;

static uint8_t dummyByte;

static void crazyradioUartInterruptHandler();

void UART0_IRQHandler() {
	crazyradioUartInterruptHandler();
}

void initCrazyradioUart() {
	NRF_GPIO->PIN_CNF[8] &= ~GPIO_PIN_CNF_PULL_Msk;
	NRF_GPIO->PIN_CNF[8] |= (GPIO_PIN_CNF_PULL_Pulldown << GPIO_PIN_CNF_PULL_Pos);

	NRF_GPIO->PIN_CNF[TX_PIN_NUMBER] = (NRF_GPIO->PIN_CNF[TX_PIN_NUMBER] & (~GPIO_PIN_CNF_DRIVE_Msk)) | (GPIO_PIN_CNF_DRIVE_S0S1 << GPIO_PIN_CNF_DRIVE_Pos);

	NRF_GPIO->DIRSET = 1 << TX_PIN_NUMBER;
	NRF_GPIO->OUTSET = 1 << TX_PIN_NUMBER;
	NRF_UART0->PSELTXD = TX_PIN_NUMBER;

	NRF_GPIO->DIRCLR = 1 << RX_PIN_NUMBER;
	NRF_UART0->PSELRXD = RX_PIN_NUMBER;

	NRF_GPIO->DIRSET = 1 << RTS_PIN_NUMBER;
	NRF_GPIO->OUTSET = 1 << RTS_PIN_NUMBER;
	NRF_UART0->PSELRTS = RTS_PIN_NUMBER;

	NRF_UART0->CONFIG = UART_CONFIG_HWFC_Msk;

	NRF_UART0->BAUDRATE = CRAZYRADIO_UART_BAUDRATE;

	NRF_UART0->ENABLE = UART_ENABLE_ENABLE_Enabled;

	NRF_UART0->TASKS_STARTTX = 1;

	// Enable interrupt on receive
	NVIC_SetPriority(UART0_IRQn, CRAZYRADIO_UART_INTERRUPT_PRIORITY);
	NVIC_EnableIRQ(UART0_IRQn);
	NRF_UART0->INTENSET = UART_INTENSET_RXDRDY_Msk;

	NRF_UART0->TASKS_STARTRX = 1;
}

void crazyradioUartInterruptHandler() {
	NRF_UART0->EVENTS_RXDRDY = 0;

	if (((rxQueueWritePos + 1) % CRAZYRADIO_UART_RX_QUEUE_SIZE) == rxQueueReadPos) {
		dummyByte = NRF_UART0->RXD;
		return;
	}

	rxQueue[rxQueueWritePos] = NRF_UART0->RXD;
	rxQueueWritePos = (rxQueueWritePos + 1) % CRAZYRADIO_UART_RX_QUEUE_SIZE;
}

void flushCrazyradioUart() {
	while(isCrazyradioUartRx()) {
		rxCrazyradioUart();
	}
}

void txCrazyradioUart(uint8_t byte) {
	NRF_UART0->TXD = byte;
	while(!NRF_UART0->EVENTS_TXDRDY);
	NRF_UART0->EVENTS_TXDRDY = 0;
}

bool isCrazyradioUartRx() {
	return rxQueueWritePos != rxQueueReadPos;
}
uint8_t rxCrazyradioUart() {
	uint8_t byte = rxQueue[rxQueueReadPos];
	rxQueueReadPos = (rxQueueReadPos + 1) % CRAZYRADIO_UART_RX_QUEUE_SIZE;
	return byte;
}
