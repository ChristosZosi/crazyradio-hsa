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
 * console.c
 *
 *  Created on: 09.10.2022
 *      Author: Christos Zosimidis
 */

/* Crazyradio-HSA includes */
#include "console.h"

/* Standard libraries includes. */
#include <string.h>

#define MAX_RTT_CONSOLE_INPUT_BUFFER_SIZE 16
static char rttInputBuffer[MAX_RTT_CONSOLE_INPUT_BUFFER_SIZE];

const char* getDebugConsoleInput() {
	memset(rttInputBuffer, 0, MAX_RTT_CONSOLE_INPUT_BUFFER_SIZE);

	const int received_bytes = SEGGER_RTT_Read(0, rttInputBuffer, MAX_RTT_CONSOLE_INPUT_BUFFER_SIZE);
	if(received_bytes == 0) {
		return NULL;
	}

	for(unsigned int i = 0; i < MAX_RTT_CONSOLE_INPUT_BUFFER_SIZE; i++) {
		if(rttInputBuffer[i] == '\n') {
			rttInputBuffer[i] = 0;
			break;
		}
	}

	return rttInputBuffer;
}
