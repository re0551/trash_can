################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSP/sevor/sevor.c 

OBJS += \
./BSP/sevor/sevor.o 

C_DEPS += \
./BSP/sevor/sevor.d 


# Each subdirectory must supply rules for building sources it contributes
BSP/sevor/%.o: ../BSP/sevor/%.c BSP/sevor/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-BSP-2f-sevor

clean-BSP-2f-sevor:
	-$(RM) ./BSP/sevor/sevor.d ./BSP/sevor/sevor.o

.PHONY: clean-BSP-2f-sevor

