################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../icode/tjc_usart/tjc_usart.c 

OBJS += \
./icode/tjc_usart/tjc_usart.o 

C_DEPS += \
./icode/tjc_usart/tjc_usart.d 


# Each subdirectory must supply rules for building sources it contributes
icode/tjc_usart/%.o: ../icode/tjc_usart/%.c icode/tjc_usart/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-icode-2f-tjc_usart

clean-icode-2f-tjc_usart:
	-$(RM) ./icode/tjc_usart/tjc_usart.d ./icode/tjc_usart/tjc_usart.o

.PHONY: clean-icode-2f-tjc_usart

