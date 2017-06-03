################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1.c \
E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_accelero.c \
E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_gyro.c \
E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_humidity.c \
E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_magneto.c \
E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_pressure.c \
E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_temperature.c 

OBJS += \
./hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1.o \
./hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_accelero.o \
./hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_gyro.o \
./hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_humidity.o \
./hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_magneto.o \
./hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_pressure.o \
./hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_temperature.o 

C_DEPS += \
./hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1.d \
./hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_accelero.d \
./hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_gyro.d \
./hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_humidity.d \
./hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_magneto.d \
./hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_pressure.d \
./hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_temperature.d 


# Each subdirectory must supply rules for building sources it contributes
hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1.o: E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F401xE -DUSE_STM32F4XX_NUCLEO -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/STM32F4xx_HAL_Driver/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/CMSIS/Include" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/Components/Common" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/Components/lsm6ds0" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/Components/lsm6ds3" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/App"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_accelero.o: E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_accelero.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F401xE -DUSE_STM32F4XX_NUCLEO -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/STM32F4xx_HAL_Driver/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/CMSIS/Include" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/Components/Common" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/Components/lsm6ds0" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/Components/lsm6ds3" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/App"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_gyro.o: E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_gyro.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F401xE -DUSE_STM32F4XX_NUCLEO -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/STM32F4xx_HAL_Driver/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/CMSIS/Include" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/Components/Common" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/Components/lsm6ds0" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/Components/lsm6ds3" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/App"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_humidity.o: E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_humidity.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F401xE -DUSE_STM32F4XX_NUCLEO -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/STM32F4xx_HAL_Driver/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/CMSIS/Include" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/Components/Common" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/Components/lsm6ds0" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/Components/lsm6ds3" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/App"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_magneto.o: E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_magneto.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F401xE -DUSE_STM32F4XX_NUCLEO -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/STM32F4xx_HAL_Driver/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/CMSIS/Include" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/Components/Common" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/Components/lsm6ds0" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/Components/lsm6ds3" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/App"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_pressure.o: E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_pressure.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F401xE -DUSE_STM32F4XX_NUCLEO -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/STM32F4xx_HAL_Driver/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/CMSIS/Include" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/Components/Common" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/Components/lsm6ds0" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/Components/lsm6ds3" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/App"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_temperature.o: E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_temperature.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F401xE -DUSE_STM32F4XX_NUCLEO -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/STM32F4xx_HAL_Driver/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/CMSIS/Include" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/Components/Common" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/Components/lsm6ds0" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/Components/lsm6ds3" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/App"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


