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
 * led.c
 *
 *  Created on: 09.10.2022
 *      Author: Christos Zosimidis
 */


/* Crazyradio-HSA includes. */
#include "led.h"

/* Nordic Semiconductor include. */
#include <nrf.h>

void initLeds() {
	bsp_board_init(BSP_INIT_LEDS);
}

void initLed(uint8_t led) {
	nrf_gpio_cfg_output(led);
	ledOFF(led);
}

void ledON(uint8_t led) {
	nrf_gpio_pin_write(led, LEDS_ACTIVE_STATE ? 1 : 0);
}

void ledOFF(uint8_t led) {
	nrf_gpio_pin_write(led, LEDS_ACTIVE_STATE ? 0 : 1);
}

void ledToggle(uint8_t led) {
	nrf_gpio_pin_toggle(led);
}

bool isLedON(uint8_t led) {
	return nrf_gpio_pin_read(led) == LEDS_ACTIVE_STATE;
}

bool isLedOFF(uint8_t led) {
	return !isLedON(led);
}
