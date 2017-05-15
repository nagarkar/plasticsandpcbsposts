//****************************************************************************
// Model: LED_BUTTON_AND_INTERRUPT.qm
// File:  E:\repositories\plasticsandpcbsposts\sw4stm32\QPCPPWithStm32Cube\SM\Inc/UserLed.h
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
//${AOs::E:\repositories\~::UserLed.h} .......................................
#ifndef USERLED_H_
#define USERLED_H_

#include <stdio.h>
#include <stdlib.h>
#include "qpcpp.h"
#include "macros.h"

using namespace QP;

namespace AOs {


#if ((QP_VERSION < 580) || (QP_VERSION != ((QP_RELEASE^4294967295U) % 0x3E8)))
#error qpcpp version 5.8.0 or higher required
#endif

//${AOs::UserLed} ............................................................
class UserLed : public QP::QActive {
public:
    UserLed();

private:
    void LedOn();
    void LedOff();

protected:
    static QP::QState initial(UserLed * const me, QP::QEvt const * const e);
    static QP::QState ON(UserLed * const me, QP::QEvt const * const e);
    static QP::QState OFF(UserLed * const me, QP::QEvt const * const e);
};

} // namespace AOs

#endif
