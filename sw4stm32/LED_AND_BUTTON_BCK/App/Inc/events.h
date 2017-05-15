#ifndef EVENTS_H
#define EVENTS_H

#include "qpcpp.h"

using namespace QP;

enum {
    TIM_2_TIMEOUT_SIG = Q_USER_SIG,
    BUTTON_1_PRESS_SIG,
    MAX_SIG
};

class ButtonPressEvt : public QP::QEvt {};

class TimeoutEvt : public QP::QEvt {};


#endif
