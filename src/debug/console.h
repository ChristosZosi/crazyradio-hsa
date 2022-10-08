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
 * console.h
 *
 *  Created on: 09.10.2022
 *      Author: Christos Zosimidis
 */

#ifndef SRC_DEBUG_CONSOLE_H_
#define SRC_DEBUG_CONSOLE_H_

/* Crazyradio-HSA includes. */
#include "arch/sleep.h"

/* SEGGER includes. */
#include "SEGGER_RTT.h"

/* Standard libraries includes. */
#include <stdio.h>
#include <stdint.h>

#define DEBUG_PRINT(...) \
	do { \
		char str[64]; \
		sprintf(str, __VA_ARGS__); \
		SEGGER_RTT_WriteString(0, RTT_CTRL_TEXT_BRIGHT_GREEN); \
		SEGGER_RTT_WriteString(0, str); \
		sleepms(1); \
	} while(0)

#define DEBUG_ERROR(...) \
	do { \
		char str[64]; \
		sprintf(str, __VA_ARGS__); \
		SEGGER_RTT_WriteString(0, RTT_CTRL_TEXT_BRIGHT_RED); \
		SEGGER_RTT_WriteString(0, str); \
		sleepms(1); \
	} while(0)

#define DEBUG_WARN(...) \
	do { \
		char str[64]; \
		sprintf(str, __VA_ARGS__); \
		SEGGER_RTT_WriteString(0, RTT_CTRL_TEXT_BRIGHT_MAGENTA); \
		SEGGER_RTT_WriteString(0, str); \
		sleepms(1); \
	} while(0)

#define DEBUG_CLEAR() \
	do { \
		SEGGER_RTT_WriteString(0, RTT_CTRL_CLEAR); \
		sleepms(1); \
	} while(0)

const char* getDebugConsoleInput();

#endif /* SRC_DEBUG_CONSOLE_H_ */
