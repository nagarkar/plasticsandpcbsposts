################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1.c \
E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_accelero.c \
E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_gyro.c \
E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_humidity.c \
E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_magneto.c \
E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_pressure.c \
E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_temperature.c 

OBJS += \
./IKSBSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1.o \
./IKSBSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_accelero.o \
./IKSBSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_gyro.o \
./IKSBSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_humidity.o \
./IKSBSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_magneto.o \
./IKSBSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_pressure.o \
./IKSBSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_temperature.o 

C_DEPS += \
./IKSBSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1.d \
./IKSBSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_accelero.d \
./IKSBSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_gyro.d \
./IKSBSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_humidity.d \
./IKSBSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_magneto.d \
./IKSBSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_pressure.d \
./IKSBSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_temperature.d 


# Each subdirectory must supply rules for building sources it contributes
IKSBSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1.o: E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F401xE -DUSE_STM32F4XX_NUCLEO -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/STM32F4xx_HAL_Driver/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/CMSIS/Include" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/X_NUCLEO_IKS01A1" -I"E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/Components/lsm6ds0" -I"E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/Components/lsm6ds3" -I"E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/Components/Common" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/CMSIS/Device/ST/STM32F4xx/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

IKSBSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_accelero.o: E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_accelero.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F401xE -DUSE_STM32F4XX_NUCLEO -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/STM32F4xx_HAL_Driver/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/CMSIS/Include" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/X_NUCLEO_IKS01A1" -I"E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/Components/lsm6ds0" -I"E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/Components/lsm6ds3" -I"E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/Components/Common" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/CMSIS/Device/ST/STM32F4xx/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

IKSBSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_gyro.o: E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_gyro.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F401xE -DUSE_STM32F4XX_NUCLEO -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/STM32F4xx_HAL_Driver/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/CMSIS/Include" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/X_NUCLEO_IKS01A1" -I"E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/Components/lsm6ds0" -I"E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/Components/lsm6ds3" -I"E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/Components/Common" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/CMSIS/Device/ST/STM32F4xx/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

IKSBSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_humidity.o: E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_humidity.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F401xE -DUSE_STM32F4XX_NUCLEO -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/STM32F4xx_HAL_Driver/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/CMSIS/Include" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/X_NUCLEO_IKS01A1" -I"E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/Components/lsm6ds0" -I"E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/Components/lsm6ds3" -I"E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/Components/Common" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/CMSIS/Device/ST/STM32F4xx/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

IKSBSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_magneto.o: E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_magneto.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F401xE -DUSE_STM32F4XX_NUCLEO -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/STM32F4xx_HAL_Driver/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/CMSIS/Include" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/X_NUCLEO_IKS01A1" -I"E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/Components/lsm6ds0" -I"E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/Components/lsm6ds3" -I"E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/Components/Common" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/CMSIS/Device/ST/STM32F4xx/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

IKSBSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_pressure.o: E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_pressure.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F401xE -DUSE_STM32F4XX_NUCLEO -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/STM32F4xx_HAL_Driver/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/CMSIS/Include" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/X_NUCLEO_IKS01A1" -I"E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/Components/lsm6ds0" -I"E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/Components/lsm6ds3" -I"E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/Components/Common" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/CMSIS/Device/ST/STM32F4xx/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

IKSBSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_temperature.o: E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/X_NUCLEO_IKS01A1/x_nucleo_iks01a1_temperature.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F401xE -DUSE_STM32F4XX_NUCLEO -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/STM32F4xx_HAL_Driver/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/CMSIS/Include" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/X_NUCLEO_IKS01A1" -I"E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/Components/lsm6ds0" -I"E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/Components/lsm6ds3" -I"E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/Components/Common" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/CMSIS/Device/ST/STM32F4xx/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


