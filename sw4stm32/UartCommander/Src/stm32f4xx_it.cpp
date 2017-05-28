/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"

/* USER CODE BEGIN 0 */
#include "qpcpp.h"
#include "UartIn.h"
#include "UartOut.h"
#include "bsp.h"

extern "C" {

using namespace AOs;

void USART2_IRQHandler_Override(void);
/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern UART_HandleTypeDef huart2;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart2_tx;

/******************************************************************************/
/*            Cortex-M4 Processor Interruption and Exception Handlers         */ 
/******************************************************************************/

/**
* @brief This function handles System tick timer.
*/
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
  /* USER CODE BEGIN SysTick_IRQn 1 */
  QXK_ISR_ENTRY();
  QP::QF::tickX_(0);
  QXK_ISR_EXIT();
  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/


/**
* @brief This function handles DMA1 stream5 global interrupt.
*/
void DMA1_Stream5_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream5_IRQn 0 */
	QXK_ISR_ENTRY();
  /* USER CODE END DMA1_Stream5_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart2_rx);
  /* USER CODE BEGIN DMA1_Stream5_IRQn 1 */
  QXK_ISR_EXIT();
  /* USER CODE END DMA1_Stream5_IRQn 1 */
}

/**
* @brief This function handles DMA1 stream6 global interrupt.
*/
void DMA1_Stream6_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream6_IRQn 0 */
	QXK_ISR_ENTRY();
	BSP_OVERRIDE_UART_CALLBACKS(&huart2);
  /* USER CODE END DMA1_Stream6_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart2_tx);
  /* USER CODE BEGIN DMA1_Stream6_IRQn 1 */
  QXK_ISR_EXIT();
  /* USER CODE END DMA1_Stream6_IRQn 1 */
}

/**
* @brief This function handles USART2 global interrupt.
*/
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */
  USART2_IRQHandler_Override();
  //return; // don't execute the next line.
  /* USER CODE END USART2_IRQn 0 */
  //HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */

  /* USER CODE END USART2_IRQn 1 */
}


/* USER CODE BEGIN 1 */

void USART2_IRQHandler_Override(void) {
	QXK_ISR_ENTRY();
	UART_HandleTypeDef *hal = &huart2;
	volatile uint32_t isrflags   = READ_REG(hal->Instance->SR);
	if (isrflags & USART_SR_ORE) {
		// Over-run error. Read DR followed by SR to clear flag.
		// Note - ORE will trigger interrupt when RXNE interrupt is enabled.
		uint32_t rxdata = READ_REG(hal->Instance->DR);
	} else {
		// Do not check RXNEIE bit as it may have been cleared automatically by DMA.
		// It is okay to not check as we don't use other UART interrupts.
		// Disable interrupt to avoid re-entering ISR before event is processed.
		CLEAR_BIT(hal->Instance->CR1, USART_CR1_RXNEIE);
		//CLEAR_BIT(hal->Instance->SR, USART_SR_RXNE);
		(void)0;
		//__disable_irq();
		//BSP_UART_ClearUnusedInterrupts(&huart2);
		AOs::UartIn::DmaDataReadyCallback();
		//__enable_irq();
	}
	// TX does not use it.
	//HAL_UART_IRQHandler(hal);
	QXK_ISR_EXIT();
	/*
	static int counterForTCIE, counterForTXE, counterForPE, counterForIDLE, counterForRNXE = 0;
	if (__HAL_UART_GET_IT_SOURCE(&huart2, UART_IT_TC)) counterForTCIE++;
	if (__HAL_UART_GET_IT_SOURCE(&huart2, UART_IT_TXE)) counterForTXE++;
	if (__HAL_UART_GET_IT_SOURCE(&huart2, UART_IT_PE)) counterForPE++;
	if (__HAL_UART_GET_IT_SOURCE(&huart2, UART_IT_IDLE)) counterForIDLE++;
	if (__HAL_UART_GET_IT_SOURCE(&huart2, UART_IT_RXNE)) counterForRNXE++;

	if (!__HAL_UART_GET_IT_SOURCE(&huart2, UART_IT_RXNE)) {
		BSP_UART_ClearUnusedInterrupts(&huart2);
		QXK_ISR_EXIT();
		return;
	}
	volatile uint32_t SRFlags   = READ_REG((&huart2)->Instance->SR);
	if (SRFlags & USART_SR_ORE) {
		// Over-run error. Read DR followed by SR to clear flag.
		// Note - ORE will trigger interrupt when RXNE interrupt is enabled.
		uint32_t rxdata = READ_REG((&huart2)->Instance->DR);
	} else {
		// Do not check RXNEIE bit as it may have been cleared automatically by DMA.
		// It is okay to not check as we don't use other UART interrupts.
		// Disable interrupt to avoid re-entering ISR before event is processed.
		CLEAR_BIT((&huart2)->Instance->CR1, USART_CR1_RXNEIE);
		AOs::UartIn::DmaDataReadyCallback();
	}
	// TX does not use it.
	//HAL_UART_IRQHandler(hal);
	QXK_ISR_EXIT();
	*/
}


void HAL_UART_TxCpltCallback(UART_HandleTypeDef *hal) {
    UartOut::DmaDoneCallback();
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *hal) {
	UartIn::DmaDoneCallback();
}

void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *hal) {
	(void)0; // Unused. You can call the UartOut::DmaDoneCallback() function if required.
}

} // Extern C
/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
