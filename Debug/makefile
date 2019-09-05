################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
SD_repeller_V3.lss \

FLASH_IMAGE += \
SD_repeller_V3.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: SD_repeller_V3.elf secondary-outputs

# Tool invocations
SD_repeller_V3.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,SD_repeller_V3.map -mmcu=atmega644p -o "SD_repeller_V3.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

SD_repeller_V3.lss: SD_repeller_V3.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S SD_repeller_V3.elf  >"SD_repeller_V3.lss"
	@echo 'Finished building: $@'
	@echo ' '

SD_repeller_V3.hex: SD_repeller_V3.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex SD_repeller_V3.elf  "SD_repeller_V3.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: SD_repeller_V3.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega644p SD_repeller_V3.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) SD_repeller_V3.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
