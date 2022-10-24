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
 * button.h
 *
 *  Created on: 09.10.2022
 *      Author: Christos Zosimidis
 */

#ifndef SRC_BOARD_BUTTON_H_
#define SRC_BOARD_BUTTON_H_

/* Nordic Semiconductor include. */
#include <boards.h>

/* Standard libraries includes. */
#include <stdint.h>
#include <stdbool.h>

enum BUTTON_IDX {
	BUTTON1 = BUTTON_1,
	BUTTON2 = BUTTON_2,
	BUTTON3 = BUTTON_3,
	BUTTON4 = BUTTON_4
};

void initButtons();
void initButton(uint8_t button);

bool isButtonActive(uint8_t button);
bool isButtonInActive(uint8_t button);

#endif /* SRC_BOARD_BUTTON_H_ */
