///***************************************************************************
// Product: DPP example, NXP mbed-LPC1768 board, coopearative QV kernel
// Last updated for version 5.8.0
// Last updated on  2016-11-30
//
//                    Q u a n t u m     L e a P s
//                    ---------------------------
//                    innovating embedded systems
//
// Copyright (C) Quantum Leaps, LLC. All rights reserved.
//
// This program is open source software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Alternatively, this program may be distributed and modified under the
// terms of Quantum Leaps commercial licenses, which expressly supersede
// the GNU General Public License and are specifically designed for
// licensees interested in retaining the proprietary status of their code.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
//
// Contact information:
// http://www.state-machine.com
// mailto:info@state-machine.com
//****************************************************************************
#include "qpcpp.h"
#include "dpp.h"
#include "bsp.h"

#include "LPC17xx.h"  // CMSIS-compliant header file for the MCU used
// add other drivers if necessary...

// namespace DPP *************************************************************
namespace DPP {

Q_DEFINE_THIS_FILE

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!! CAUTION !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Assign a priority to EVERY ISR explicitly by calling NVIC_SetPriority().
// DO NOT LEAVE THE ISR PRIORITIES AT THE DEFAULT VALUE!
//
enum KernelUnawareISRs { // see NOTE00
    // ...
    MAX_KERNEL_UNAWARE_CMSIS_PRI  // keep always last
};
// "kernel-unaware" interrupts can't overlap "kernel-aware" interrupts
Q_ASSERT_COMPILE(MAX_KERNEL_UNAWARE_CMSIS_PRI <= QF_AWARE_ISR_CMSIS_PRI);

enum KernelAwareISRs {
    EINT0_PRIO = QF_AWARE_ISR_CMSIS_PRI, // see NOTE00
    SYSTICK_PRIO,
    // ...
    MAX_KERNEL_AWARE_CMSIS_PRI // keep always last
};
// "kernel-aware" interrupts should not overlap the PendSV priority
Q_ASSERT_COMPILE(MAX_KERNEL_AWARE_CMSIS_PRI <= (0xFF >>(8-__NVIC_PRIO_BITS)));

// Local-scope objects -------------------------------------------------------
// LEDs available on the board
#define LED_1    (1U << 18)  // P1.18
#define LED_2    (1U << 20)  // P1.20
#define LED_3    (1U << 21)  // P1.21
#define LED_4    (1U << 23)  // P1.23

// Push-Button wired externally to DIP8 (P0.6)
#define BTN_EXT  (1U << 6)    // P0.6

static unsigned  l_rnd;  // random seed

#ifdef Q_SPY

    QP::QSTimeCtr QS_tickTime_;
    QP::QSTimeCtr QS_tickPeriod_;

    // event-source identifiers used for tracing
    static uint8_t const l_SysTick_Handler  = 0U;
    static uint8_t const l_EINT0_IRQHandler = 0U;

    #define UART_BAUD_RATE      115200U
    #define UART_FR_TXFE        0x80U
    #define UART_TXFIFO_DEPTH   16U

    enum AppRecords { // application-specific trace records
        PHILO_STAT = QP::QS_USER
    };

#endif

// ISRs used in this project =================================================
extern "C" {

//............................................................................
void SysTick_Handler(void); // prototype
void SysTick_Handler(void) {
    // state of the button debouncing, see below
    static struct ButtonsDebouncing {
        uint32_t depressed;
        uint32_t previous;
    } buttons = { ~0U, ~0U };
    uint32_t current;
    uint32_t tmp;

#ifdef Q_SPY
    {
        tmp = SysTick->CTRL; // clear SysTick_CTRL_COUNTFLAG
        QS_tickTime_ += QS_tickPeriod_; // account for the clock rollover
    }
#endif

    QP::QF::TICK_X(0U, &l_SysTick_Handler); // process time events for rate 0

    // Perform the debouncing of buttons. The algorithm for debouncing
    // adapted from the book "Embedded Systems Dictionary" by Jack Ganssle
    // and Michael Barr, page 71.
    //
    current = ~LPC_GPIO0->FIOPIN; // read P0 with the state of the Buttons
    tmp = buttons.depressed; // save the debounced depressed buttons
    buttons.depressed |= (buttons.previous & current); // set depressed
    buttons.depressed &= (buttons.previous | current); // clear released
    buttons.previous   = current; // update the history
    tmp ^= buttons.depressed;     // changed debounced depressed
    if ((tmp & BTN_EXT) != 0U) {  // debounced BTN_EXT state changed?
        if ((buttons.depressed & BTN_EXT) != 0U) { // is BTN_EXT depressed?
            static QP::QEvt const pauseEvt = { DPP::PAUSE_SIG, 0U, 0U};
            QP::QF::PUBLISH(&pauseEvt, &l_SysTick_Handler);
        }
        else {            // the button is released
            static QP::QEvt const serveEvt = { DPP::SERVE_SIG, 0U, 0U};
            QP::QF::PUBLISH(&serveEvt, &l_SysTick_Handler);
        }
    }
}
//............................................................................
void EINT0_IRQHandler(void); // prototype
void EINT0_IRQHandler(void) {
    // for testing..
    DPP::AO_Table->POST(Q_NEW(QP::QEvt, DPP::MAX_PUB_SIG),
                        &l_EINT0_IRQHandler);
}

} // extern "C"

// BSP functions =============================================================
void BSP::init(void) {
    // NOTE: SystemInit() already called from the startup code
    //  but SystemCoreClock needs to be updated
    //
    SystemCoreClockUpdate();

    // turn the GPIO clock on
    LPC_SC->PCONP |= (1U << 15);

    // setup the GPIO pin functions for the LEDs...
    LPC_PINCON->PINSEL3 &= ~(3U <<  4); // LED_1: function P1.18 to GPIO
    LPC_PINCON->PINSEL3 &= ~(3U <<  8); // LED_2: function P1.20 to GPIO
    LPC_PINCON->PINSEL3 &= ~(3U << 10); // LED_3: function P1.21 to GPIO
    LPC_PINCON->PINSEL3 &= ~(3U << 14); // LED_4: function P1.23 to GPIO

    // Set GPIO-P1 LED pins to output
    LPC_GPIO1->FIODIR |= (LED_1 | LED_2 | LED_3 | LED_4);


    // setup the GPIO pin function for the Button...
    LPC_PINCON->PINSEL0 &= ~(3U << 12); // function P0.6 to GPIO, pull-up

    // Set GPIO-P0 Button pin as input
    LPC_GPIO0->FIODIR &= ~BTN_EXT;

    BSP::randomSeed(1234U);

    if (QS_INIT((void *)0) == 0U) { // initialize the QS software tracing
        Q_ERROR();
    }
    QS_OBJ_DICTIONARY(&l_SysTick_Handler);
    QS_OBJ_DICTIONARY(&l_EINT0_IRQHandler);
    QS_USR_DICTIONARY(PHILO_STAT);
}
//............................................................................
void BSP::displayPhilStat(uint8_t n, char const *stat) {
    if (stat[0] == 'h') {
        LPC_GPIO1->FIOSET = LED_1;  // turn LED on
    }
    else {
        LPC_GPIO1->FIOCLR = LED_1;  // turn LED off
    }
    if (stat[0] == 'e') {
        LPC_GPIO1->FIOSET = LED_2;  // turn LED on
    }
    else {
        LPC_GPIO1->FIOCLR = LED_2;  // turn LED off
    }

    QS_BEGIN(PHILO_STAT, AO_Philo[n]) // application-specific record begin
        QS_U8(1, n);  // Philosopher number
        QS_STR(stat); // Philosopher status
    QS_END()
}
//............................................................................
void BSP::displayPaused(uint8_t paused) {
    if (paused != 0U) {
        LPC_GPIO1->FIOSET = LED_3;  // turn LED on
    }
    else {
        LPC_GPIO1->FIOCLR = LED_3;  // turn LED off
    }
}
//............................................................................
uint32_t BSP::random(void) { // a very cheap pseudo-random-number generator
    // "Super-Duper" Linear Congruential Generator (LCG)
    // LCG(2^32, 3*7*11*13*23, 0, seed)
    //
    l_rnd = l_rnd * (3U*7U*11U*13U*23U);

    return l_rnd >> 8;
}
//............................................................................
void BSP::randomSeed(uint32_t seed) {
    l_rnd = seed;
}
//............................................................................
void BSP::terminate(int16_t result) {
    (void)result;
}

} // namespace DPP


// namespace QP **************************************************************
namespace QP {

// QF callbacks ==============================================================
void QF::onStartup(void) {
    // set up the SysTick timer to fire at BSP::TICKS_PER_SEC rate
    SysTick_Config(SystemCoreClock / DPP::BSP::TICKS_PER_SEC);

    // assing all priority bits for preemption-prio. and none to sub-prio.
    NVIC_SetPriorityGrouping(0U);

    // set priorities of ALL ISRs used in the system, see NOTE00
    //
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!! CAUTION !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // Assign a priority to EVERY ISR explicitly by calling NVIC_SetPriority().
    // DO NOT LEAVE THE ISR PRIORITIES AT THE DEFAULT VALUE!
    //
    NVIC_SetPriority(SysTick_IRQn,   DPP::SYSTICK_PRIO);
    NVIC_SetPriority(EINT0_IRQn,     DPP::EINT0_PRIO);
    // ...

    // enable IRQs...
    NVIC_EnableIRQ(EINT0_IRQn);
}
//............................................................................
void QF::onCleanup(void) {
}
//............................................................................
void QV::onIdle(void) { // called with interrupts disabled, see NOTE01
    // toggle the User LED on and then off, see NOTE01
    LPC_GPIO1->FIOSET = LED_4;  // turn LED on
    __NOP();   // a couple of NOPs to actually see the LED glow
    __NOP();
    __NOP();
    __NOP();
    LPC_GPIO1->FIOCLR = LED_4;  // turn LED off

#ifdef Q_SPY
    QF_INT_ENABLE();
    if ((LPC_UART0->LSR & 0x20U) != 0U) {  // TX Holding Register empty?
        uint16_t fifo = UART_TXFIFO_DEPTH; // max bytes we can accept
        uint8_t const *block;

        QF_INT_DISABLE();
        block = QS::getBlock(&fifo); // try to get next block to transmit
        QF_INT_ENABLE();

        while (fifo-- != 0) { // any bytes in the block?
            LPC_UART0->THR = *block++; // put into the FIFO
        }
    }
#elif defined NDEBUG
    // Put the CPU and peripherals to the low-power mode.
    // you might need to customize the clock management for your application,
    // see the datasheet for your particular Cortex-M MCU.
    //
    QV_CPU_SLEEP();  // atomically go to sleep and enable interrupts
#else
    QF_INT_ENABLE(); // just enable interrupts
#endif
}

//............................................................................
extern "C" void Q_onAssert(char const *module, int loc) {
    //
    // NOTE: add here your application-specific error handling
    //
    (void)module;
    (void)loc;
    QS_ASSERTION(module, loc, static_cast<uint32_t>(10000U));
    NVIC_SystemReset();
}

// QS callbacks ==============================================================
#ifdef Q_SPY

static void UART0_setBaudrate(uint32_t baud);  // helper function

//............................................................................
bool QS::onStartup(void const *arg) {
    static uint8_t qsBuf[2*1024]; // buffer for Quantum Spy
    initBuf(qsBuf, sizeof(qsBuf));

    // setup the P0_2 UART0 TX pin
    LPC_PINCON->PINSEL0  &= ~(3U << 4); /* clear P0_2 function */
    LPC_PINCON->PINSEL0  |=  (1U << 4); /* P0_2 to UART function (TX) */
    LPC_PINCON->PINMODE0 &= ~(3U << 4); /* P0_2 pull-up register */

    // setup the P0_3 UART0 RX pin
    LPC_PINCON->PINSEL0  &= ~(3U << 6); /* clear P0_3 function */
    LPC_PINCON->PINSEL0  |=  (1U << 6); /* P0_3 to UART function (RX) */
    LPC_PINCON->PINMODE0 &= ~(3U << 6); /* P0_3 pull-up register */

    /* enable power to UART0 */
    LPC_SC->PCONP |= (1U << 3);

    /* enable FIFOs and default RX trigger level */
    LPC_UART0->FCR =
        (1U << 0)    /* FIFO Enable - 0 = Disables, 1 = Enabled */
        | (0U << 1)  /* Rx Fifo Reset */
        | (0U << 2)  /* Tx Fifo Reset */
        | (0U << 6); /* Rx irq trig: 0=1char, 1=4chars, 2=8chars, 3=14chars */

    /* disable IRQs */
    LPC_UART0->IER =
        (0U << 0)    /* Rx Data available IRQ disable */
        | (0U << 1)  /* Tx Fifo empty IRQ disable     */
        | (0U << 2); /* Rx Line Status IRQ disable    */


    // set default baud rate
    UART0_setBaudrate(115200U);

    // format 8-data-bits, 1-stop-bit, parity-none
    LPC_UART0->LCR =
        (3U << 0)    /* 8-data-bits    */
        | (0U << 2)  /* 1 stop-bit     */
        | (0U << 3)  /* parity disable */
        | (0U << 4); /* parity none    */

    DPP::QS_tickPeriod_ = SystemCoreClock / DPP::BSP::TICKS_PER_SEC;
    DPP::QS_tickTime_ = DPP::QS_tickPeriod_; // to start the timestamp at zero

    // setup the QS filters...
    QS_FILTER_ON(QS_QEP_STATE_ENTRY);
    QS_FILTER_ON(QS_QEP_STATE_EXIT);
    QS_FILTER_ON(QS_QEP_STATE_INIT);
    QS_FILTER_ON(QS_QEP_INIT_TRAN);
    QS_FILTER_ON(QS_QEP_INTERN_TRAN);
    QS_FILTER_ON(QS_QEP_TRAN);
    QS_FILTER_ON(QS_QEP_IGNORED);
    QS_FILTER_ON(QS_QEP_DISPATCH);
    QS_FILTER_ON(QS_QEP_UNHANDLED);

    QS_FILTER_ON(DPP::PHILO_STAT);

    return true; // return success
}
//............................................................................
void QS::onCleanup(void) {
}
//............................................................................
QSTimeCtr QS::onGetTime(void) {  // NOTE: invoked with interrupts DISABLED
    if ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0) { // not set?
        return DPP::QS_tickTime_ - static_cast<QSTimeCtr>(SysTick->VAL);
    }
    else { // the rollover occured, but the SysTick_ISR did not run yet
        return DPP::QS_tickTime_ + DPP::QS_tickPeriod_
               - static_cast<QSTimeCtr>(SysTick->VAL);
    }
}
//............................................................................
void QS::onFlush(void) {
    uint16_t b;

    QF_INT_DISABLE();
    while ((b = getByte()) != QS_EOD) {    // while not End-Of-Data...
        QF_INT_ENABLE();
        while ((LPC_UART0->LSR & 0x20U) == 0U) { // while THR empty...
        }
        LPC_UART0->THR = (b & 0xFFU);  // put into the DR register
        QF_INT_DISABLE();
    }
    QF_INT_ENABLE();
}
//............................................................................
//! callback function to reset the target (to be implemented in the BSP)
void QS::onReset(void) {
    //TBD
}
//............................................................................
//! callback function to execute a uesr command (to be implemented in BSP)
void QS::onCommand(uint8_t cmdId, uint32_t param) {
    (void)cmdId;
    (void)param;
    //TBD
}

//............................................................................
//
// Set the LPC UART0 barud-rate generator according to
// Section 14.4.12 in LPC176x Manual (document UM10360)
//
static void UART0_setBaudrate(uint32_t baud) {

    /* First we check to see if the basic divide with no DivAddVal/MulVal
    * ratio gives us an integer result. If it does, we set DivAddVal = 0,
    * MulVal = 1. Otherwise, we search the valid ratio value range to find
    * the closest match. This could be more elegant, using search methods
    * and/or lookup tables, but the brute force method is not that much
    * slower, and is more maintainable.
    */
    uint32_t PCLK     = SystemCoreClock; /* divider /1 set below */
    uint16_t DL       = PCLK / (16U * baud);
    uint8_t DivAddVal = 0U;
    uint8_t MulVal    = 1U;

    /* set PCLK divider to 1 */
    LPC_SC->PCLKSEL0 &= ~(0x3U << 6); /* clear divider bits */
    LPC_SC->PCLKSEL0 |=  (0x1U << 6); /* set divider to 1 */

    if ((PCLK % (16U * baud)) != 0U) { /* non zero remainder? */
        uint32_t err_best = baud;
        bool found = false;
        uint32_t b;
        uint8_t mv;
        for (mv = 1U; mv < 16U && !found; mv++) {
            uint16_t dlv;
            uint8_t dav;
            for (dav = 0U; dav < mv; ++dav) {
                /*
                * baud = PCLK / (16 * dlv * (1 + (DivAdd / Mul))
                * solving for dlv, we get
                * dlv = mul * PCLK / (16 * baud * (divadd + mul))
                * mul has 4 bits, PCLK has 27 so we have 1 bit headroom,
                * which can be used for rounding for many values of mul
                * and PCLK we have 2 or more bits of headroom which can
                * be used to improve precision
                * note: X / 32 doesn't round correctly.
                * Instead, we use ((X / 16) + 1) / 2 for correct rounding
                */
                if ((mv*PCLK*2U) & 0x80000000U) { /* 1 bit headroom */
                    dlv = ((((2U*mv*PCLK) / (baud*(dav + mv)))/16U) + 1U)/2U;
                }
                else { /* 2 bits headroom, use more precision */
                    dlv = ((((4U*mv*PCLK) / (baud*(dav+mv)))/32U) + 1U)/2U;
                }

                /* datasheet says if DLL==DLM==0, then 1 is used instead */
                if (dlv == 0U) {
                    dlv = 1U;
                }
                /* datasheet says if dav > 0 then DL must be >= 2 */
                if ((dav > 0U) && (dlv < 2U)) {
                    dlv = 2U;
                }
                /* integer rearrangement of baud equation (with rounding) */
                b = ((PCLK*mv / (dlv*(dav + mv)*8U)) + 1U)/2U;
                b = (b >= baud) ? (b - baud) : (baud - b);

                /* check to see how we did */
                if (b < err_best) {
                    err_best  = b;
                    DL        = dlv;
                    MulVal    = mv;
                    DivAddVal = dav;

                    if (b == baud) {
                        found = true;
                        break;   /* break out of the inner for-loop */
                    }
                }
            }
        }
    }

    // set LCR[DLAB] to enable writing to divider registers
    LPC_UART0->LCR |= (1U << 7);

    // set divider values
    LPC_UART0->DLM = (DL >> 8) & 0xFFU;
    LPC_UART0->DLL = (DL >> 0) & 0xFFU;
    LPC_UART0->FDR = ((uint32_t)DivAddVal << 0)
                   | ((uint32_t)MulVal    << 4);

    // clear LCR[DLAB]
    LPC_UART0->LCR &= ~(1U << 7);
}
#endif // Q_SPY
//--------------------------------------------------------------------------*/

} // namespace QP

//****************************************************************************
// NOTE00:
// The QF_AWARE_ISR_CMSIS_PRI constant from the QF port specifies the highest
// ISR priority that is disabled by the QF framework. The value is suitable
// for the NVIC_SetPriority() CMSIS function.
//
// Only ISRs prioritized at or below the QF_AWARE_ISR_CMSIS_PRI level (i.e.,
// with the numerical values of priorities equal or higher than
// QF_AWARE_ISR_CMSIS_PRI) are allowed to call the QK_ISR_ENTRY/QK_ISR_ENTRY
// macros or any other QF/QK  services. These ISRs are "QF-aware".
//
// Conversely, any ISRs prioritized above the QF_AWARE_ISR_CMSIS_PRI priority
// level (i.e., with the numerical values of priorities less than
// QF_AWARE_ISR_CMSIS_PRI) are never disabled and are not aware of the kernel.
// Such "QF-unaware" ISRs cannot call any QF/QK services. In particular they
// can NOT call the macros QK_ISR_ENTRY/QK_ISR_ENTRY. The only mechanism
// by which a "QF-unaware" ISR can communicate with the QF framework is by
// triggering a "QF-aware" ISR, which can post/publish events.
//
// NOTE01:
// The QV::onIdle() callback is called with interrupts disabled, because the
// determination of the idle condition might change by any interrupt posting
// an event. QV::onIdle() must internally enable interrupts, ideally
// atomically with putting the CPU to the power-saving mode.
//
// NOTE02:
// The User LED is used to visualize the idle loop activity. The brightness
// The User LED is used to visualize the idle loop activity. The brightness
// of the LED is proportional to the frequency of invcations of the idle loop.
// Please note that the LED is toggled with interrupts locked, so no interrupt
// execution time contributes to the brightness of the User LED.
//
