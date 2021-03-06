/*
 * app_ao_config.h
 *
 *  Created on: May 19, 2017
 *      Author: chinm_000
 */
#ifndef APP_AO_CONFIG_H_
#define APP_AO_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "qpcpp.h"
#include "active_enum.h"

#define _ACTIVE_LOG_ENABLED_

using namespace QP;

#define SIG_LIST(m)  \
	m(Signal, DUMMY_NULL)    \
	m(Signal, ENTRY_SIG)    \
	m(Signal, EXIT_SIG)		\
	m(Signal, INIT_SIG)		\
	m(Signal, DONT_CARE_SIG = QP::Q_USER_SIG)		\
	\
	m(Signal, SYSTEM_START_REQ_SIG)    \
	m(Signal, USER_LED_START_REQ_SIG)    \
	m(Signal, USER_LED_START_CFM_SIG)    \
	m(Signal, USER_LED_STOP_REQ_SIG)    \
	m(Signal, USER_LED_STOP_CFM_SIG)    \
	m(Signal, USER_LED_ON_REQ_SIG)    \
	m(Signal, USER_LED_ON_CFM_SIG)    \
	m(Signal, USER_LED_OFF_REQ_SIG)    \
	m(Signal, USER_LED_OFF_CFM_SIG)    \
	m(Signal, USER_LED_STATE_TIMER_SIG)    \
	m(Signal, USER_LED_DONE_SIG)    \
	\
	m(Signal, UART_ACT_START_REQ_SIG)    \
	m(Signal, UART_ACT_START_CFM_SIG)    \
	m(Signal, UART_ACT_STOP_REQ_SIG)    \
	m(Signal, UART_ACT_STOP_CFM_SIG)    \
	m(Signal, UART_ACT_FAIL_IND_SIG)    \
	m(Signal, UART_ACT_STATE_TIMER_SIG)    \
	m(Signal, UART_ACT_START_SIG)    \
	m(Signal, UART_ACT_DONE_SIG)    \
	m(Signal, UART_ACT_FAIL_SIG)    \
	\
	m(Signal, UART_OUT_START_REQ_SIG)    \
	m(Signal, UART_OUT_START_CFM_SIG)    \
	m(Signal, UART_OUT_STOP_REQ_SIG)    \
	m(Signal, UART_OUT_STOP_CFM_SIG)    \
	m(Signal, UART_OUT_FAIL_IND_SIG)    \
	m(Signal, UART_OUT_WRITE_REQ_SIG)    \
	m(Signal, UART_OUT_WRITE_CFM_SIG)    \
	m(Signal, UART_OUT_EMPTY_IND_SIG)    \
	m(Signal, UART_OUT_ACTIVE_TIMER_SIG)    \
	m(Signal, UART_OUT_DONE_SIG)    \
	m(Signal, UART_OUT_DMA_DONE_SIG)    \
	m(Signal, UART_OUT_CONTINUE_SIG)    \
	m(Signal, UART_OUT_HW_FAIL_SIG)    \
	\
	m(Signal, UART_IN_START_REQ_SIG)    \
	m(Signal, UART_IN_START_CFM_SIG)    \
	m(Signal, UART_IN_STOP_REQ_SIG)    \
	m(Signal, UART_IN_STOP_CFM_SIG)    \
	m(Signal, UART_IN_CHAR_IND_SIG)    \
	m(Signal, UART_IN_DATA_IND_SIG)    \
	m(Signal, UART_IN_FAIL_IND_SIG)    \
	m(Signal, UART_IN_ACTIVE_TIMER_SIG)    \
	m(Signal, UART_IN_DONE_SIG)    \
	m(Signal, UART_IN_DATA_RDY_SIG)    \
	m(Signal, UART_IN_DMA_RECV_SIG)    \
	m(Signal, UART_IN_OVERFLOW_SIG)    \
	m(Signal, UART_IN_HW_FAIL_SIG)    \
	\
	m(Signal, UART_COMMANDER_STOP_REQ_SIG)    \
	m(Signal, UART_COMMANDER_START_REQ_SIG)    \
	m(Signal, UART_COMMANDER_STOP_CFM_SIG)    \
	m(Signal, UART_COMMANDER_START_CFM_SIG)    \
	m(Signal, UART_COMMANDER_SHOW_USAGE_SIG)    \
	m(Signal, MAX_PUB_SIG)

SMARTENUM_DEFINE_ENUM(Signal, SIG_LIST)
SMARTENUM_DECLARE_NAMES(Signal, SIG_LIST)
SMARTENUM_DECLARE_GET_VALUE_FROM_STRING(Signal, SIG_LIST)

enum SignalAliases {
	UART_COMMANDER_CMD_IND_SIG = UART_IN_DATA_IND_SIG
};

// Higher value corresponds to higher priority.
// The maximum priority is defined in qf_port.h as QF_MAX_ACTIVE (32)
enum
{
	PRIO_UART2_COMMANDER  = 11, //30,
    PRIO_UART2_ACT  = 10, //30,
	//PRIO_CONSOLE    = 28,
	//PRIO_SYSTEM     = 26,
	//PRIO_USER_BTN   = 24,
    PRIO_USER_LED   = 22,
	//PRIO_SAMPLE     = 5
};

#ifdef __cplusplus
}
#endif

#endif /* AO_CONFIG_H_ */
