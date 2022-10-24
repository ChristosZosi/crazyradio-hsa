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
 * button.c
 *
 *  Created on: 09.10.2022
 *      Author: Christos Zosimidis
 */


/* Crazyradio-HSA includes. */
#include "button.h"

/* Nordic Semiconductor include. */
#include <nrf.h>

#define ENABLE_BUTTON BUTTON_PULL

void initButtons() {
	bsp_board_init(BSP_INIT_BUTTONS);
}

void initButton(uint8_t button) {
	nrf_gpio_cfg_input(button, ENABLE_BUTTON);
}

bool isButtonActive(uint8_t button) {
	if(nrf_gpio_pin_read(button) == 0) {
		/* Wait until button has been released. */
		while(nrf_gpio_pin_read(button) == 0);
		return true;
	}
	return false;
}

bool isButtonInActive(uint8_t button) {
	return !isButtonActive(button);
}
