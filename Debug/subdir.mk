################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC.c \
../DS1340.c \
../IOPort.c \
../Interrupt.c \
../LEDMosfet.c \
../Led.c \
../LightMeasure.c \
../MoveSensor.c \
../Random.c \
../SDTimes.c \
../Switch.c \
../TimeCount.c \
../Timer.c \
../i2c.c \
../main.c \
../mmc.c \
../pff.c \
../uart.c \
../wav.c 

OBJS += \
./ADC.o \
./DS1340.o \
./IOPort.o \
./Interrupt.o \
./LEDMosfet.o \
./Led.o \
./LightMeasure.o \
./MoveSensor.o \
./Random.o \
./SDTimes.o \
./Switch.o \
./TimeCount.o \
./Timer.o \
./i2c.o \
./main.o \
./mmc.o \
./pff.o \
./uart.o \
./wav.o 

C_DEPS += \
./ADC.d \
./DS1340.d \
./IOPort.d \
./Interrupt.d \
./LEDMosfet.d \
./Led.d \
./LightMeasure.d \
./MoveSensor.d \
./Random.d \
./SDTimes.d \
./Switch.d \
./TimeCount.d \
./Timer.d \
./i2c.d \
./main.d \
./mmc.d \
./pff.d \
./uart.d \
./wav.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -Os -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=20000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


