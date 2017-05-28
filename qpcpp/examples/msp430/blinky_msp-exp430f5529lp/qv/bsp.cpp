//****************************************************************************
// Product: "Blinky" example on MSP-EXP430F5529LP board, cooperative QV kernel
// Last updated for version 5.5.0
// Last updated on  2015-09-23
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
#include "blinky.h"
#include "bsp.h"

#include <msp430f5529.h>  // MSP430 variant used
// add other drivers if necessary...

#ifdef Q_SPY
    #error Simple Blinky Application does not provide Spy build configuration
#endif

//Q_DEFINE_THIS_FILE

// Local-scope objects -------------------------------------------------------
// 1MHz clock setting, see BSP_init()
#define BSP_MCK     1000000U
#define BSP_SMCLK   1000000U

#define LED1        (1U << 0)
#define LED2        (1U << 7)

#define BTN_S1      (1U << 1)

// ISRs used in this project =================================================
extern "C" {

//............................................................................
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
    __interrupt void TIMER0_A0_ISR (void); // prototype
    #pragma vector=TIMER0_A0_VECTOR
    __interrupt void TIMER0_A0_ISR(void)
#elif defined(__GNUC__)
    __attribute__ ((interrupt(TIMER0_A0_VECTOR)))
    void TIMER0_A0_ISR (void)
#else
    #error Compiler not supported!
#endif
{
#ifdef NDEBUG
    __low_power_mode_off_on_exit(); // see NOTE1
#endif

    QF::TICK_X(0U, (void *)0); // process time events for rate 0
}

} // extern "C"

// BSP functions =============================================================
void BSP_init(void) {
    WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer

    // leave the MCK and SMCLK at default DCO setting

    P1DIR |= LED1;  // set LED1 pin to output
    P4DIR |= LED2;  // set LED2 pin to output
}
//............................................................................
void BSP_ledOff(void) {
    P1OUT &= ~LED1; // turn LED1 off
}
//............................................................................
void BSP_ledOn(void) {
    P1OUT |= LED1;  // turn LED1 on
}


// QF callbacks ==============================================================
void QF::onStartup(void) {
    TA0CCTL0 = CCIE;                          // CCR0 interrupt enabled
    TA0CCR0 = BSP_MCK / BSP_TICKS_PER_SEC;
    TA0CTL = TASSEL_2 + MC_1 + TACLR;         // SMCLK, upmode, clear TAR
}
//............................................................................
void QF::onCleanup(void) {
}
//............................................................................
void QV::onIdle(void) { // NOTE: called with interrutps DISABLED, see NOTE1
    // toggle LED2 on and then off, see NOTE2
    P4OUT |=  LED2;        // turn LED2 on
    P4OUT &= ~LED2;        // turn LED2 off

#ifdef NDEBUG
    // Put the CPU and peripherals to the low-power mode.
    // you might need to customize the clock management for your application,
    // see the datasheet for your particular MSP430 MCU.
    //
    __low_power_mode_1(); // Enter LPM1; also ENABLES interrupts
#else
    QF_INT_ENABLE(); // just enable interrupts
#endif
}

//............................................................................
extern "C" void Q_onAssert(char const *module, int loc) {
    // implement the error-handling policy for your application!!!
    QF_INT_DISABLE(); // disable all interrupts
    QS_ASSERTION(module, loc, static_cast<uint32_t>(10000U));

    // cause the reset of the CPU...
    WDTCTL = WDTPW | WDTHOLD;
    __asm("    push &0xFFFE");
    // return from function does the reset
}

//****************************************************************************
// NOTE1:
// With the cooperative QV kernel for MSP430, it is necessary to explicitly
// turn the low-power mode OFF in the interrupt, because the return
// from the interrupt will restore the CPU status register, which will
// re-enter the low-power mode. This, in turn, will prevent the QV event-loop
// from running.
//
// NOTE2:
// NOTE1:
// One of the LEDs is used to visualize the idle loop activity. The brightness
// of the LED is proportional to the frequency of invcations of the idle loop.
// Please note that the LED is toggled with interrupts locked, so no interrupt
// execution time contributes to the brightness of the User LED.
//
