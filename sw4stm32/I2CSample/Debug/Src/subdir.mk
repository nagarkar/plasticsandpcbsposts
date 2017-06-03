################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/gpio.c \
../Src/i2c.c \
../Src/main.c \
../Src/stm32f4xx_hal_msp.c \
../Src/stm32f4xx_it.c \
../Src/system_stm32f4xx.c \
../Src/usart.c 

OBJS += \
./Src/gpio.o \
./Src/i2c.o \
./Src/main.o \
./Src/stm32f4xx_hal_msp.o \
./Src/stm32f4xx_it.o \
./Src/system_stm32f4xx.o \
./Src/usart.o 

C_DEPS += \
./Src/gpio.d \
./Src/i2c.d \
./Src/main.d \
./Src/stm32f4xx_hal_msp.d \
./Src/stm32f4xx_it.d \
./Src/system_stm32f4xx.d \
./Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F401xE -DUSE_STM32F4XX_NUCLEO -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/STM32F4xx_HAL_Driver/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/CMSIS/Include" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/X_NUCLEO_IKS01A1" -I"E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/Components/Common" -I"E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/Components/lsm6ds0" -I"E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/Components/lsm6ds3"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


