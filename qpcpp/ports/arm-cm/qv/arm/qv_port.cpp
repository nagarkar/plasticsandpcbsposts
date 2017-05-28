/// @file
/// @brief QP/C++ port to ARM Cortex-M, cooperative QV kernel, IAR-ARM toolset
/// @cond
///***************************************************************************
/// Last updated for version 5.8.1
/// Last updated on  2016-12-12
///
///                    Q u a n t u m     L e a P s
///                    ---------------------------
///                    innovating embedded systems
///
/// Copyright (C) Quantum Leaps, LLC. All rights reserved.
///
/// This program is open source software: you can redistribute it and/or
/// modify it under the terms of the GNU General Public License as published
/// by the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// Alternatively, this program may be distributed and modified under the
/// terms of Quantum Leaps commercial licenses, which expressly supersede
/// the GNU General Public License and are specifically designed for
/// licensees interested in retaining the proprietary status of their code.
///
/// This program is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License
/// along with this program. If not, see <http://www.gnu.org/licenses/>.
///
/// Contact information:
/// www.state-machine.com
/// mailto:info@state-machine.com
///***************************************************************************
/// @endcond

#include "qf_port.h"

#if (__TARGET_ARCH_THUMB != 3) // NOT Cortex-M0/M0+/M1(v6-M, v6S-M)?

extern "C" {

#define SCnSCB_ICTR  ((uint32_t volatile *)0xE000E004)
#define SCB_SYSPRI   ((uint32_t volatile *)0xE000ED14)
#define NVIC_IP      ((uint32_t volatile *)0xE000E400)

/*
* Initialize the exception priorities and IRQ priorities to safe values.
*
* Description:
* On Cortex-M3/M4/M7, this QV port disables interrupts by means of the
* BASEPRI register. However, this method cannot disable interrupt
* priority zero, which is the default for all interrupts out of reset.
* The following code changes the SysTick priority and all IRQ priorities
* to the safe value QF_BASEPRI, wich the QF critical section can disable.
* This avoids breaching of the QF critical sections in case the
* application programmer forgets to explicitly set priorities of all
* "kernel aware" interrupts.
*
* The interrupt priorities established in QV_init() can be later
* changed by the application-level code.
*/

void QV_init(void) {

    // set exception priorities to QF_BASEPRI...
    // SCB_SYSPRI1: Usage-fault, Bus-fault, Memory-fault
    SCB_SYSPRI[1] |= (QF_BASEPRI << 16) | (QF_BASEPRI << 8) | QF_BASEPRI;

    // SCB_SYSPRI2: SVCall
    SCB_SYSPRI[2] |= (QF_BASEPRI << 24);

    // SCB_SYSPRI3:  SysTick, PendSV, Debug
    SCB_SYSPRI[3] |= (QF_BASEPRI << 24) | (QF_BASEPRI << 16) | QF_BASEPRI;

    // set all implemented IRQ priories to QF_BASEPRI...
    uint32_t n = 8 + (*SCnSCB_ICTR << 3); // # interrupt priority registers
    do {
        --n;
        NVIC_IP[n] = (QF_BASEPRI << 24) | (QF_BASEPRI << 16)
                     | (QF_BASEPRI << 8) | QF_BASEPRI;
    } while (n != 0);
}

} // extern "C"

#endif // NOT Cortex-M0/M0+/M1(v6-M, v6S-M)?
