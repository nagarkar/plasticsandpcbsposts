/*
 * qpsp.cpp
 *
 *  Created on: May 2, 2017
 *      Author: chinm_000
 */

#include "../Inc/qpsp.h"

#include "qpcpp.h"
#include "macros.h"
#include "bsp.h"
#include "UserLed.h"


enum
{
    PRIO_LED     = 5
};

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

enum {
	MAX_SUBSCRIBER_COUNT = 10
};

uint32_t evtPoolSmall[ROUND_UP_DIV_4(EVT_SIZE_SMALL * EVT_COUNT_SMALL)];
uint32_t evtPoolMedium[ROUND_UP_DIV_4(EVT_SIZE_MEDIUM * EVT_COUNT_MEDIUM)];
uint32_t evtPoolLarge[ROUND_UP_DIV_4(EVT_SIZE_LARGE * EVT_COUNT_LARGE)];
QP::QSubscrList subscrSto[MAX_SUBSCRIBER_COUNT];

static UserLed led;
static QEvt const *ledEventQueueStore[EVT_QUEUE_COUNT];

void QPSP_Init() {
	QF::init();
	QF::poolInit(evtPoolSmall, sizeof(evtPoolSmall), EVT_SIZE_SMALL);
	QF::poolInit(evtPoolMedium, sizeof(evtPoolMedium), EVT_SIZE_MEDIUM);
	QF::poolInit(evtPoolLarge, sizeof(evtPoolLarge), EVT_SIZE_LARGE);
	QP::QF::psInit(subscrSto, Q_DIM(subscrSto)); // init publish-subscribe

	BSP_Printf("Starting LED HSM\r\n");
	led.start(PRIO_LED, ledEventQueueStore, COUNTOF(ledEventQueueStore), NULL, 0);

	BSP_Printf("Running QF\r\n");
	QF::run();
}
// namespace QP **************************************************************
namespace QP {

// QF callbacks ==============================================================
void QF::onStartup(void) {
}
//............................................................................
void QF::onCleanup(void) {
}
//............................................................................
void QXK::onIdle(void) {
    QF_INT_DISABLE();
    QF_INT_ENABLE();


#if defined NDEBUG
    // Put the CPU and peripherals to the low-power mode.
    // you might need to customize the clock management for your application,
    // see the datasheet for your particular Cortex-M3 MCU.
    //
    // !!!CAUTION!!!
    // The WFI instruction stops the CPU clock, which unfortunately disables
    // the JTAG port, so the ST-Link debugger can no longer connect to the
    // board. For that reason, the call to __WFI() has to be used with CAUTION.
    //
    // NOTE: If you find your board "frozen" like this, strap BOOT0 to VDD and
    // reset the board, then connect with ST-Link Utilities and erase the part.
    // The trick with BOOT(0) is it gets the part to run the System Loader
    // instead of your broken code. When done disconnect BOOT0, and start over.
    //
    //__WFI();   Wait-For-Interrupt
#endif
}

//............................................................................

extern "C" void Q_onAssert(char const * const module, int loc) {
    //
    // NOTE: add here your application-specific error handling
    //
    (void)module;
    (void)loc;

    // Gallium - TBD
    char buf[200];
    BSP_Delay(100);
    QF_INT_DISABLE();
    snprintf(buf, sizeof(buf), "**** ASSERT: %s %d ****\n\r", module, loc);
    BSP_Printf(buf);
    for (;;) {
    }
    //NVIC_SystemReset();
}

} // namespace QP
