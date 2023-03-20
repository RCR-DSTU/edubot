################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/ssd1306/Src/fonts.c \
../Core/ssd1306/Src/ssd1306.c 

OBJS += \
./Core/ssd1306/Src/fonts.o \
./Core/ssd1306/Src/ssd1306.o 

C_DEPS += \
./Core/ssd1306/Src/fonts.d \
./Core/ssd1306/Src/ssd1306.d 


# Each subdirectory must supply rules for building sources it contributes
Core/ssd1306/Src/%.o Core/ssd1306/Src/%.su: ../Core/ssd1306/Src/%.c Core/ssd1306/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I"C:/Users/User/Documents/STM32/Core/ssd1306/Inc" -I"C:/Users/User/Documents/STM32/Core/ssd1306/Src" -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-ssd1306-2f-Src

clean-Core-2f-ssd1306-2f-Src:
	-$(RM) ./Core/ssd1306/Src/fonts.d ./Core/ssd1306/Src/fonts.o ./Core/ssd1306/Src/fonts.su ./Core/ssd1306/Src/ssd1306.d ./Core/ssd1306/Src/ssd1306.o ./Core/ssd1306/Src/ssd1306.su

.PHONY: clean-Core-2f-ssd1306-2f-Src

