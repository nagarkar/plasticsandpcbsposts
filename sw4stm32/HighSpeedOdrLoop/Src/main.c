/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
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
#include "main.h"
#include "stm32f4xx_hal.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include <stdbool.h>
#include "LSM6DS0_ACC_GYRO_driver.h"
#include "LSM6DS0_ACC_GYRO_driver_HL.h"
#include "component.h"
#include "x_nucleo_iks01a1_accelero.h"
#include "x_nucleo_iks01a1_gyro.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

void * handle;
void * gyroHandle;
int counter;
int prevCounter;
int delays;
float gyroRate;
float sensitivity;
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Error_Handler(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
static void ACC_Init(void);
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();

  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if (prevCounter == counter) {
		  ACC_Init();
	  }
	  prevCounter = counter;
	  HAL_Delay(1000); // milliseconds
	  delays++;
	  gyroRate = ((float)counter)/delays; // Hz
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */


  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

static void ACC_Init(void) {

	static uint8_t isInitialized = 0;
	uint32_t prim = __get_PRIMASK();
	__disable_irq();

	volatile status_t status;
	volatile DrvStatusTypeDef result = COMPONENT_OK;
	volatile DrvStatusTypeDef drv_status = COMPONENT_ERROR;

	if (isInitialized == 1) {
		result = BSP_ACCELERO_DeInit(&handle);
		isInitialized = 0;
	}
	result = BSP_ACCELERO_Init(LSM6DS0_X_0, &handle);
	isInitialized = 1;
	if (result == COMPONENT_OK) {
		result = BSP_ACCELERO_Sensor_Enable(handle);
		if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) != RESET) {
			LSM6DS0_ACC_GYRO_W_ResetSW(handle, LSM6DS0_ACC_GYRO_SW_RESET_YES);
		}
	}
	if (result != COMPONENT_OK) {
		if (!prim) {
			__enable_irq();
		}
		ACC_Init();
	}


	// CTRL_REG1_G Register
	status = LSM6DS0_ACC_GYRO_W_GyroDataRate(handle, LSM6DS0_ACC_GYRO_ODR_G_952Hz);
	status = LSM6DS0_ACC_GYRO_W_GyroBandwidthSelection(handle, LSM6DS0_ACC_GYRO_BW_G_ULTRA_HIGH);
	status = LSM6DS0_ACC_GYRO_W_GyroFullScale(handle, LSM6DS0_ACC_GYRO_FS_G_2000dps);
	status = LSM6DS0_ACC_GYRO_W_AutoIndexOnMultiAccess(handle, LSM6DS0_ACC_GYRO_IF_ADD_INC_ENABLE);


	// CTRL_REG4 Register
	status = LSM6DS0_ACC_GYRO_W_AccelerometerDataRate(handle, LSM6DS0_ACC_GYRO_ODR_XL_952Hz);
	status = LSM6DS0_ACC_GYRO_W_AccelerometerFullScale(handle, LSM6DS0_ACC_GYRO_FS_XL_2g);
	status = LSM6DS0_ACC_GYRO_W_AccelerometerBandWitdthSelection(handle, LSM6DS0_ACC_GYRO_BW_SCAL_ODR_WITH_BW_XL);
	status = LSM6DS0_ACC_GYRO_W_AccelerometerFilterBandwidth(handle, LSM6DS0_ACC_GYRO_BW_XL_105Hz);

	// CTRL_REG7_XL Register
	status = LSM6DS0_ACC_GYRO_W_AccelerometerAxisX(handle, LSM6DS0_ACC_GYRO_XEN_XL_ENABLE);
	status = LSM6DS0_ACC_GYRO_W_AccelerometerAxisY(handle, LSM6DS0_ACC_GYRO_XEN_XL_ENABLE);
	status = LSM6DS0_ACC_GYRO_W_AccelerometerAxisZ(handle, LSM6DS0_ACC_GYRO_XEN_XL_ENABLE);

	status = LSM6DS0_ACC_GYRO_W_GyroAxisX(handle, LSM6DS0_ACC_GYRO_XEN_G_ENABLE);
	status = LSM6DS0_ACC_GYRO_W_GyroAxisY(handle, LSM6DS0_ACC_GYRO_XEN_G_ENABLE);
	status = LSM6DS0_ACC_GYRO_W_GyroAxisZ(handle, LSM6DS0_ACC_GYRO_XEN_G_ENABLE);

	status = LSM6DS0_ACC_GYRO_W_AccelerometerHighResolutionMode(handle, LSM6DS0_ACC_GYRO_HR_ENABLE);
	status = LSM6DS0_ACC_GYRO_W_AccelerometerCutOff_filter(handle, LSM6DS0_ACC_GYRO_DCF_ODR_DIV_9);
	status = LSM6DS0_ACC_GYRO_W_AccelerometerFilteredDataSelection(handle, LSM6DS0_ACC_GYRO_FDS_FILTER_ENABLE);

	/////// 	INT_CTRL Register 	//////////
	status = LSM6DS0_ACC_GYRO_W_XL_DataReadyOnINT(handle, LSM6DS0_ACC_GYRO_INT_DRDY_XL_ENABLE);
	status = LSM6DS0_ACC_GYRO_W_GYRO_DataReadyOnINT(handle, LSM6DS0_ACC_GYRO_INT_DRDY_G_ENABLE);

	DrvContextTypeDef *ctx = (DrvContextTypeDef *)handle;
	u8_t acc_8_t[6] = {0, 0, 0, 0, 0, 0};
	status = HAL_I2C_Mem_Read(GetI2CHandle(), ctx->address, LSM6DS0_ACC_GYRO_OUT_X_L_XL, I2C_MEMADD_SIZE_8BIT, acc_8_t, 6, NUCLEO_I2C_EXPBD_TIMEOUT_MAX);

	if (!prim) {
		__enable_irq();
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin != GPIO_PIN_5) {
		return;
	}
	uint32_t prim = __get_PRIMASK();

	u8_t value;
	LSM6DS0_ACC_GYRO_ReadReg(handle, LSM6DS0_ACC_GYRO_STATUS_REG, &value, 1);

	if ((value & LSM6DS0_ACC_GYRO_GDA_MASK) != LSM6DS0_ACC_GYRO_GDA_UP) {
		return;
	}

	DrvContextTypeDef *ctx = (DrvContextTypeDef *)handle;
	HAL_StatusTypeDef status;

	u8_t acc_8_t[6] = {0, 0, 0, 0, 0, 0};
	status = HAL_I2C_Mem_Read(GetI2CHandle(), ctx->address, LSM6DS0_ACC_GYRO_OUT_X_L_XL, I2C_MEMADD_SIZE_8BIT, acc_8_t, 6, NUCLEO_I2C_EXPBD_TIMEOUT_MAX);
	status = HAL_I2C_Mem_Read(GetI2CHandle(), ctx->address, LSM6DS0_ACC_GYRO_OUT_X_L_G, I2C_MEMADD_SIZE_8BIT, acc_8_t, 6, NUCLEO_I2C_EXPBD_TIMEOUT_MAX);
	counter++;
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
