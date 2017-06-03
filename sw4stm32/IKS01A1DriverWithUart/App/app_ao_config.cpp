#include "app_ao_config.h"
#include "active_config.h"
#include "active_events.h"
#include "active_log.h"
#include "UartIn.h"
#include "UartOut.h"
#include "UartAct.h"
#include "UartCommander.h"
#include "x_nucleo_iks01a1_accelero.h"
#include "AO_IKS01A1.h"
#include "ABumpDetector.h"
#include "CircularBuffer.h"
#include "macros.h"
#include "bsp.h"

#define MY_GPIO_PIN_5                 ((uint16_t)0x0020)  /* Pin 5 selected    */

using namespace AOs;
using namespace QP;
using namespace StdDataStruct;

using namespace IKS01A1;
using namespace SigProc;

/*** DEFINE SIGNALS **/
SMARTENUM_DEFINE_NAMES(Signal, SIG_LIST)
SMARTENUM_DEFINE_GET_VALUE_FROM_STRING(Signal, SIG_LIST)


/** QP CONFIGURATION **/

static UartAct uart2Act(&huart2);
static UartCommander commander(&uart2Act.GetInFifo());

//static void *LSM6DS0_X_0_handle = NULL;
static AO_IKS01A1 accel(20 /* Milliseconds */);
static BumpDetector bumper(100, &accel.m_circbuf, 15);

QP::QSubscrList subscrSto[MAX_PUB_SIG];
extern "C" {

/** PRIVATE FUNCTION PROTOTYPES **/
static void App_UART_DMATransmitCplt(DMA_HandleTypeDef *hdma);
/** End **/


void QP_StartActiveObjectsAndPublishBootTimeEvents(void) {

	uart2Act.Start(PRIO_UART2_ACT);
	QF::PUBLISH(new Evt(UART_ACT_START_REQ_SIG), NULL);

	commander.Start(PRIO_UART2_COMMANDER);
	QF::PUBLISH(new Evt(UART_COMMANDER_START_REQ_SIG), NULL);

	QF::PUBLISH(new Evt(UART_COMMANDER_SHOW_USAGE_SIG), NULL);

	accel.Start(PRIO_IKS01A1_PRIO);
	QF::PUBLISH(new Evt(IKS01A1_ACC_START_REQ_SIG), NULL);

	bumper.Start(PRIO_BUMPER);
	QF::PUBLISH(new Evt(ABUMP_DET_START_REQ_SIG), NULL);
}

void QP_AllocateSubscriberLists(void) {
	QF::psInit(subscrSto, Q_DIM(subscrSto)); // init publish-subscribe
}

/** END QP CONFIGURATION **/

/** UART COMMANDER PLUGS 		**/
const char * UART_CMDR_GetUsage() {
	return "Usage: \r\n u: Print Usage \r\n t: Stop UartAct \r\n s: Start UartAct \r\n a: Print Accel Data";
}

void UART_CMDR_ProcessCommand(char command) {
	switch(command) {
		case 's':
			QF::PUBLISH(new Evt(UART_ACT_START_REQ_SIG), NULL);
			break;
		case 't':
			QF::PUBLISH(new Evt(UART_ACT_STOP_REQ_SIG), NULL);
			break;
		case 'u':
			break;
		case 'a':
			accel.m_xPrintStream = !accel.m_xPrintStream;
			break;
		case 'l':
			TOGGLE_EVENT_LOGGING();
			break;
		case 'i':
			bumper.m_bumpThreshold++;
			PRINT("Bumper threshold now %d.\r\n", (int)(bumper.m_bumpThreshold));
			break;
		case 'd':
			bumper.m_bumpThreshold--;
			PRINT("Bumper threshold now %d.\r\n", (int)(bumper.m_bumpThreshold));
			break;
		default :
			PRINT("Unknown Command. Type 'u' to print usage.\r\n");
	}
}
/** UART COMMANDER PLUGS END 	**/

/** BSP OVERRIDES **/

void BSP_OVERRIDE_UART_CALLBACKS(USART_HANDLE_TYPE_DEF *uart) {
	uart->hdmatx->XferCpltCallback = App_UART_DMATransmitCplt;
}

static void App_UART_DMATransmitCplt(DMA_HandleTypeDef *hdma) {
  UART_HandleTypeDef* huart = ( UART_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;
  /* DMA Normal mode*/
  if((hdma->Instance->CR & DMA_SxCR_CIRC) == 0U)
  {
	huart->TxXferCount = 0U;

	/* Disable the DMA transfer for transmit request by setting the DMAT bit
	   in the UART CR3 register */
	CLEAR_BIT(huart->Instance->CR3, USART_CR3_DMAT);

	/* Enable the UART Transmit Complete Interrupt */
	//SET_BIT(huart->Instance->CR1, USART_CR1_TCIE);
	huart->gState = HAL_UART_STATE_READY;
	HAL_UART_TxCpltCallback(huart);
  }
  /* DMA Circular mode */
  else
  {
	HAL_UART_TxCpltCallback(huart);
  }

}
// End BSP OVERRIDES
}
