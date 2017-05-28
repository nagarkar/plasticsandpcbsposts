//////////////////////////////////////////////////////////////////////////////
// Product: DPP example with emWin/uC/GUI, WITH Window Manager
// Last Updated for Version: 5.1.1
// Date of the Last Update:  Nov 08, 2013
//
//                    Q u a n t u m     L e a P s
//                    ---------------------------
//                    innovating embedded systems
//
// Copyright (C) 2002-2013 Quantum Leaps, LLC. All rights reserved.
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
// Quantum Leaps Web sites: http://www.quantum-leaps.com
//                          http://www.state-machine.com
// e-mail:                  info@quantum-leaps.com
//////////////////////////////////////////////////////////////////////////////
#include "qp_port.h"
#include "dpp.h"
#include "bsp.h"

extern "C" {
    #include "GUI.h"
    #include "WM.h"                                   // emWin Windows Manager
    #include "DIALOG.h"
    #include "SIM.h"
}

Q_DEFINE_THIS_FILE

// Active object class -------------------------------------------------------
class Table : public QActive {
private:
    uint8_t m_fork[N_PHILO];
    uint8_t m_isHungry[N_PHILO];

public:
    Table();

private:
    static QState initial(Table *me, QEvt const *e);
    static QState ready  (Table *me, QEvt const *e);
    static QState serving(Table *me, QEvt const *e);
    static QState paused (Table *me, QEvt const *e);
};

#define RIGHT(n_) ((uint8_t)(((n_) + (N_PHILO - 1)) % N_PHILO))
#define LEFT(n_)  ((uint8_t)(((n_) + 1) % N_PHILO))
enum m_forkState { FREE, USED };

// Local objects -------------------------------------------------------------
static Table l_table;                                    // local Table object

#ifdef Q_SPY
    enum QSUserRecords {
        PHILO_STAT = QS_USER,
        TABLE_STAT
    };
    static uint8_t const l_onDialogGUI = 0U;
#endif

// Public-scope objects ------------------------------------------------------
QActive * const AO_Table = &l_table;                    // "opaque" AO pointer


// GUI definition ============================================================
static WM_HWIN l_hDlg;
static WM_CALLBACK *l_cb_WM_HBKWIN;

static const GUI_WIDGET_CREATE_INFO l_dialog[] = {
    { &FRAMEWIN_CreateIndirect, "Dining Philosopher Problem",
        0,  30,  30, 260, 180, FRAMEWIN_CF_MOVEABLE },
    { &TEXT_CreateIndirect, "Philosopher 0",
        GUI_ID_TEXT9,  50,  10, 0, 0, TEXT_CF_LEFT },
    { &TEXT_CreateIndirect, "Philosopher 1",
        GUI_ID_TEXT9,  50,  30, 0, 0, TEXT_CF_LEFT },
    { &TEXT_CreateIndirect, "Philosopher 2",
        GUI_ID_TEXT9,  50,  50, 0, 0, TEXT_CF_LEFT },
    { &TEXT_CreateIndirect, "Philosopher 3",
        GUI_ID_TEXT9,  50,  70, 0, 0, TEXT_CF_LEFT },
    { &TEXT_CreateIndirect, "Philosopher 4",
        GUI_ID_TEXT9,  50,  90, 0, 0, TEXT_CF_LEFT },
    { &TEXT_CreateIndirect, "Table",
        GUI_ID_TEXT9,  50, 110, 0, 0, TEXT_CF_LEFT },

    { &TEXT_CreateIndirect, "thinking",
        GUI_ID_TEXT0, 130,  10, 0, 0, TEXT_CF_LEFT },
    { &TEXT_CreateIndirect, "thinking",
        GUI_ID_TEXT1, 130,  30, 0, 0, TEXT_CF_LEFT },
    { &TEXT_CreateIndirect, "thinking",
        GUI_ID_TEXT2, 130,  50, 0, 0, TEXT_CF_LEFT },
    { &TEXT_CreateIndirect, "thinking",
        GUI_ID_TEXT3, 130,  70, 0, 0, TEXT_CF_LEFT },
    { &TEXT_CreateIndirect, "thinking",
        GUI_ID_TEXT4, 130,  90, 0, 0, TEXT_CF_LEFT },
    { &TEXT_CreateIndirect, "serving",
        GUI_ID_TEXT5, 130, 110, 0, 0, TEXT_CF_LEFT },

    { &BUTTON_CreateIndirect,"PAUSE",
        GUI_ID_BUTTON0,    160, 130, 80, 30 }
};

   //..........................................................................*/
static void onMainWndGUI(WM_MESSAGE* pMsg) {
    switch (pMsg->MsgId) {
        case WM_PAINT: {
            GUI_SetBkColor(GUI_GRAY);
            GUI_Clear();
            GUI_SetColor(GUI_BLACK);
            GUI_SetFont(&GUI_Font24_ASCII);
            GUI_DispStringHCenterAt("Dining Philosophers - Demo", 160, 5);
            break;
        }
        default: {
            WM_DefaultProc(pMsg);
            break;
        }
    }
}
   //..........................................................................*/
static void onDialogGUI(WM_MESSAGE * pMsg) {
    switch (pMsg->MsgId) {
        case WM_INIT_DIALOG: {
            break;
        }
        case WM_NOTIFY_PARENT: {
            switch (pMsg->Data.v) {
                case WM_NOTIFICATION_RELEASED: {     // react only if released */
                    switch (WM_GetId(pMsg->hWinSrc)) {
                        case GUI_ID_BUTTON0: {
                                        // static PAUSE event for the Table AO */
                            static QEvent const pauseEvt = { PAUSE_SIG, 0 };
                            AO_Table->POST(&pauseEvt, &l_onDialogGUI);
                            break;
                        }
                    }
                    break;
                }
            }
            break;
        }
        default: {
            WM_DefaultProc(pMsg);
            break;
        }
    }
}
   //..........................................................................*/
static void displyPhilStat(uint8_t n, char const *stat) {
    TEXT_SetText(WM_GetDialogItem(l_hDlg, GUI_ID_TEXT0 + n), stat);
    WM_Exec();                    // update the screen and invoke WM callbacks */

    QS_BEGIN(PHILO_STAT, AO_Philo[n])     // application-specific record begin */
        QS_U8(1, n);                                     // Philosopher number */
        QS_STR(stat);                                    // Philosopher status */
    QS_END()
}
   //..........................................................................*/
static void displyTableStat(char const *stat) {
    TEXT_SetText(WM_GetDialogItem(l_hDlg, GUI_ID_TEXT5), stat);
    WM_Exec();                    // update the screen and invoke WM callbacks */

    QS_BEGIN(TABLE_STAT, AO_Table)        // application-specific record begin */
        QS_STR(stat);                                    // Philosopher status */
    QS_END()
}

//............................................................................
Table::Table() : QActive((QStateHandler)&Table::initial) {
    uint8_t n;
    for (n = 0; n < N_PHILO; ++n) {
        m_fork[n] = FREE;
        m_isHungry[n] = 0;
    }
}
//............................................................................
QState Table::initial(Table *me, QEvt const *) {

    QS_OBJ_DICTIONARY(&l_table);
    QS_FUN_DICTIONARY(&QHsm::top);
    QS_FUN_DICTIONARY(&Table::initial);
    QS_FUN_DICTIONARY(&Table::serving);

    QS_SIG_DICTIONARY(DONE_SIG,      0);                     // global signals
    QS_SIG_DICTIONARY(EAT_SIG,       0);
    QS_SIG_DICTIONARY(PAUSE_SIG, 0);

    QS_SIG_DICTIONARY(HUNGRY_SIG,    me);             // signal just for Table

    GUI_Init();                                 // initialize the embedded GUI

    me->subscribe(DONE_SIG);
    me->subscribe(PAUSE_SIG);

    return Q_TRAN(&Table::ready);
}
//............................................................................
QState Table::ready(Table *me, QEvt const *e) {
    switch (e->sig) {
        case Q_ENTRY_SIG: {
            l_cb_WM_HBKWIN = WM_SetCallback(WM_HBKWIN, &onMainWndGUI);
                            // create the diaglog box and return right away...
            l_hDlg = GUI_CreateDialogBox(l_dialog, GUI_COUNTOF(l_dialog),
                                         &onDialogGUI, 0, 0, 0);
            return Q_HANDLED();
        }
        case Q_EXIT_SIG: {
            GUI_EndDialog(l_hDlg, 0);
            WM_SetCallback(WM_HBKWIN, l_cb_WM_HBKWIN);
            return Q_HANDLED();
        }
        case Q_INIT_SIG: {
            return Q_TRAN(&Table::serving);
        }

        case MOUSE_CHANGE_SIG: {         // mouse change (move or click) event
            GUI_PID_STATE mouse;
            mouse.x = ((MouseEvt const *)e)->xPos;
            mouse.y = ((MouseEvt const *)e)->yPos;
            mouse.Pressed = ((MouseEvt const *)e)->buttonStates;

            GUI_PID_StoreState(&mouse);   // update the state of the Mouse PID

            WM_Exec();            // update the screen and invoke WM callbacks
            return Q_HANDLED();
        }

        // ... hardkey events ...
        case KEY_LEFT_REL_SIG: {                      // hardkey LEFT released
            WM_MoveWindow(l_hDlg, -5, 0);
            WM_Exec();            // update the screen and invoke WM callbacks
            return Q_HANDLED();
        }
        case KEY_RIGHT_REL_SIG: {                    // hardkey RIGHT released
            WM_MoveWindow(l_hDlg, 5, 0);
            WM_Exec();            // update the screen and invoke WM callbacks
            return Q_HANDLED();
        }
        case KEY_DOWN_REL_SIG: {                      // hardkey DOWN released
            WM_MoveWindow(l_hDlg, 0, 5);
            WM_Exec();            // update the screen and invoke WM callbacks
            return Q_HANDLED();
        }
        case KEY_UP_REL_SIG: {                          // hardkey UP released
            WM_MoveWindow(l_hDlg, 0, -5);
            WM_Exec();            // update the screen and invoke WM callbacks
            return Q_HANDLED();
        }
    }
    return Q_SUPER(&QHsm::top);
}
//............................................................................
QState Table::serving(Table *me, QEvt const *e) {
    uint8_t n, m;
    TableEvt *pe;

    switch (e->sig) {
        case Q_ENTRY_SIG: {
            displyTableStat("serving");
            for (n = 0; n < N_PHILO; ++n) {      // give permissions to eat...
                if (me->m_isHungry[n]
                    && (me->m_fork[LEFT(n)] == FREE)
                        && (me->m_fork[n] == FREE))
                {
                    me->m_fork[LEFT(n)] = me->m_fork[n] = USED;
                    pe = Q_NEW(TableEvt, EAT_SIG);
                    pe->philoNum = n;
                    QF::PUBLISH(pe, me);
                    me->m_isHungry[n] = 0;
                    displyPhilStat(n, "eating  ");
                }
            }
            return Q_HANDLED();
        }
        case HUNGRY_SIG: {
            n = ((TableEvt *)e)->philoNum;
            Q_ASSERT(n < N_PHILO && !me->m_isHungry[n]);
            displyPhilStat(n, "hungry  ");
            m = LEFT(n);
            if (me->m_fork[m] == FREE && me->m_fork[n] == FREE) {
                me->m_fork[m] = me->m_fork[n] = USED;
                pe = Q_NEW(TableEvt, EAT_SIG);
                pe->philoNum = n;
                QF::PUBLISH(pe, me);
                displyPhilStat(n, "eating  ");
            }
            else {
                me->m_isHungry[n] = 1;
            }
            return Q_HANDLED();
        }
        case DONE_SIG: {
            n = ((TableEvt *)e)->philoNum;
            Q_ASSERT(n < N_PHILO);
            displyPhilStat(n, "thinking");
            me->m_fork[LEFT(n)] = me->m_fork[n] = FREE;
            m = RIGHT(n);                          // check the right neighbor
            if (me->m_isHungry[m] && me->m_fork[m] == FREE) {
                me->m_fork[n] = me->m_fork[m] = USED;
                me->m_isHungry[m] = 0;
                pe = Q_NEW(TableEvt, EAT_SIG);
                pe->philoNum = m;
                QF::PUBLISH(pe, me);
                displyPhilStat(m, "eating  ");
            }
            m = LEFT(n);                            // check the left neighbor
            n = LEFT(m);
            if (me->m_isHungry[m] && me->m_fork[n] == FREE) {
                me->m_fork[m] = me->m_fork[n] = USED;
                me->m_isHungry[m] = 0;
                pe = Q_NEW(TableEvt, EAT_SIG);
                pe->philoNum = m;
                QF::PUBLISH(pe, me);
                displyPhilStat(m, "eating  ");
            }
            return Q_HANDLED();
        }
        case PAUSE_SIG:                             // "Toggle" button pressed
        case KEY_CENTER_PRESS_SIG: {                 // hardkey CENTER pressed
            return Q_TRAN(&Table::paused);
        }
    }
    return Q_SUPER(&Table::ready);
}
//............................................................................
QState Table::paused(Table *me, QEvt const *e) {
    uint8_t n;

    switch (e->sig) {
        case Q_ENTRY_SIG: {
            displyTableStat("paused");
            return Q_HANDLED();
        }
        case HUNGRY_SIG: {
            n = ((TableEvt *)e)->philoNum;
            Q_ASSERT(n < N_PHILO && !me->m_isHungry[n]);
            displyPhilStat(n, "hungry  ");
            me->m_isHungry[n] = 1;
            return Q_HANDLED();
        }
        case DONE_SIG: {
            n = ((TableEvt *)e)->philoNum;
            Q_ASSERT(n < N_PHILO);
            displyPhilStat(n, "thinking");
            me->m_fork[LEFT(n)] = me->m_fork[n] = FREE;
            return Q_HANDLED();
        }
        case PAUSE_SIG:                             // "Toggle" button pressed
        case KEY_CENTER_REL_SIG: {                  // hardkey CENTER released
            return Q_TRAN(&Table::serving);
        }
    }
    return Q_SUPER(&Table::ready);
}
