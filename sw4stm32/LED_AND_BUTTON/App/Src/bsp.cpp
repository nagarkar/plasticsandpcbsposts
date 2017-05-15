#include "bsp.h"
//#include "qpcpp.h"
//#include "events.h"

//using namespace QP;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	GPIO_PinState state = HAL_GPIO_ReadPin(LD2_GPIO_Port, LD2_Pin);
	if (state == GPIO_PIN_SET) {
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
	} else {
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
	}
	BSP_Printf("In Interrupt\r\n");

	//QF::PUBLISH(Q_NEW(ButtonPressEvt, BUTTON_1_PRESS_SIG), dummy);
}

extern "C" void assert_failed() {

}


static uint16_t PRINTF_BUF_LEN = 200;
void BSP_Printf(char const *format, ...) {
	va_list arg;
	va_start(arg, format);
	char buf[PRINTF_BUF_LEN];
	uint32_t len = vsnprintf(buf, COUNTOF(buf), format, arg);
	va_end(arg);
	len = LESS(len, COUNTOF(buf) - 1);
	HAL_UART_Transmit(&huart2, (uint8_t *) buf, len, 0xFFFF);
}

void BSP_LedOn(void) {
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
}

void BSP_LedOff(void) {
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
}

void BSP_Delay(volatile uint32_t delay) {
	HAL_Delay(delay);
}
