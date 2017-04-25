/*
 * application.c
 *
 *  Created on: Apr 24, 2017
 *      Author: chinm_000
 */

#include "../App/application.h"

#include <stdio.h>
#include <stdarg.h>
#include "usart.h"
#include "stm32f4xx_hal_uart.h"

static uint16_t BUF_LEN = 200;

void App_Init() {
App_Printf("Starting Board, Hello %s\r\n", "<your name here>");
}

void App_Printf(char const *format, ...) {
va_list arg;
va_start(arg, format);
char buf[BUF_LEN];
uint32_t len = vsnprintf(buf, sizeof(buf), format, arg);
va_end(arg);
len = LESS(len, sizeof(buf) - 1);
HAL_UART_Transmit(&huart2, (uint8_t *) buf, len, 0xFFFF);
}
