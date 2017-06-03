################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/Components/lsm6ds3/LSM6DS3_ACC_GYRO_driver.c \
E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/Components/lsm6ds3/LSM6DS3_ACC_GYRO_driver_HL.c 

OBJS += \
./IKSBSP/Components/lsm6ds3/LSM6DS3_ACC_GYRO_driver.o \
./IKSBSP/Components/lsm6ds3/LSM6DS3_ACC_GYRO_driver_HL.o 

C_DEPS += \
./IKSBSP/Components/lsm6ds3/LSM6DS3_ACC_GYRO_driver.d \
./IKSBSP/Components/lsm6ds3/LSM6DS3_ACC_GYRO_driver_HL.d 


# Each subdirectory must supply rules for building sources it contributes
IKSBSP/Components/lsm6ds3/LSM6DS3_ACC_GYRO_driver.o: E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/Components/lsm6ds3/LSM6DS3_ACC_GYRO_driver.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F401xE -DUSE_STM32F4XX_NUCLEO -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/STM32F4xx_HAL_Driver/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/CMSIS/Include" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/X_NUCLEO_IKS01A1" -I"E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/Components/lsm6ds0" -I"E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/Components/lsm6ds3" -I"E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/Components/Common" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/CMSIS/Device/ST/STM32F4xx/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

IKSBSP/Components/lsm6ds3/LSM6DS3_ACC_GYRO_driver_HL.o: E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/Components/lsm6ds3/LSM6DS3_ACC_GYRO_driver_HL.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F401xE -DUSE_STM32F4XX_NUCLEO -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/STM32F4xx_HAL_Driver/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/CMSIS/Include" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/X_NUCLEO_IKS01A1" -I"E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/Components/lsm6ds0" -I"E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/Components/lsm6ds3" -I"E:/software/stmtoolchain/en.x-cube-mems1/STM32CubeExpansion_MEMS1_V3.0.0/Drivers/BSP/Components/Common" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/I2CSample/Drivers/CMSIS/Device/ST/STM32F4xx/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


