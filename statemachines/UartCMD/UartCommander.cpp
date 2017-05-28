//****************************************************************************
// Model: UartCommander.qm
// File:  UartCMD/UartCommander.cpp
//
// This code has been generated by QM tool (see state-machine.com/qm).
// DO NOT EDIT THIS FILE MANUALLY. All your changes will be lost.
//
// This program is open source software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
// for more details.
//****************************************************************************
//${UartCMD::UartCommander.cpp} ..............................................
#include "qpcpp.h"
#include "UartCommander.h"

using namespace QP;
using namespace StdEvents;

void _UartCommanderProcessCommand(char command) {
    if (command == 'u') {
        PRINT("%s\r\n", UART_CMDR_GetUsage());
    }
    PRINT("Processing %c\r\n", command);
    UART_CMDR_ProcessCommand(command);
}

namespace AOs {


#if ((QP_VERSION < 580) || (QP_VERSION != ((QP_RELEASE^4294967295U) % 0x3E8)))
#error qpcpp version 5.8.0 or higher required
#endif

//${UartCommander::UartCommander} ............................................
//${UartCommander::UartCommander::UartCommander} .............................
UartCommander::UartCommander(Fifo * characterFifo)
  : AO(DONT_CARE_SIG, Q_STATE_CAST(&initial), "Uart Commander")
  , m_fifo(characterFifo)
{}

//${UartCommander::UartCommander::SM} ........................................
QP::QState UartCommander::initial(UartCommander * const me, QP::QEvt const * const e) {
    // ${UartCommander::UartCommander::SM::initial}
    me->subscribe(UART_COMMANDER_STOP_REQ_SIG);
    me->subscribe(UART_COMMANDER_START_REQ_SIG);
    me->subscribe(UART_COMMANDER_CMD_IND_SIG);
    me->subscribe(UART_COMMANDER_SHOW_USAGE_SIG);
    return Q_TRAN(&Root);
}
//${UartCommander::UartCommander::SM::Root} ..................................
QP::QState UartCommander::Root(UartCommander * const me, QP::QEvt const * const e) {
    QP::QState status_;
    switch (e->sig) {
        // ${UartCommander::UartCommander::SM::Root}
        case Q_ENTRY_SIG: {
            LOG_EVENT(e);
            status_ = Q_HANDLED();
            break;
        }
        // ${UartCommander::UartCommander::SM::Root}
        case Q_EXIT_SIG: {
            LOG_EVENT(e);
            status_ = Q_HANDLED();
            break;
        }
        // ${UartCommander::UartCommander::SM::Root::initial}
        case Q_INIT_SIG: {
            LOG_EVENT(e);
            status_ = Q_TRAN(&Stopped);
            break;
        }
        default: {
            status_ = Q_SUPER(&top);
            break;
        }
    }
    return status_;
}
//${UartCommander::UartCommander::SM::Root::Stopped} .........................
QP::QState UartCommander::Stopped(UartCommander * const me, QP::QEvt const * const e) {
    QP::QState status_;
    switch (e->sig) {
        // ${UartCommander::UartCommander::SM::Root::Stopped}
        case Q_ENTRY_SIG: {
            LOG_EVENT(e);
            me->RecallDeferred();
            status_ = Q_HANDLED();
            break;
        }
        // ${UartCommander::UartCommander::SM::Root::Stopped}
        case Q_EXIT_SIG: {
            LOG_EVENT(e);
            status_ = Q_HANDLED();
            break;
        }
        // ${UartCommander::UartCommander::SM::Root::Stopped::UART_COMMANDER_START_REQ}
        case UART_COMMANDER_START_REQ_SIG: {
            LOG_EVENT(e);
            me->PublishConfirmation(
                EVT_CAST(*e),
                UART_COMMANDER_STOP_CFM_SIG);
            status_ = Q_TRAN(&Started);
            break;
        }
        // ${UartCommander::UartCommander::SM::Root::Stopped::UART_COMMANDER_CMD_IND,UART_COMM~}
        case UART_COMMANDER_CMD_IND_SIG: // intentionally fall through
        case UART_COMMANDER_SHOW_USAGE_SIG: {
            LOG_EVENT(e);
            me->Defer(e);
            status_ = Q_HANDLED();
            break;
        }
        // ${UartCommander::UartCommander::SM::Root::Stopped::UART_COMMANDER_STOP_REQ}
        case UART_COMMANDER_STOP_REQ_SIG: {
            LOG_EVENT(e);
            me->PublishConfirmation(
                EVT_CAST(*e),
                UART_COMMANDER_STOP_CFM_SIG);
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_SUPER(&Root);
            break;
        }
    }
    return status_;
}
//${UartCommander::UartCommander::SM::Root::Started} .........................
QP::QState UartCommander::Started(UartCommander * const me, QP::QEvt const * const e) {
    QP::QState status_;
    switch (e->sig) {
        // ${UartCommander::UartCommander::SM::Root::Started}
        case Q_ENTRY_SIG: {
            LOG_EVENT(e);
            me->RecallDeferred();
            status_ = Q_HANDLED();
            break;
        }
        // ${UartCommander::UartCommander::SM::Root::Started}
        case Q_EXIT_SIG: {
            LOG_EVENT(e);
            status_ = Q_HANDLED();
            break;
        }
        // ${UartCommander::UartCommander::SM::Root::Started::UART_COMMANDER_START_REQ}
        case UART_COMMANDER_START_REQ_SIG: {
            LOG_EVENT(e);
            me->PublishConfirmation(
                EVT_CAST(*e),
                UART_COMMANDER_START_CFM_SIG
            );
            status_ = Q_HANDLED();
            break;
        }
        // ${UartCommander::UartCommander::SM::Root::Started::UART_COMMANDER_CMD_IND}
        case UART_COMMANDER_CMD_IND_SIG: {
            LOG_EVENT(e);
            uint32_t count = me->m_fifo->GetUsedCount();
            while(count--) {
                uint8_t ch;
                me->m_fifo->Read(&ch, 1);
                PRINT("Command:%c\r\n", ch);
                _UartCommanderProcessCommand(ch);
            }
            status_ = Q_HANDLED();
            break;
        }
        // ${UartCommander::UartCommander::SM::Root::Started::UART_COMMANDER_STOP_REQ}
        case UART_COMMANDER_STOP_REQ_SIG: {
            LOG_EVENT(e);
            me->PublishConfirmation(
                EVT_CAST(*e),
                UART_COMMANDER_STOP_CFM_SIG);
            status_ = Q_TRAN(&Stopped);
            break;
        }
        // ${UartCommander::UartCommander::SM::Root::Started::UART_COMMANDER_SHOW_USAGE}
        case UART_COMMANDER_SHOW_USAGE_SIG: {
            LOG_EVENT(e);
            PRINT(UART_CMDR_GetUsage());
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_SUPER(&Root);
            break;
        }
    }
    return status_;
}

} // namespace AOs

// define other elements...