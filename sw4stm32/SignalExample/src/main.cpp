/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "app_ao_config.h"
#include "smartenum.h"

SMARTENUM_DEFINE_NAMES(Signal, SIG_LIST)
SMARTENUM_DEFINE_GET_VALUE_FROM_STRING(Signal, SIG_LIST)

int main(void) {
	const char * evtName1 = SignalArray[MAX_PUB_SIG]; // "MAX_PUB_SIG"
	const char * evtName2 = SignalArray[UART_ACT_DONE_SIG]; // "UART_ACT_DONE_SIG"
}
