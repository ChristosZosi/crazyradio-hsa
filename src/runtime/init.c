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
 * init.c
 *
 *  Created on: 09.10.2022
 *      Author: Christos Zosimidis
 */

/* Crazyradio-HSA includes. */
#include "init.h"
#include "board/led.h"
#include "board/button.h"

/* Nordic Semiconductor include. */
#include <nrf.h>

static void initClock() {

	NRF_CLOCK->EVENTS_HFCLKSTARTED = 0UL;
	NRF_CLOCK->TASKS_HFCLKSTART    = 1UL;

	/* Wait for the external oscillator to start up */
	while (NRF_CLOCK->EVENTS_HFCLKSTARTED == 0)
	{
		// Do nothing.
	}
}

bool initPlatform() {
	/* initialize system clock */
	initClock();

	/* Initialize all buttons and leds */
	initButtons();
	initLeds();

	return true;
}
