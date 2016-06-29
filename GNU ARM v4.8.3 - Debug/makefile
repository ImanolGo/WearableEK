################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include emlib/subdir.mk
-include Drivers/subdir.mk
-include CMSIS/efm32tg/subdir.mk
-include BSP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: WirelessChargerEK.axf

# Tool invocations
WirelessChargerEK.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -T "WirelessChargerEK.ld" -Xlinker --gc-sections -Xlinker -Map="WirelessChargerEK.map" --specs=nano.specs -o WirelessChargerEK.axf "./src/InitDevice.o" "./src/adp8866.o" "./src/device_utils.o" "./src/gpiosManager.o" "./src/i2c.o" "./src/main.o" "./src/mpu9250.o" "./src/noise.o" "./src/si7021.o" "./src/stc3105.o" "./src/stc3115.o" "./src/time_utils.o" "./emlib/em_adc.o" "./emlib/em_assert.o" "./emlib/em_cmu.o" "./emlib/em_emu.o" "./emlib/em_gpio.o" "./emlib/em_i2c.o" "./emlib/em_int.o" "./emlib/em_lcd.o" "./emlib/em_rtc.o" "./emlib/em_system.o" "./emlib/em_timer.o" "./emlib/em_vcmp.o" "./emlib/gpiointerrupt.o" "./Drivers/i2cspm.o" "./Drivers/rtcdriver.o" "./Drivers/segmentlcd.o" "./Drivers/si1147_i2c.o" "./Drivers/si114x_algorithm.o" "./Drivers/si114x_functions.o" "./Drivers/si7013.o" "./Drivers/vddcheck.o" "./CMSIS/efm32tg/startup_efm32tg.o" "./CMSIS/efm32tg/system_efm32tg.o" "./BSP/bsp_trace.o" -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: WirelessChargerEK.hex'
	arm-none-eabi-objcopy -O ihex "WirelessChargerEK.axf" "WirelessChargerEK.hex"
	@echo ' '

	@echo 'Building bin file: WirelessChargerEK.bin'
	arm-none-eabi-objcopy -O binary "WirelessChargerEK.axf" "WirelessChargerEK.bin"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "WirelessChargerEK.axf"
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) WirelessChargerEK.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
