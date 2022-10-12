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
 * runtime.c
 *
 *  Created on: 09.10.2022
 *      Author: Christos Zosimidis
 */

/* Crazyradio-HSA includes. */
#include "runtime.h"
#include "cmdHandler.h"
#include "syslink.h"
#include "arch/sleep.h"
#include "board/led.h"
#include "debug/console.h"

/* Standard libraries include. */
#include <stdbool.h>

static void printRuntime() {
	DEBUG_CLEAR();
	DEBUG_PRINT("######################################################\r\n");
	DEBUG_PRINT("# Crazyradio-HSA Runtime                         #####\r\n");
	DEBUG_PRINT("# University of Applied sciences Augsburg        #####\r\n");
	DEBUG_PRINT("# Professor Dr.-Ing Klaus Kefferpuetz            #####\r\n");
	DEBUG_PRINT("# Developers                                     #####\r\n");
	DEBUG_PRINT("# **********                                     #####\r\n");
	DEBUG_PRINT("# Christos Zosimidis                             #####\r\n");
	DEBUG_PRINT("# Thomas Izycki                                  #####\r\n");
	DEBUG_PRINT("######################################################\r\n\n");
	handleCommand("help");
}

void startRuntime() {
	printRuntime();
	ledON(RUNTIME_LED);

	static SyslinkPacket syslinkRxPacket;

	while(true) {

		/* Read the Syslink-packet. */
		if(syslinkReceive(&syslinkRxPacket)) {
			// TODO: Handle the Syslink-packet from the cflib
		}

		/* Read a command from the debug console. */
		const char* consoleInput = getDebugConsoleInput();
		if(consoleInput != NULL) {
			handleCommand(consoleInput);
		}

		sleepms(500); // TODO: Remove this line
	}
}
