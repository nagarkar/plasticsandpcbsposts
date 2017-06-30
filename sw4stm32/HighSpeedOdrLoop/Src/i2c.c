/**
  ******************************************************************************
  * File Name          : I2C.c
  * Description        : This file provides code for the configuration
  *                      of the I2C instances.
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
#include "i2c.h"

#include "gpio.h"

/* USER CODE BEGIN 0 */
#include "x_nucleo_iks01a1.h"
/* USER CODE END 0 */

I2C_HandleTypeDef hi2c3;

/* I2C3 init function */
void MX_I2C3_Init(void)
{

  hi2c3.Instance = I2C3;
  hi2c3.Init.ClockSpeed = 100000;
  hi2c3.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c3.Init.OwnAddress1 = 0;
  hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c3.Init.OwnAddress2 = 0;
  hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c3) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_I2C_MspInit(I2C_HandleTypeDef* i2cHandle)
{
  /// I2C Busy Flag Stuck Problem (I2C keeps timing out because the busy flag is always set)
  //  Mentioned here: https://goo.gl/mQdMUu
  //  Once this code runs, the busy flag will be reset. 
  //  Generally speaking, you can leave this in after the issue is fixed.
  HAL_I2C_ClearBusyFlagErrata_2_14_7(i2cHandle);
  GPIO_InitTypeDef GPIO_InitStruct;
  if(i2cHandle->Instance==I2C3)
  {
  /* USER CODE BEGIN I2C3_MspInit 0 */

  /* USER CODE END I2C3_MspInit 0 */
  
    /**I2C3 GPIO Configuration    
    PC9     ------> I2C3_SDA
    PA8     ------> I2C3_SCL 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C3;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C3;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* Peripheral clock enable */
    __HAL_RCC_I2C3_CLK_ENABLE();
  /* USER CODE BEGIN I2C3_MspInit 1 */

  /* USER CODE END I2C3_MspInit 1 */
  }
}

void HAL_I2C_MspDeInit(I2C_HandleTypeDef* i2cHandle)
{

  if(i2cHandle->Instance==I2C3)
  {
  /* USER CODE BEGIN I2C3_MspDeInit 0 */

  /* USER CODE END I2C3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_I2C3_CLK_DISABLE();
  
    /**I2C3 GPIO Configuration    
    PC9     ------> I2C3_SDA
    PA8     ------> I2C3_SCL 
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_9);

    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_8);

  }
  /* USER CODE BEGIN I2C3_MspDeInit 1 */

  /* USER CODE END I2C3_MspDeInit 1 */
} 

/* USER CODE BEGIN 1 */
/** Follow the steps given in section 2.14.7 of the stm32Fxx errata sheet:
	1. Disable the I2C peripheral by clearing the PE bit in I2Cx_CR1 register.
	2. Configure the SCL and SDA I/Os as General Purpose Output Open-Drain, High level
	(Write 1 to GPIOx_ODR).
	3. Check SCL and SDA High level in GPIOx_IDR.
	4. Configure the SDA I/O as General Purpose Output Open-Drain, Low level (Write 0 to
	GPIOx_ODR).
	5. Check SDA Low level in GPIOx_IDR.
	6. Configure the SCL I/O as General Purpose Output Open-Drain, Low level (Write 0 to
	GPIOx_ODR).
	7. Check SCL Low level in GPIOx_IDR.
	8. Configure the SCL I/O as General Purpose Output Open-Drain, High level (Write 1 to
	GPIOx_ODR).
	9. Check SCL High level in GPIOx_IDR.
	10. Configure the SDA I/O as General Purpose Output Open-Drain , High level (Write 1 to
	GPIOx_ODR).
	11. Check SDA High level in GPIOx_IDR.
	12. Configure the SCL and SDA I/Os as Alternate function Open-Drain.
	13. Set SWRST bit in I2Cx_CR1 register.
	14. Clear SWRST bit in I2Cx_CR1 register.
	15. Enable the I2C peripheral by setting the PE bit in I2Cx_CR1 register.
	
	This function only runs when the key symptom, hte busy flag being set, is true. It only
	runs once.
	
	Also see
	**/
void HAL_I2C_ClearBusyFlagErrata_2_14_7(I2C_HandleTypeDef *hi2c) {

	static uint8_t resetTried = 0;
	static uint8_t verify = 1;
	if (resetTried == 1) {
		return;
	}
	if(__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BUSY) != SET) {
		return;
	}
	uint32_t SDA_PIN = NUCLEO_I2C_EXPBD_SDA_PIN;
	uint32_t SCL_PIN = NUCLEO_I2C_EXPBD_SCL_PIN;
	GPIO_InitTypeDef GPIO_InitStruct;

	// 1
	__HAL_I2C_DISABLE(hi2c);

	// 2
	GPIO_InitStruct.Pin = SDA_PIN|SCL_PIN;
	HAL_GPIO_DeInit(GPIOB, &GPIO_InitStruct);
	__HAL_RCC_GPIOB_CLK_DISABLE();

	__HAL_RCC_GPIOB_CLK_ENABLE();

	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	HAL_GPIO_WRITE_ODR(GPIOB, SDA_PIN);
	HAL_GPIO_WRITE_ODR(GPIOB, SCL_PIN);

	// 3
	if (verify && HAL_GPIO_ReadPin(GPIOB, SDA_PIN) == GPIO_PIN_RESET) {
		for(;;){}
	}
	if (verify && HAL_GPIO_ReadPin(GPIOB, SCL_PIN) == GPIO_PIN_RESET) {
		for(;;){}
	}

	// 4
	GPIO_InitStruct.Pin = SDA_PIN;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	HAL_GPIO_TogglePin(GPIOB, SDA_PIN);

	// 5
	if (verify && HAL_GPIO_ReadPin(GPIOB, SDA_PIN) == GPIO_PIN_SET) {
		for(;;){}
	}

	// 6
	GPIO_InitStruct.Pin = SCL_PIN;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	HAL_GPIO_TogglePin(GPIOB, SCL_PIN);

	// 7
	if (verify && HAL_GPIO_ReadPin(GPIOB, SCL_PIN) == GPIO_PIN_SET) {
		for(;;){}
	}

	// 8
	GPIO_InitStruct.Pin = SDA_PIN;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	HAL_GPIO_WRITE_ODR(GPIOB, SDA_PIN);

	// 9
	if (verify && HAL_GPIO_ReadPin(GPIOB, SDA_PIN) == GPIO_PIN_RESET) {
		for(;;){}
	}

	// 10
	GPIO_InitStruct.Pin = SCL_PIN;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	HAL_GPIO_WRITE_ODR(GPIOB, SCL_PIN);

	// 11
	if (verify && HAL_GPIO_ReadPin(GPIOB, SCL_PIN) == GPIO_PIN_RESET) {
		for(;;){}
	}

	// 12
	GPIO_InitStruct.Pin 		= SDA_PIN|SCL_PIN;
	GPIO_InitStruct.Mode 		= GPIO_MODE_AF_OD;
	GPIO_InitStruct.Speed 		= GPIO_SPEED_FAST;
	GPIO_InitStruct.Pull 		= GPIO_NOPULL;
	GPIO_InitStruct.Alternate 	= NUCLEO_I2C_EXPBD_SCL_SDA_AF;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

   // 13
   hi2c->Instance->CR1 |= I2C_CR1_SWRST;

   // 14
   hi2c->Instance->CR1 ^= I2C_CR1_SWRST;

   // 15
   __HAL_I2C_ENABLE(hi2c);

   resetTried = 1;
}

void HAL_GPIO_WRITE_ODR(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  GPIOx->ODR |= GPIO_Pin;
}
/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
