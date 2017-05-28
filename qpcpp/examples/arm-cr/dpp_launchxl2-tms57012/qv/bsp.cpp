///***************************************************************************
// Product: DPP example, LAUCHXL2-TMS570LS12 board, cooperative QV kernel
// Last Updated for Version: 5.7.0
// Date of the Last Update:  2016-08-31
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

#include "sys_common.h"
#include "sys_core.h"
#include "sys_vim.h"
#include "system.h"
#include "gio.h"
#include "rti.h"
#include "het.h"
#include "sci.h"
// add other drivers if necessary...

// namespace DPP *************************************************************
namespace DPP {

Q_DEFINE_THIS_FILE

// Local-scope objects -------------------------------------------------------
#define LED2_PIN    1
#define LED2_PORT   gioPORTB

#define LED3_PIN    2
#define LED3_PORT   gioPORTB

// NOTE: Switch-A is multiplexed on the same port/pin as LED3,
// so you can use one or the other but not both simultaneously.
//
#define SWA_PIN     2
#define SWA_PORT    gioPORTB

#define SWB_PIN     15
#define SWB_PORT    hetREG1

#define VIM_RAM     ((t_isrFuncPTR *)0xFFF82000U)

static uint32_t l_rnd; // random seed

#ifdef Q_SPY

    // QS source IDs
    static uint8_t const l_rtiCompare0 = (uint8_t)0;
    static uint8_t const l_ssiTest = (uint8_t)0;

    enum AppRecords { // application-specific trace records
        PHILO_STAT = QP::QS_USER,
        COMMAND_STAT
    };

#endif

} // namespace DPP

// ISRs used in this project =================================================
//............................................................................
extern "C" {
//............................................................................
// NOTE:
// The QV kernel can use the standard interrupt implementation generated
// by the HALCoGen. Here the RTI COMPARE0 is handled in a "notification"
// function called from rtiCompare0Interrupt() in the rti.c module.
//
void rtiNotification(uint32 notification) {
    if (notification == rtiNOTIFICATION_COMPARE0) {
       // state of the button debouncing, see below
       static struct ButtonsDebouncing {
           uint32_t depressed;
           uint32_t previous;
       } buttons = { ~0U, ~0U };
       uint32_t current;
       uint32_t tmp;

       rtiREG1->INTFLAG = 1U;    // clear the interrutp source
       QP::QF::TICK_X(0U, &DPP::l_rtiCompare0); // time events for rate 0

       // Perform the debouncing of buttons. The algorithm for debouncing
       // adapted from the book "Embedded Systems Dictionary" by Jack Ganssle
       // and Michael Barr, page 71.
       //
       current = ~SWB_PORT->DIN; // read SWB
       tmp = buttons.depressed; // save the debounced depressed buttons
       buttons.depressed |= (buttons.previous & current); // set depressed
       buttons.depressed &= (buttons.previous | current); // clear released
       buttons.previous   = current; // update the history
       tmp ^= buttons.depressed;     // changed debounced depressed
       if ((tmp & (1U << SWB_PIN)) != 0U) {  // debounced SWB state changed?
           if ((buttons.depressed & (1U << SWB_PIN)) != 0U) { // SWB depressed?
               static QP::QEvt const pauseEvt = { DPP::PAUSE_SIG, 0U, 0U};
               QP::QF::PUBLISH(&pauseEvt, &DPP::l_rtiCompare0);
           }
           else {            // the button is released
               static QP::QEvt const serveEvt = { DPP::SERVE_SIG, 0U, 0U};
               QP::QF::PUBLISH(&serveEvt, &DPP::l_rtiCompare0);
           }
       }
    }
}


//............................................................................
#ifdef Q_SPY
//
// ISR for receiving bytes from the QSPY Back-End
// NOTE: This ISR is "QP-unaware" meaning that it does not interact with
// the QP and is not disabled. Such ISRs don't need to call QK_ISR_ENTRY/
// QK_ISR_EXIT and they cannot post or publish events.
//
#if defined __IAR_SYSTEMS_ICC__
    FIQ
#elif defined __TI_ARM__
    #pragma CODE_STATE(32)
    #pragma INTERRUPT(FIQ)
#else
    #error Unsupported compiler
#endif
void sciHighLevel(void) {
    uint32_t vec = scilinREG->INTVECT0;
    if (vec == 11U) { // SCI receive interrupt
        uint32_t b = scilinREG->RD;
        QP::QS::rxPut(b);
    }
}
#endif // Q_SPY

} // extern "C"

namespace DPP {

// BSP functions =============================================================
void BSP::init(void) {
    // configure the LEDs
    gioInit();
    LED2_PORT->DIR |= (1U << LED2_PIN);  // set as output
    LED3_PORT->DIR |= (1U << LED3_PIN);  // set as output

    // configure the Buttons
    SWB_PORT->DIR  &= (1U << SWB_PIN);    // set as input

    // initialize the random seed
    BSP::randomSeed(1234U);

    if (QS_INIT((void *)0) == 0) { // initialize the QS software tracing
        Q_ERROR();
    }
    QS_OBJ_DICTIONARY(&l_rtiCompare0);
    QS_OBJ_DICTIONARY(&l_ssiTest);
    QS_USR_DICTIONARY(PHILO_STAT);
    QS_USR_DICTIONARY(COMMAND_STAT);
}
//............................................................................
void BSP::displayPhilStat(uint8_t n, char const *stat) {
    if (stat[0] == 'e') {
        LED2_PORT->DSET = (1U << LED2_PIN);
    }
    else {
        LED2_PORT->DCLR = (1U << LED2_PIN);
    }

    QS_BEGIN(PHILO_STAT, AO_Philo[n]) // application-specific record begin
        QS_U8(1, n);  // Philosopher number
        QS_STR(stat); // Philosopher status
    QS_END()
}
//............................................................................
void BSP::displayPaused(uint8_t paused) {
    if (paused != 0U) {
        //LED2_PORT->DSET = (1U << LED2_PIN);
    }
    else {
        //LED2_PORT->DCLR = (1U << LED2_PIN);
    }
}
//............................................................................
uint32_t BSP::random(void) { // a very cheap pseudo-random-number generator
    // Some flating point code is to exercise the VFP...
    float volatile x = 3.1415926F;
    x = x + 2.7182818F;

    // "Super-Duper" Linear Congruential Generator (LCG)
    // LCG(2^32, 3*7*11*13*23, 0, seed)
    //
    uint32_t rnd = l_rnd * (3U*7U*11U*13U*23U);
    l_rnd = rnd; // set for the next time

    return (rnd >> 8);
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
    rtiInit(); // configure RTI with UC counter of 7
    rtiSetPeriod(rtiCOUNTER_BLOCK0,
                 (uint32)((RTI_FREQ*1E6/(7+1))/DPP::BSP::TICKS_PER_SEC));
    rtiEnableNotification(rtiNOTIFICATION_COMPARE0);
    rtiStartCounter(rtiCOUNTER_BLOCK0);

    // NOTE: don't need to install the IRQ handler in VIM_RAM, because
    // the standard handler rtiCompare0Interrupt() installed in the
    // HALCoGen code is adequate
    //
    vimREG->FIRQPR0 &= ~(1U << 2);   // designate interrupt as IRQ, NOTE00
    vimREG->REQMASKSET0 = (1U << 2); // enable interrupt

    QF_INT_ENABLE_ALL(); // enable all interrupts (IRQ and FIQ)
}
//............................................................................
void QF::onCleanup(void) {
}

//............................................................................
void QV::onIdle(void) { // CATION: called with interrupts DISABLED, NOTE01
    // toggle the User LED on and then off, see NOTE01
    LED3_PORT->DSET = (1U << LED3_PIN);
    LED3_PORT->DCLR = (1U << LED3_PIN);

#ifdef Q_SPY
    QS::rxParse();  // parse all the received bytes
    QF_INT_ENABLE();

    //if (sciIsTxReady(scilinREG)) {
    if ((scilinREG->FLR & (uint32)SCI_TX_INT) != 0U) {  // is TX empty?
        uint16_t b;

        QF_INT_DISABLE();
        b = QS::getByte();
        QF_INT_ENABLE();

        if (b != QS_EOD) {  // not End-Of-Data?
            //sciSendByte(scilinREG, (b & 0xFFU));
            scilinREG->TD = (b & 0xFFU);  // put into the TD register
        }
    }
#elif defined NDEBUG
    // Put the CPU and peripherals to the low-power mode.
    // you might need to customize the clock management for your application,
    // see the datasheet for your particular Cortex-R MCU.
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

#ifndef NDEBUG
    // light up both LEDs
    LED2_PORT->DSET = (1U << LED2_PIN);
    LED3_PORT->DSET = (1U << LED3_PIN);
    // for debugging, hang on in an endless loop until SWB is pressed...
    while ((SWB_PORT->DIN & (1U << SWB_PIN)) != 0) {
    }
#endif

    systemREG1->SYSECR = 0; // perform system reset
}

// QS callbacks ==============================================================
#ifdef Q_SPY
//............................................................................
bool QS::onStartup(void const *arg) {
    static uint8_t qsTxBuf[2*1024]; // buffer for QS transmit channel
    static uint8_t qsRxBuf[100];    // buffer for QS receive channel
    initBuf  (qsTxBuf, sizeof(qsTxBuf));
    rxInitBuf(qsRxBuf, sizeof(qsRxBuf));

    // the SCI (UART) is configured in HALCoGen for 8-n-1 and 115200 baud
    sciInit();

    VIM_RAM[13 + 1] = (t_isrFuncPTR)&sciHighLevel; // install the ISR
    vimREG->FIRQPR0 |= (1U << 13);   // designate interrupt as FIQ
    vimREG->REQMASKSET0 = (1U << 13); // enable interrupt

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
    QS_FILTER_ON(DPP::COMMAND_STAT);

    return true; // return success
}
//............................................................................
void QS::onCleanup(void) {
}
//............................................................................
QSTimeCtr QS::onGetTime(void) {  // NOTE: invoked with interrupts DISABLED
    return rtiREG1->CNT[0].FRCx; // free running RTI counter0
}
//............................................................................
void QS::onFlush(void) {
    uint16_t b;

    QF_INT_DISABLE();
    while ((b = getByte()) != QS_EOD) { // while not End-Of-Data...
        QF_INT_ENABLE();
        //while (!sciIsTxReady(scilinREG)) {
        while ((scilinREG->FLR & (uint32)SCI_TX_INT) == 0U) {
        }
        //sciSendByte(scilinREG, (b & 0xFFU));
        scilinREG->TD = (b & 0xFFU);
        QF_INT_DISABLE();
    }
    QF_INT_ENABLE();
}
//............................................................................
//! callback function to reset the target (to be implemented in the BSP)
void QS::onReset(void) {
    systemREG1->SYSECR = 0; // perform system reset
}
//............................................................................
//! callback function to execute a user command (to be implemented in BSP)
extern "C" void assert_failed(char const *module, int loc);
void QS::onCommand(uint8_t cmdId, uint32_t param) {
    (void)cmdId;
    (void)param;

    // application-specific record
    QS_BEGIN(DPP::COMMAND_STAT, static_cast<void *>(0))
        QS_U8(2, cmdId);
        QS_U32(8, param);
    QS_END()

    if ((cmdId == 10U) || (cmdId == 11U)) {
        // report error
        QS_BEGIN(QS_RX_STATUS, static_cast<void *>(0))
            QS_U8_(static_cast<uint8_t>(0x80) | cmdId); // error
        QS_END()
    }
}

#endif // Q_SPY
//----------------------------------------------------------------------------

} // namespace QP

//****************************************************************************
// NOTE00:
// The FIQ-type interrupts are never disabled in this QP port, therefore
// they can always preempt any code, including the IRQ-handlers (ISRs).
// Therefore, FIQ-type interrupts are "kernel-unaware" and must NEVER call
// any QP services, such as posting events.
//
// NOTE01:
// One of the LEDs is used to visualize the idle loop activity. The brightness
// of the LED is proportional to the frequency of invcations of the idle loop.
// Please note that the LED is toggled with interrupts locked, so no interrupt
// execution time contributes to the brightness of the User LED.
//
