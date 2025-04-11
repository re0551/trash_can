################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../icode/infrared/infrared.c 

OBJS += \
./icode/infrared/infrared.o 

C_DEPS += \
./icode/infrared/infrared.d 


# Each subdirectory must supply rules for building sources it contributes
icode/infrared/%.o: ../icode/infrared/%.c icode/infrared/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-icode-2f-infrared

clean-icode-2f-infrared:
	-$(RM) ./icode/infrared/infrared.d ./icode/infrared/infrared.o

.PHONY: clean-icode-2f-infrared

