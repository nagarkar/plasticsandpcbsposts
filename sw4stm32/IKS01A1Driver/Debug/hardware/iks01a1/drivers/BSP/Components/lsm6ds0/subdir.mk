################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/Components/lsm6ds0/LSM6DS0_ACC_GYRO_driver.c \
E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/Components/lsm6ds0/LSM6DS0_ACC_GYRO_driver_HL.c 

OBJS += \
./hardware/iks01a1/drivers/BSP/Components/lsm6ds0/LSM6DS0_ACC_GYRO_driver.o \
./hardware/iks01a1/drivers/BSP/Components/lsm6ds0/LSM6DS0_ACC_GYRO_driver_HL.o 

C_DEPS += \
./hardware/iks01a1/drivers/BSP/Components/lsm6ds0/LSM6DS0_ACC_GYRO_driver.d \
./hardware/iks01a1/drivers/BSP/Components/lsm6ds0/LSM6DS0_ACC_GYRO_driver_HL.d 


# Each subdirectory must supply rules for building sources it contributes
hardware/iks01a1/drivers/BSP/Components/lsm6ds0/LSM6DS0_ACC_GYRO_driver.o: E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/Components/lsm6ds0/LSM6DS0_ACC_GYRO_driver.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F401xE -DUSE_STM32F4XX_NUCLEO -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/STM32F4xx_HAL_Driver/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/CMSIS/Include" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/Components/Common" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/Components/lsm6ds0" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/Components/lsm6ds3" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/App"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

hardware/iks01a1/drivers/BSP/Components/lsm6ds0/LSM6DS0_ACC_GYRO_driver_HL.o: E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/Components/lsm6ds0/LSM6DS0_ACC_GYRO_driver_HL.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F401xE -DUSE_STM32F4XX_NUCLEO -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/STM32F4xx_HAL_Driver/Inc" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/Drivers/CMSIS/Include" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/X_NUCLEO_IKS01A1" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/Components/Common" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/Components/lsm6ds0" -I"E:/repositories/plasticsandpcbsposts/hardware/iks01a1/drivers/BSP/Components/lsm6ds3" -I"E:/repositories/plasticsandpcbsposts/sw4stm32/IKS01A1Driver/App"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


