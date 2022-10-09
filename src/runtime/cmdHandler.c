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
 * cmdHandler.c
 *
 *  Created on: 09.10.2022
 *      Author: Christos Zosimidis
 */

/* Crazyradio-HSA includes. */
#include "cmdHandler.h"
#include "debug/console.h"

/* Nordic Semiconductor include. */
#include <nordic_common.h>

/* Standard libraries include. */
#include <strings.h>
#include <stdint.h>
#include <stdbool.h>

typedef void(*CmdFunctionCall)(const char*);

typedef struct cmd_map_t {
	const char* cmdName;
	const char* descirption;
	CmdFunctionCall call;
} CmdMap;

static void help(const char*);
static void clear(const char*);

static const CmdMap cmdMap[] = {
	{"help",     "prints this message",          help    },
	{"clear",    "clears the console",           clear   },
};

void help(const char* args) {
	(void)args; /* disable -Wunuse-parameter */
	DEBUG_PRINT("\r\nCrazyradio debug command menu\r\n");
	DEBUG_PRINT("Nr: Command     Description                           \r\n");
	DEBUG_PRINT("------------------------------------------------------\r\n");
	for (unsigned int i = 0; i < ARRAY_SIZE(cmdMap); i++) {
		DEBUG_PRINT("%-2d: %-9s - %s\r\n", i, cmdMap[i].cmdName, cmdMap[i].descirption);
	}
}

void clear(const char* args) {
	(void)args; /* disable -Wunuse-parameter */
	DEBUG_CLEAR();
}

static bool checkInputCommand(const char* args, const char* cmd) {
	for(unsigned int i = 0; cmd[i] != '\0'; i++) {
		if(cmd[i] != args[i]) {
			return false;
		}
	}
	return true;
}

static const char* getCmdArgs(const char* args) {
	while(args[0] != '\0' && args[0] != ' ') {
		args++;
	}
	return args++;
}

void handleCommand(const char* args) {
	for(unsigned int i = 0; i < ARRAY_SIZE(cmdMap); i++) {
		if(checkInputCommand(args, cmdMap[i].cmdName)) {
			cmdMap[i].call(getCmdArgs(args));
			return;
		}
	}
	DEBUG_ERROR("Unknown command: %s\r\n", args);
}
