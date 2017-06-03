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
#include "stm32f4xx_hal_uart.h"
#include "buffers.h"
static void MY_UART_DMAAbortOnError(DMA_HandleTypeDef *hdma);

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart2_tx;
extern UART_HandleTypeDef huart2;

/******************************************************************************/
/*            Cortex-M4 Processor Interruption and Exception Handlers         */ 
/******************************************************************************/

/**
* @brief This function handles System service call via SWI instruction.
*/
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
* @brief This function handles Pendable request for system service.
*/
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

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

  /* USER CODE END DMA1_Stream5_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart2_rx);
  /* USER CODE BEGIN DMA1_Stream5_IRQn 1 */

  /* USER CODE END DMA1_Stream5_IRQn 1 */
}

/**
* @brief This function handles DMA1 stream6 global interrupt.
*/
void DMA1_Stream6_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream6_IRQn 0 */

  /* USER CODE END DMA1_Stream6_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart2_tx);
  /* USER CODE BEGIN DMA1_Stream6_IRQn 1 */

  /* USER CODE END DMA1_Stream6_IRQn 1 */
}

/**
* @brief This function handles USART2 global interrupt.
*/
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */
	/*&
	static uint32_t remainingCount = BUFFER_SIZE;
    //__disable_irq();
    UART_HandleTypeDef *hal = &huart2;
    volatile uint32_t isrflags   = READ_REG(hal->Instance->SR);
    if (isrflags & USART_SR_ORE) {
        // Over-run error. Read DR followed by SR to clear flag.
        // Note - ORE will trigger interrupt when RXNE interrupt is enabled.
        uint32_t rxdata = READ_REG(hal->Instance->DR);
    } else if (isrflags & USART_SR_RXNE) {
        // Do not check RXNEIE bit as it may have been cleared automatically by DMA.
        // It is okay to not check as we don't use other UART interrupts.
        // Disable interrupt to avoid re-entering ISR before event is processed.
        //CLEAR_BIT(hal->Instance->CR1, USART_CR1_RXNEIE);
        uint32_t prevCount = remainingCount;
        uint32_t offset = BUFFER_SIZE - remainingCount;
        remainingCount = __HAL_DMA_GET_COUNTER(hal->hdmarx);
        uint32_t toEcho = prevCount - remainingCount;
        //__enable_irq();
        if (toEcho > 0) {
        	HAL_UART_Transmit_DMA(&huart2, (uint8_t *)(readBuffer + offset), toEcho);
        }
        else {
        	SET_BIT(hal->Instance->CR1, USART_CR1_RXNEIE);
        }
    }
    */
  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */
  //__HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE);
  /* USER CODE END USART2_IRQn 1 */
}

/* USER CODE BEGIN 1 */

void HAL_UART_ErrorCallback(UART_HandleTypeDef *hal) {
	static int x = 0;
	x++;
	(void)0;
}
void HAL_UART_TxHalfCpltCallback(UART_HandleTypeDef *hal) {
	static int x = 0;
	x++;
	(void)0;
}
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *hal) {
	//__HAL_UART_ENABLE_IT(hal, UART_IT_TC);
	//__HAL_UART_ENABLE_IT(hal, UART_IT_RXNE);
	static int x = 0;
	x++;
	(void)0;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *hal) {
	//__HAL_UART_DISABLE_IT(hal, UART_IT_TC);
	//__HAL_UART_ENABLE_IT(hal, UART_IT_RXNE);
	HAL_UART_Transmit_DMA(hal, (uint8_t *)readBuffer, 1);
	static int x = 0;
	x++;
	(void)0;
}

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
