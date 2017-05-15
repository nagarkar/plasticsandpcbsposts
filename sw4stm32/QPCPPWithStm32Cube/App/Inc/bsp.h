#ifndef BSP_H_
#define BSP_H_

#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include "usart.h"
#include "stm32f4xx_hal.h"
#include "gpio.h"
#include "stm32f4xx_hal_gpio.h"
#include "macros.h"

#ifdef __cplusplus
 extern "C" {
#endif

void BSP_Printf(char const *format, ...);
void BSP_LedOn(void);
void BSP_LedOff(void);
void BSP_Delay(volatile uint32_t delay);

#ifdef __cplusplus
}
#endif
#endif
