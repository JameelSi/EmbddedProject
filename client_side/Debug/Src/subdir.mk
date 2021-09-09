################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/button.c \
../Src/cyclic_buffer.c \
../Src/eventQ.c \
../Src/led.c \
../Src/main.c \
../Src/modem.c \
../Src/terminal.c \
../Src/timer2.c \
../Src/usart1.c \
../Src/usart1terminal.c \
../Src/usart2.c \
../Src/watchdog.c 

OBJS += \
./Src/button.o \
./Src/cyclic_buffer.o \
./Src/eventQ.o \
./Src/led.o \
./Src/main.o \
./Src/modem.o \
./Src/terminal.o \
./Src/timer2.o \
./Src/usart1.o \
./Src/usart1terminal.o \
./Src/usart2.o \
./Src/watchdog.o 

C_DEPS += \
./Src/button.d \
./Src/cyclic_buffer.d \
./Src/eventQ.d \
./Src/led.d \
./Src/main.d \
./Src/modem.d \
./Src/terminal.d \
./Src/timer2.d \
./Src/usart1.d \
./Src/usart1terminal.d \
./Src/usart2.d \
./Src/watchdog.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F3 -DDEBUG -DSTM32F303RETx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

