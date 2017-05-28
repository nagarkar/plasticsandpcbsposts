//****************************************************************************
// Model: Uart.qm
// File:  Uart/UartIn.cpp
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
//${Uart::Uart::UartIn.cpp} ..................................................
#include "UartIn.h"
#include "qpcpp.h"
#include "active_events.h"
#include "active_pipe.h"
#include "active_log.h"
#include "bsp.h"

Q_DEFINE_THIS_MODULE("Uart In")

using namespace QP;
using namespace StdEvents;

namespace AOs {


#if ((QP_VERSION < 580) || (QP_VERSION != ((QP_RELEASE^4294967295U) % 0x3E8)))
#error qpcpp version 5.8.0 or higher required
#endif

//${Uart::UartIn} ............................................................
//${Uart::UartIn::UartIn} ....................................................
UartIn::UartIn(
    QP::QActive * owner,
    Fifo * fifo,
    USART_HANDLE_TYPE_DEF * devUart)
  : ASM(UART_IN_ACTIVE_TIMER_SIG, (QStateHandler)&UartIn::initial, owner, "UartIn")
    , m_fifo(fifo)
    , m_devUart(devUart)
    , m_dataReady(false)
{}

//${Uart::UartIn::DmaDoneCallback} ...........................................
void UartIn::DmaDoneCallback() {
    static uint16_t counter = 0;
    Evt *evt = new Evt(UART_IN_DMA_RECV_SIG, counter++);
    QF::PUBLISH(evt, 0);
}
//${Uart::UartIn::DmaHalfDoneCallback} .......................................
void UartIn::DmaHalfDoneCallback() {
    static uint16_t counter = 0;
    Evt *evt = new Evt(UART_IN_DMA_RECV_SIG, counter++);
    QF::PUBLISH(evt, 0);
}
//${Uart::UartIn::DmaDataReadyCallback} ......................................
void UartIn::DmaDataReadyCallback() {
    static uint16_t counter = 0;
    Evt *evt = new Evt(UART_IN_DATA_RDY_SIG, counter++);
    QF::PUBLISH(evt, 0);
}
//${Uart::UartIn::SM} ........................................................
QP::QState UartIn::initial(UartIn * const me, QP::QEvt const * const e) {
    // ${Uart::UartIn::SM::initial}
    return Q_TRAN(&Root);
}
//${Uart::UartIn::SM::Root} ..................................................
QP::QState UartIn::Root(UartIn * const me, QP::QEvt const * const e) {
    QP::QState status_;
    switch (e->sig) {
        // ${Uart::UartIn::SM::Root}
        case Q_ENTRY_SIG: {
            LOG_EVENT(e);
            status_ = Q_HANDLED();
            break;
        }
        // ${Uart::UartIn::SM::Root}
        case Q_EXIT_SIG: {
            LOG_EVENT(e);
            status_ = Q_HANDLED();
            break;
        }
        // ${Uart::UartIn::SM::Root::initial}
        case Q_INIT_SIG: {
            LOG_EVENT(e);
            status_ = Q_TRAN(&Stopped);
            break;
        }
        // ${Uart::UartIn::SM::Root::UART_IN_START_REQ}
        case UART_IN_START_REQ_SIG: {
            LOG_EVENT(e);
            me->PublishConfirmationWithInvalidState(
                EVT_CAST(*e),
                UART_IN_START_CFM_SIG);
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_SUPER(&top);
            break;
        }
    }
    return status_;
}
//${Uart::UartIn::SM::Root::Stopped} .........................................
QP::QState UartIn::Stopped(UartIn * const me, QP::QEvt const * const e) {
    QP::QState status_;
    switch (e->sig) {
        // ${Uart::UartIn::SM::Root::Stopped}
        case Q_ENTRY_SIG: {
            LOG_EVENT(e);
            status_ = Q_HANDLED();
            break;
        }
        // ${Uart::UartIn::SM::Root::Stopped}
        case Q_EXIT_SIG: {
            LOG_EVENT(e);
            status_ = Q_HANDLED();
            break;
        }
        // ${Uart::UartIn::SM::Root::Stopped::UART_IN_START_REQ}
        case UART_IN_START_REQ_SIG: {
            LOG_EVENT(e);
            me->m_fifo->Reset();
            me->PublishConfirmation(
                EVT_CAST(*e),
                UART_IN_START_CFM_SIG);
            status_ = Q_TRAN(&Started);
            break;
        }
        // ${Uart::UartIn::SM::Root::Stopped::UART_IN_STOP_REQ}
        case UART_IN_STOP_REQ_SIG: {
            LOG_EVENT(e);
            me->PublishConfirmation(
                EVT_CAST(*e),
                UART_IN_STOP_CFM_SIG);
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
//${Uart::UartIn::SM::Root::Started} .........................................
QP::QState UartIn::Started(UartIn * const me, QP::QEvt const * const e) {
    QP::QState status_;
    switch (e->sig) {
        // ${Uart::UartIn::SM::Root::Started}
        case Q_ENTRY_SIG: {
            LOG_EVENT(e);
            status_ = Q_HANDLED();
            break;
        }
        // ${Uart::UartIn::SM::Root::Started}
        case Q_EXIT_SIG: {
            LOG_EVENT(e);
            status_ = Q_HANDLED();
            break;
        }
        // ${Uart::UartIn::SM::Root::Started::initial}
        case Q_INIT_SIG: {
            LOG_EVENT(e);
            status_ = Q_TRAN(&Normal);
            break;
        }
        // ${Uart::UartIn::SM::Root::Started::UART_IN_STOP_REQ}
        case UART_IN_STOP_REQ_SIG: {
            LOG_EVENT(e);
            me->PublishConfirmation(
                EVT_CAST(*e),
                UART_IN_STOP_CFM_SIG);
            status_ = Q_TRAN(&Stopped);
            break;
        }
        default: {
            status_ = Q_SUPER(&Root);
            break;
        }
    }
    return status_;
}
//${Uart::UartIn::SM::Root::Started::Failed} .................................
QP::QState UartIn::Failed(UartIn * const me, QP::QEvt const * const e) {
    QP::QState status_;
    switch (e->sig) {
        // ${Uart::UartIn::SM::Root::Started::Failed}
        case Q_ENTRY_SIG: {
            LOG_EVENT(e);
            status_ = Q_HANDLED();
            break;
        }
        // ${Uart::UartIn::SM::Root::Started::Failed}
        case Q_EXIT_SIG: {
            LOG_EVENT(e);
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_SUPER(&Started);
            break;
        }
    }
    return status_;
}
//${Uart::UartIn::SM::Root::Started::Normal} .................................
QP::QState UartIn::Normal(UartIn * const me, QP::QEvt const * const e) {
    QP::QState status_;
    switch (e->sig) {
        // ${Uart::UartIn::SM::Root::Started::Normal}
        case Q_ENTRY_SIG: {
            LOG_EVENT(e);
            BSP_STATUS result;
            result = (BSP_STATUS)BSP_UART_RECEIVE_DMA(me->m_devUart, (uint8_t *)me->m_fifo->GetAddr(0), me->m_fifo->GetBufSize());
            Q_ASSERT(result == BSP_OK);
            status_ = Q_HANDLED();
            break;
        }
        // ${Uart::UartIn::SM::Root::Started::Normal}
        case Q_EXIT_SIG: {
            LOG_EVENT(e);
            BSP_UART_DMA_STOP(me->m_devUart);
            BSP_DisableRxInt(me->m_devUart);
            status_ = Q_HANDLED();
            break;
        }
        // ${Uart::UartIn::SM::Root::Started::Normal::initial}
        case Q_INIT_SIG: {
            LOG_EVENT(e);
            status_ = Q_TRAN(&Inactive);
            break;
        }
        // ${Uart::UartIn::SM::Root::Started::Normal::UART_IN_DMA_RECV}
        case UART_IN_DMA_RECV_SIG: {
            LOG_EVENT(e);
            uint32_t dmaRemainCount = BSP_GetCountOfRemainingDmaXferUnits(me->m_devUart);
            uint32_t dmaCurrIndex = me->m_fifo->GetBufSize() - dmaRemainCount;
            uint32_t dmaRxCount = me->m_fifo->GetDiff(dmaCurrIndex, me->m_fifo->GetWriteIndex());
            if (dmaRxCount > 0) {
                if (dmaRxCount > me->m_fifo->GetAvailCount()) {
                    me->PostToOwnerLifo(UART_IN_OVERFLOW_SIG);
                } else {
                    me->m_fifo->IncWriteIndex(dmaRxCount);
                    me->Publish(UART_IN_DATA_IND_SIG);
                }
            }
            status_ = Q_HANDLED();
            break;
        }
        // ${Uart::UartIn::SM::Root::Started::Normal::UART_IN_OVERFLOW}
        case UART_IN_OVERFLOW_SIG: {
            LOG_EVENT(e);
            status_ = Q_TRAN(&Failed);
            break;
        }
        default: {
            status_ = Q_SUPER(&Started);
            break;
        }
    }
    return status_;
}
//${Uart::UartIn::SM::Root::Started::Normal::Active} .........................
QP::QState UartIn::Active(UartIn * const me, QP::QEvt const * const e) {
    QP::QState status_;
    switch (e->sig) {
        // ${Uart::UartIn::SM::Root::Started::Normal::Active}
        case Q_ENTRY_SIG: {
            LOG_EVENT(e);
            me->m_timer.armX(UART_IN_ACTIVE_TIMER_MS);
            BSP_EnableRxInt(me->m_devUart);
            me->m_dataReady = false;
            status_ = Q_HANDLED();
            break;
        }
        // ${Uart::UartIn::SM::Root::Started::Normal::Active}
        case Q_EXIT_SIG: {
            LOG_EVENT(e);
            me->m_timer.disarm();
            status_ = Q_HANDLED();
            break;
        }
        // ${Uart::UartIn::SM::Root::Started::Normal::Active::UART_IN_DATA_RDY}
        case UART_IN_DATA_RDY_SIG: {
            LOG_EVENT(e);
            me->m_dataReady = true;
            status_ = Q_HANDLED();
            break;
        }
        // ${Uart::UartIn::SM::Root::Started::Normal::Active::UART_IN_ACTIVE_TIMER}
        case UART_IN_ACTIVE_TIMER_SIG: {
            LOG_EVENT(e);
            // ${Uart::UartIn::SM::Root::Started::Normal::Active::UART_IN_ACTIVE_T~::[DRDY=false]}
            if (me->m_dataReady == false) {
                me->Publish(UART_IN_DMA_RECV_SIG);
                status_ = Q_TRAN(&Inactive);
            }
            // ${Uart::UartIn::SM::Root::Started::Normal::Active::UART_IN_ACTIVE_T~::[DRDY=true]}
            else if (me->m_dataReady == true) {
                status_ = Q_TRAN(&Active);
            }
            else {
                status_ = Q_UNHANDLED();
            }
            break;
        }
        default: {
            status_ = Q_SUPER(&Normal);
            break;
        }
    }
    return status_;
}
//${Uart::UartIn::SM::Root::Started::Normal::Inactive} .......................
QP::QState UartIn::Inactive(UartIn * const me, QP::QEvt const * const e) {
    QP::QState status_;
    switch (e->sig) {
        // ${Uart::UartIn::SM::Root::Started::Normal::Inactive}
        case Q_ENTRY_SIG: {
            LOG_EVENT(e);
            BSP_EnableRxInt(me->m_devUart);
            status_ = Q_HANDLED();
            break;
        }
        // ${Uart::UartIn::SM::Root::Started::Normal::Inactive}
        case Q_EXIT_SIG: {
            LOG_EVENT(e);
            status_ = Q_HANDLED();
            break;
        }
        // ${Uart::UartIn::SM::Root::Started::Normal::Inactive::UART_IN_DATA_RDY}
        case UART_IN_DATA_RDY_SIG: {
            status_ = Q_TRAN(&Active);
            break;
        }
        default: {
            status_ = Q_SUPER(&Normal);
            break;
        }
    }
    return status_;
}

} // namespace AOs