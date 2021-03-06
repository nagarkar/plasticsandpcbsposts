//****************************************************************************
// Model: AO_IKS01A1.qm
// File:  IKS01A1/AO_IKS01A1.h
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
//${IKS01A1::IKS01A1::AO_IKS01A1.h} ..........................................
#ifndef _AO_IKS01A1_H
#define _AO_IKS01A1_H

#include "qpcpp.h"
#include "bsp.h"
#include "active_events.h"
#include "active_log.h"
#include "x_nucleo_iks01a1_accelero.h"
#include "CircularBuffer.h"
#include "stm32f4xx_hal.h"

//// CONSUMES EVENTS /////////////////////////
//    IKS01A1_ACC_START_REQ_SIG
//    IKS01A1_ACC_STOP_REQ_SIG
//// PRODUCES EVENTS /////////////////////////
//    IKS01A1_ACC_START_CFM_SIG
//    IKS01A1_ACC_COMPONENT_FAILED_SIG
//    IKS01A1_ACC_STOP_CFM_SIG
//////////////////////////////////////////////

using namespace StdDataStruct;

namespace IKS01A1 {
class SensorAxesBufferElement : public CircularBufferElement {
public:
    SensorAxes_t axes;
    SensorAxesBufferElement(const SensorAxesBufferElement& el)
        : CircularBufferElement(el.timestamp), axes(el.axes) {}
    SensorAxesBufferElement() : CircularBufferElement(HAL_GetTick()) {}
    SensorAxesBufferElement(uint32_t ts): CircularBufferElement(ts) {}
    SensorAxesBufferElement(SensorAxes_t axes) : CircularBufferElement(), axes(axes) {}
    SensorAxesBufferElement(SensorAxes_t axes, uint32_t timestamp):
        CircularBufferElement(timestamp), axes(axes) {}
    virtual void print(void) override;
};

} // namespace;

namespace IKS01A1 {


#if ((QP_VERSION < 580) || (QP_VERSION != ((QP_RELEASE^4294967295U) % 0x3E8)))
#error qpcpp version 5.8.0 or higher required
#endif

//${IKS01A1::AO_IKS01A1} .....................................................
class AO_IKS01A1 : public StdEvents::AO {
protected:
    void * m_handle;
    uint32_t const m_dataCollectionInterval;
    enum { ACC_BUFFER_SIZE = 1000 };
    SensorAxesBufferElement m_buffer[ACC_BUFFER_SIZE];

public:
    CircularBuffer<SensorAxesBufferElement> m_circbuf;
    DrvStatusTypeDef m_xInitStatus = COMPONENT_ERROR;
    bool m_xPrintStream;

public:
    AO_IKS01A1(uint32_t interval);
    void armTimer();

protected:
    static QP::QState initial(AO_IKS01A1 * const me, QP::QEvt const * const e);
    static QP::QState Root(AO_IKS01A1 * const me, QP::QEvt const * const e);
    static QP::QState Stopped(AO_IKS01A1 * const me, QP::QEvt const * const e);
    static QP::QState Started(AO_IKS01A1 * const me, QP::QEvt const * const e);
    static QP::QState CollectingData(AO_IKS01A1 * const me, QP::QEvt const * const e);
    static QP::QState Failed(AO_IKS01A1 * const me, QP::QEvt const * const e);
};

} // namespace IKS01A1

#endif // _AO_IKS01A1_H
