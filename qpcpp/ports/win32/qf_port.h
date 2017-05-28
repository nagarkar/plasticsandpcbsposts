/// \file
/// \brief QF/C++ port to Win32 API
/// \cond
///***************************************************************************
/// Last updated for version 5.8.2
/// Last updated on  2016-12-22
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
/// http://www.state-machine.com
/// mailto:info@state-machine.com
///***************************************************************************
/// \endcond

#ifndef qf_port_h
#define qf_port_h

// Win32 event queue and thread types
#define QF_EQUEUE_TYPE       QEQueue
#define QF_OS_OBJECT_TYPE    void*
#define QF_THREAD_TYPE       void*

// The maximum number of active objects in the application
#define QF_MAX_ACTIVE        64

// The number of system clock tick rates
#define QF_MAX_TICK_RATE     2

// various QF object sizes configuration for this port
#define QF_EVENT_SIZ_SIZE    4
#define QF_EQUEUE_CTR_SIZE   4
#define QF_MPOOL_SIZ_SIZE    4
#define QF_MPOOL_CTR_SIZE    4
#define QF_TIMEEVT_CTR_SIZE  4

// QF interrupt disable/enable, see NOTE1
#define QF_INT_DISABLE()     (QP::QF_enterCriticalSection_())
#define QF_INT_ENABLE()      (QP::QF_leaveCriticalSection_())

// Win32 critical section
// QF_CRIT_STAT_TYPE -- not defined
#define QF_CRIT_ENTRY(dummy) QF_INT_DISABLE()
#define QF_CRIT_EXIT(dummy)  QF_INT_ENABLE()

// QF_LOG2 not defined -- use the internal LOG2() implementation

#include "qep_port.h"  // QEP port
#include "qequeue.h"   // Win32 needs event-queue
#include "qmpool.h"    // Win32 needs memory-pool
#include "qpset.h"     // Win32 needs priority-set
#include "qf.h"        // QF platform-independent public interface

namespace QP {

void QF_enterCriticalSection_(void);
void QF_leaveCriticalSection_(void);

// set Win32 thread priority;
// can be called either before or after QActive::START()
//
void QF_setWin32Prio(QActive *act, int_t win32Prio);

// set clock tick rate
void QF_setTickRate(uint32_t ticksPerSec);

// clock tick callback (provided in the app)
void QF_onClockTick(void);

} // namespace QP


// special adaptations for QWIN GUI applications
#ifdef QWIN_GUI
    // replace main() with main_gui() as the entry point to a GUI app.
    #define main() main_gui()
    int_t main_gui(); // prototype of the GUI application entry point
#endif

// portable "safe" facilities from <stdio.h> and <string.h> ...
#ifdef _MSC_VER /* Microsoft C/C++ compiler? */

#define SNPRINTF_S(buf_, len_, format_, ...) \
    _snprintf_s(buf_, len_, _TRUNCATE, format_, ##__VA_ARGS__)

#define STRNCPY_S(dest_, src_, len_) \
    strncpy_s(dest_, len_, src_, _TRUNCATE)

#define FOPEN_S(fp_, fName_, mode_) \
    if (fopen_s(&fp_, fName_, mode_) != 0) { \
        fp_ = static_cast<FILE *>(0); \
    } else (void)0

#define CTIME_S(buf_, len_, time_) \
    ctime_s((char *)buf_, len_, time_)

#define SSCANF_S(buf_, format_, ...) \
    sscanf_s(buf_, format_, ##__VA_ARGS__)

#else // other C/C++ compilers (GNU, etc.)

#define SNPRINTF_S(buf_, len_, format_, ...) \
    snprintf(buf_, len_, format_, ##__VA_ARGS__)

#define STRNCPY_S(dest_, src_, len_) strncpy(dest_, src_, len_)

#define FOPEN_S(fp_, fName_, mode_) \
    (fp_ = fopen(fName_, mode_))

#define CTIME_S(buf_, len_, time_) \
    strncpy(static_cast<char *>(buf_), ctime(time_), len_)

#define SSCANF_S(buf_, format_, ...) \
    sscanf(buf_, format_, ##__VA_ARGS__)

#endif // _MSC_VER

//****************************************************************************
// interface used only inside QF, but not in applications

#ifdef QP_IMPL

    // Win32-specific scheduler locking, see NOTE2
    #define QF_SCHED_STAT_
    #define QF_SCHED_LOCK_(dummy) QF_enterCriticalSection_()
    #define QF_SCHED_UNLOCK_()    QF_leaveCriticalSection_()

    // Win32-specific event queue customization
    #define QACTIVE_EQUEUE_WAIT_(me_) \
        while ((me_)->m_eQueue.m_frontEvt == static_cast<QEvt const *>(0)) { \
            QF_CRIT_EXIT_(); \
            (void)WaitForSingleObject((me_)->m_osObject, (DWORD)INFINITE); \
            QF_CRIT_ENTRY_(); \
        }

    #define QACTIVE_EQUEUE_SIGNAL_(me_) \
        Q_ASSERT_ID(410, QF::active_[(me_)->m_prio] \
                         != static_cast<QActive *>(0)); \
        (void)SetEvent((me_)->m_osObject)

    // Win32-specific event pool operations
    #define QF_EPOOL_TYPE_  QMPool

    #define QF_EPOOL_INIT_(p_, poolSto_, poolSize_, evtSize_) \
        (p_).init((poolSto_), (poolSize_), (evtSize_))

    #define QF_EPOOL_EVENT_SIZE_(p_)  ((p_).getBlockSize())
    #define QF_EPOOL_GET_(p_, e_, m_) \
        ((e_) = static_cast<QEvt *>((p_).get((m_))))
    #define QF_EPOOL_PUT_(p_, e_)     ((p_).put(e_))

    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>  // Win32 API

#endif  // QP_IMPL

// NOTES: ====================================================================
//
// NOTE1:
// QF, like all real-time frameworks, needs to execute certain sections of
// code indivisibly to avoid data corruption. The most straightforward way of
// protecting such critical sections of code is disabling and enabling
// interrupts, which Win32 does not allow.
//
// This QF port uses therefore a single package-scope Win32 critical section
// object QF_win32CritSect_ to protect all critical sections.
//
// Using the single critical section object for all crtical section guarantees
// that only one thread at a time can execute inside a critical section. This
// prevents race conditions and data corruption.
//
// Please note, however, that the Win32 critical section implementation
// behaves differently than interrupt locking. A common Win32 critical section
// ensures that only one thread at a time can execute a critical section, but
// it does not guarantee that a context switch cannot occur within the
// critical section. In fact, such context switches probably will happen, but
// they should not cause concurrency hazards because the critical section
// eliminates all race conditionis.
//
// Unlinke simply disabling and enabling interrupts, the critical section
// approach is also subject to priority inversions. Various versions of
// Windows handle priority inversions differently, but it seems that most of
// them recognize priority inversions and dynamically adjust the priorities of
// threads to prevent it. Please refer to the MSN articles for more
// information.
//
// NOTE2:
// Scheduler locking (used inside QF_publish_()) is implemented in this
// port with the main critical section. This means that event multicasting
// will appear atomic, in the sense that no thread will be able to post
// events during multicasting.
//

#endif // qf_port_h
