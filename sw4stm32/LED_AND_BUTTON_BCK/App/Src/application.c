/*
 * application.c
 *
 *  Created on: Apr 24, 2017
 *      Author: chinm_000
 */

#include "application.h"
#include "bsp.h"
#include <stdio.h>
#include <stdarg.h>

#include "../../SM/Inc/qpsp.h"

void App_Init() {
	BSP_Printf("Starting Board, Hello %s\r\n");
	QPSP_Init();
}
