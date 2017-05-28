//****************************************************************************
// Product: DPP example, POSIX
// Last Updated for Version: 5.8.0
// Date of the Last Update:  2016-11-30
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>  // for memcpy() and memset()
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>

//****************************************************************************
namespace DPP {

Q_DEFINE_THIS_FILE

// Local objects -------------------------------------------------------------
static uint32_t l_rnd; // random seed

#ifdef Q_SPY
    enum {
        PHILO_STAT = QP::QS_USER
    };
    static uint8_t const l_clock_tick = 0U;
#endif

//............................................................................
void BSP::init(void) {
    printf("Dining Philosopher Problem example"
           "\nQP %s\n"
           "Press p to pause the forks\n"
           "Press s to serve the forks\n"
           "Press ESC to quit...\n",
           QP::versionStr);

    BSP::randomSeed(1234U);
    Q_ALLEGE(QS_INIT((void *)0));
    QS_OBJ_DICTIONARY(&l_clock_tick); // must be called *after* QF::init()
    QS_USR_DICTIONARY(PHILO_STAT);
}
//............................................................................
void BSP::terminate(int16_t result) {
    (void)result;
    QP::QF::stop();
}
//............................................................................
void BSP::displayPhilStat(uint8_t n, char const *stat) {
    printf("Philosopher %2d is %s\n", (int)n, stat);

    QS_BEGIN(PHILO_STAT, AO_Philo[n]) // application-specific record begin
        QS_U8(1, n);  // Philosopher number
        QS_STR(stat); // Philosopher status
    QS_END()
}
//............................................................................
void BSP::displayPaused(uint8_t paused) {
    printf("Paused is %s\n", paused ? "ON" : "OFF");
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

} // namespace DPP


//****************************************************************************

namespace QP {

static struct termios l_tsav; // structure with saved terminal attributes

//............................................................................
void QF::onStartup(void) { // QS startup callback
    struct termios tio;    // modified terminal attributes

    tcgetattr(0, &l_tsav); // save the current terminal attributes
    tcgetattr(0, &tio);    // obtain the current terminal attributes
    tio.c_lflag &= ~(ICANON | ECHO); // disable the canonical mode & echo
    tcsetattr(0, TCSANOW, &tio); // set the new attributes

    QF_setTickRate(DPP::BSP::TICKS_PER_SEC); // set the desired tick rate
}
//............................................................................
void QF::onCleanup(void) {  // cleanup callback
    printf("\nBye! Bye!\n");
    tcsetattr(0, TCSANOW, &l_tsav); // restore the saved terminal attributes
    QS_EXIT();  // perfomr the QS cleanup
}
//............................................................................
void QF_onClockTick(void) {

    QF::TICK_X(0U, &DPP::l_clock_tick); // process time events at rate 0

    struct timeval timeout = { 0, 0 }; // timeout for select()
    fd_set con; // FD set representing the console
    FD_ZERO(&con);
    FD_SET(0, &con);
    // check if a console input is available, returns immediately
    if (0 != select(1, &con, 0, 0, &timeout)) { // any descriptor set?
        char ch;
        read(0, &ch, 1);
        if (ch == '\33') { // ESC pressed?
            DPP::BSP::terminate(0);
        }
        else if (ch == 'p') {
            QF::PUBLISH(Q_NEW(QEvt, DPP::PAUSE_SIG), &DPP::l_clock_tick);
        }
        else if (ch == 's') {
            QF::PUBLISH(Q_NEW(QEvt, DPP::SERVE_SIG), &DPP::l_clock_tick);
        }
    }
}
//............................................................................
extern "C" void Q_onAssert(char const * const module, int loc) {
    QS_ASSERTION(module, loc, 10000U); // report assertion to QS
    fprintf(stderr, "Assertion failed in %s, location %d", module, loc);
    DPP::BSP::terminate(-1);
}

//----------------------------------------------------------------------------*/
#ifdef Q_SPY // define QS callbacks

#include "qspy.h"

static uint8_t l_running;

//............................................................................
static void *idleThread(void *par) { // the expected P-Thread signature
    (void)par;

    l_running = (uint8_t)1;
    while (l_running) {
        uint16_t nBytes = 256U;
        uint8_t const *block;
        struct timeval timeout = { 0, 10000 }; // timeout for select()

        QF_CRIT_ENTRY(dummy);
        block = QS::getBlock(&nBytes);
        QF_CRIT_EXIT(dummy);

        if (block != (uint8_t *)0) {
            QSPY_parse(block, nBytes);
        }
        select(0, 0, 0, 0, &timeout);   // sleep for a while
    }
    return 0; // return success
}
//............................................................................
bool QS::onStartup(void const */*arg*/) {
    static uint8_t qsBuf[4*1024]; // 4K buffer for Quantum Spy
    initBuf(qsBuf, sizeof(qsBuf));

    QSPY_config(QP_VERSION,         // version
                QS_OBJ_PTR_SIZE,    // objPtrSize
                QS_FUN_PTR_SIZE,    // funPtrSize
                QS_TIME_SIZE,       // tstampSize
                Q_SIGNAL_SIZE,      // sigSize,
                QF_EVENT_SIZ_SIZE,  // evtSize
                QF_EQUEUE_CTR_SIZE, // queueCtrSize
                QF_MPOOL_CTR_SIZE,  // poolCtrSize
                QF_MPOOL_SIZ_SIZE,  // poolBlkSize
                QF_TIMEEVT_CTR_SIZE,// tevtCtrSize
                (void *)0,          // matFile,
                (void *)0,
                (QSPY_CustParseFun)0); // customized parser function

    // set up the QS filters...
    QS_FILTER_ON(QS_QEP_STATE_ENTRY);
    QS_FILTER_ON(QS_QEP_STATE_EXIT);
    QS_FILTER_ON(QS_QEP_STATE_INIT);
    QS_FILTER_ON(QS_QEP_INIT_TRAN);
    QS_FILTER_ON(QS_QEP_INTERN_TRAN);
    QS_FILTER_ON(QS_QEP_TRAN);
    QS_FILTER_ON(QS_QEP_IGNORED);
    QS_FILTER_ON(QS_QEP_DISPATCH);
    QS_FILTER_ON(QS_QEP_UNHANDLED);

    QS_FILTER_ON(QS_QF_ACTIVE_POST_FIFO);
    QS_FILTER_ON(QS_QF_ACTIVE_POST_LIFO);
    QS_FILTER_ON(QS_QF_PUBLISH);

    QS_FILTER_ON(DPP::PHILO_STAT);

    pthread_attr_t attr;
    struct sched_param param;
    pthread_t idle;

    // SCHED_FIFO corresponds to real-time preemptive priority-based
    // scheduler.
    // NOTE: This scheduling policy requires the superuser priviledges

    pthread_attr_init(&attr);
    pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
    param.sched_priority = sched_get_priority_min(SCHED_FIFO);

    pthread_attr_setschedparam(&attr, &param);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    if (pthread_create(&idle, &attr, &idleThread, 0) != 0) {
        // Creating the p-thread with the SCHED_FIFO policy failed.
        // Most probably this application has no superuser privileges,
        // so we just fall back to the default SCHED_OTHER policy
        // and priority 0.
        pthread_attr_setschedpolicy(&attr, SCHED_OTHER);
        param.sched_priority = 0;
        pthread_attr_setschedparam(&attr, &param);
        if (pthread_create(&idle, &attr, &idleThread, 0) == 0) {
            return false;
        }
    }
    pthread_attr_destroy(&attr);

    return true;
}
//............................................................................
void QS::onCleanup(void) {
    l_running = (uint8_t)0;
    QSPY_stop();
}
//............................................................................
void QS::onFlush(void) {
    uint16_t nBytes = 1024U;
    uint8_t const *block;
    while ((block = getBlock(&nBytes)) != (uint8_t *)0) {
        QSPY_parse(block, nBytes);
        nBytes = 1024U;
    }
}
//............................................................................
QSTimeCtr QS::onGetTime(void) {
    return (QSTimeCtr)clock(); // see NOTE01
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
void QSPY_onPrintLn(void) {
    fputs(QSPY_line, stdout);
    fputc('\n', stdout);
}

//****************************************************************************
// NOTE01:
// clock() is the most portable facility, but might not provide the desired
// granularity. Other, less-portable alternatives are clock_gettime(),
// rdtsc(), or gettimeofday().
//

#endif // Q_SPY
//----------------------------------------------------------------------------

} // namespace QP

