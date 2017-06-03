################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/gpio.c \
../Src/i2c.c \
../Src/rtc.c \
../Src/stm32f4xx_hal_msp.c \
../Src/stm32f4xx_it.c \
../Src/system_stm32f4xx.c \
../Src/usart.c 

CPP_SRCS += \
../Src/main.cpp 

OBJS += \
./Src/gpio.o \
./Src/i2c.o \
./Src/main.o \
./Src/rtc.o \
./Src/stm32f4xx_hal_msp.o \
./Src/stm32f4xx_it.o \
./Src/system_stm32f4xx.o \
./Src/usart.o 

C_DEPS += \
./Src/gpio.d \
./Src/i2c.d \
./Src/rtc.d \
./Src/stm32f4xx_hal_msp.d \
./Src/stm32f4xx_it.d \
./Src/system_stm32f4xx.d \
./Src/usart.d 

CPP_DEPS += \
./Src/main.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F401xE -DUSE_STM32F4XX_NUCLEO -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/STM32F4xx_HAL_Driver/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/CMSIS/Include" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/Components/Common" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/Components/lsm6ds0" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/Components/lsm6ds3" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/App"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Src/%.o: ../Src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU G++ Compiler'
	@echo $(PWD)
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F401xE -DUSE_STM32F4XX_NUCLEO '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/STM32F4xx_HAL_Driver/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/CMSIS/Include" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/Components/Common" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/Components/lsm6ds0" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/Components/lsm6ds3" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/App"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fno-exceptions -fno-rtti -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


