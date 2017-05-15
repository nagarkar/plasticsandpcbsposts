/*
 * application.c
 *
 *  Created on: Apr 24, 2017
 *      Author: chinm_000
 */

#include "application.h"

#include <stdio.h>
#include <stdarg.h>
#include "stm32f4xx_hal.h"
#include "gpio.h"
#include "stm32f4xx_hal_gpio.h"
#include "qpcpp.h"
#include "UserLed.h"
#include "macros.h"

static uint16_t BUF_LEN = 200;

using namespace QP;
using namespace AOs;

enum {
    EVT_SIZE_SMALL = 32,
    EVT_SIZE_MEDIUM = 64,
    EVT_SIZE_LARGE = 256,
    EVT_COUNT_SMALL = 128,
    EVT_COUNT_MEDIUM = 16,
    EVT_COUNT_LARGE = 4
};

enum {
    EVT_QUEUE_COUNT = 16,
    DEFER_QUEUE_COUNT = 4
};

enum
{
    PRIO_LED     = 5
};

enum {
	MAX_SUBSCRIBER_COUNT = 10
};

uint32_t evtPoolSmall[ROUND_UP_DIV_4(EVT_SIZE_SMALL * EVT_COUNT_SMALL)];
uint32_t evtPoolMedium[ROUND_UP_DIV_4(EVT_SIZE_MEDIUM * EVT_COUNT_MEDIUM)];
uint32_t evtPoolLarge[ROUND_UP_DIV_4(EVT_SIZE_LARGE * EVT_COUNT_LARGE)];
QP::QSubscrList subscrSto[MAX_SUBSCRIBER_COUNT];

static UserLed led;
static QEvt const *ledEventQueueStore[EVT_QUEUE_COUNT];

void App_Init() {
	Application::Init();
}

void App_InitComplete() {
	Application::InitComplete();
}

void App_Printf(char const *format, ...) {
	va_list arg;
	va_start(arg, format);
	char buf[BUF_LEN];
	uint32_t len = vsnprintf(buf, COUNTOF(buf), format, arg);
	va_end(arg);
	len = LESS(len, COUNTOF(buf) - 1);
	//HAL_UART_Transmit(&huart2, (uint8_t *) buf, len, 0xFFFF);
}

void Application::Init() {
	QF::init();
	QF::poolInit(evtPoolSmall, sizeof(evtPoolSmall), EVT_SIZE_SMALL);
	QF::poolInit(evtPoolMedium, sizeof(evtPoolMedium), EVT_SIZE_MEDIUM);
	QF::poolInit(evtPoolLarge, sizeof(evtPoolLarge), EVT_SIZE_LARGE);
	QP::QF::psInit(subscrSto, Q_DIM(subscrSto)); // init publish-subscribe

	led.start(PRIO_LED, ledEventQueueStore, COUNTOF(ledEventQueueStore), NULL, 0);
	QF::run();
}

void Application::InitComplete() {
	App_Printf("Starting Board, Hello %s\r\n", "<your name here>");
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	App_Printf("In Interrupt\r\n");
}

extern "C" void assert_failed() {

}
