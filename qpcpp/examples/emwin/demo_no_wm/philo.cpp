//////////////////////////////////////////////////////////////////////////////
// Product: DPP example
// Last updated for version 5.8.2
// Last updated on  2017-01-15
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
//////////////////////////////////////////////////////////////////////////////
#include "qpcpp.h"
#include "dpp.h"
#include "bsp.h"

Q_DEFINE_THIS_FILE

// Active object class -------------------------------------------------------
class Philo : public QActive {
private:
    QTimeEvt m_timeEvt; // to timeout thinking or eating

public:
    Philo();

private:
    static QState initial (Philo *me, QEvt const *e);
    static QState thinking(Philo *me, QEvt const *e);
    static QState hungry  (Philo *me, QEvt const *e);
    static QState eating  (Philo *me, QEvt const *e);
};

// Local objects -------------------------------------------------------------
static Philo l_philo[N_PHILO]; // storage for all Philos

#define THINK_TIME  7
#define EAT_TIME    5

// helper macro to provide the ID of Philo "me_"
#define PHILO_ID(me_)    ((uint8_t)((me_) - l_philo))

enum InternalSignals { // internal signals
    TIMEOUT_SIG = MAX_SIG
};
// Global objects ------------------------------------------------------------
QActive * const AO_Philo[N_PHILO] = { // "opaque" pointers to Philo AOs
    &l_philo[0],
    &l_philo[1],
    &l_philo[2],
    &l_philo[3],
    &l_philo[4]
};

//............................................................................
Philo::Philo()
    : QActive((QStateHandler)&Philo::initial),
      m_timeEvt(TIMEOUT_SIG)
{}
//............................................................................
QState Philo::initial(Philo *me, QEvt const *) {
    static uint8_t registered; // starts off with 0, per C-standard
    if (!registered) {
        QS_OBJ_DICTIONARY(&l_philo[0]);
        QS_OBJ_DICTIONARY(&l_philo[0].m_timeEvt);
        QS_OBJ_DICTIONARY(&l_philo[1]);
        QS_OBJ_DICTIONARY(&l_philo[1].m_timeEvt);
        QS_OBJ_DICTIONARY(&l_philo[2]);
        QS_OBJ_DICTIONARY(&l_philo[2].m_timeEvt);
        QS_OBJ_DICTIONARY(&l_philo[3]);
        QS_OBJ_DICTIONARY(&l_philo[3].m_timeEvt);
        QS_OBJ_DICTIONARY(&l_philo[4]);
        QS_OBJ_DICTIONARY(&l_philo[4].m_timeEvt);

        QS_FUN_DICTIONARY(&Philo::initial);
        QS_FUN_DICTIONARY(&Philo::thinking);
        QS_FUN_DICTIONARY(&Philo::hungry);
        QS_FUN_DICTIONARY(&Philo::eating);

        registered = (uint8_t)1;
    }
    QS_SIG_DICTIONARY(HUNGRY_SIG, me);  // signal for each Philos
    QS_SIG_DICTIONARY(TIMEOUT_SIG, me); // signal for each Philos

    me->subscribe(EAT_SIG);

    return Q_TRAN(&Philo::thinking);
}
//............................................................................
QState Philo::thinking(Philo *me, QEvt const *e) {
    switch (e->sig) {
        case Q_ENTRY_SIG: {
            me->m_timeEvt.postIn(me, THINK_TIME);
            return Q_HANDLED();
        }
        case TIMEOUT_SIG: {
            return Q_TRAN(&Philo::hungry);
        }
        case EAT_SIG: // intentionally fall-through
        case DONE_SIG: {
            // EAT or DONE must be for other Philos than this one
            Q_ASSERT(((TableEvt const *)e)->philoNum != PHILO_ID(me));
            return Q_HANDLED();
        }
    }
    return Q_SUPER(&QHsm::top);
}
//............................................................................
QState Philo::hungry(Philo *me, QEvt const *e) {
    switch (e->sig) {
        case Q_ENTRY_SIG: {
            TableEvt *pe = Q_NEW(TableEvt, HUNGRY_SIG);
            pe->philoNum = PHILO_ID(me);
            AO_Table->POST(pe, me);
            return Q_HANDLED();
        }
        case EAT_SIG: {
            if (((TableEvt *)e)->philoNum == PHILO_ID(me)) {
                return Q_TRAN(&Philo::eating);
            }
            break;
        }
        case DONE_SIG: {
            // DONE must be for other Philos than this one
            Q_ASSERT(((TableEvt const *)e)->philoNum != PHILO_ID(me));
            return Q_HANDLED();
        }
    }
    return Q_SUPER(&QHsm::top);
}
//............................................................................
QState Philo::eating(Philo *me, QEvt const *e) {
    switch (e->sig) {
        case Q_ENTRY_SIG: {
            me->m_timeEvt.postIn(me, EAT_TIME);
            return Q_HANDLED();
        }
        case Q_EXIT_SIG: {
            TableEvt *pe = Q_NEW(TableEvt, DONE_SIG);
            pe->philoNum = PHILO_ID(me);
            QF::PUBLISH(pe, me);
            return Q_HANDLED();
        }
        case TIMEOUT_SIG: {
            return Q_TRAN(&Philo::thinking);
        }
        case EAT_SIG: // intentionally fall-through
        case DONE_SIG: {
            // EAT or DONE must be for other Philos than this one
            Q_ASSERT(((TableEvt const *)e)->philoNum != PHILO_ID(me));
            return Q_HANDLED();
        }
    }
    return Q_SUPER(&QHsm::top);
}

