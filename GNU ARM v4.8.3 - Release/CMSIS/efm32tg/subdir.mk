################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32TG/Source/system_efm32tg.c 

S_UPPER_SRCS += \
/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32TG/Source/GCC/startup_efm32tg.S 

OBJS += \
./CMSIS/efm32tg/startup_efm32tg.o \
./CMSIS/efm32tg/system_efm32tg.o 

C_DEPS += \
./CMSIS/efm32tg/system_efm32tg.d 


# Each subdirectory must supply rules for building sources it contributes
CMSIS/efm32tg/startup_efm32tg.o: /Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32TG/Source/GCC/startup_efm32tg.S
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Assembler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -c -x assembler-with-cpp -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/EFM32TG_STK3300/examples/weatherstation" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/EFM32TG_STK3300/config" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/CMSIS/Include" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/emlib/inc" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/emdrv/common/inc" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/emdrv/config" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/emdrv/dmadrv/inc" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/emdrv/gpiointerrupt/inc" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/emdrv/nvm/inc" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/emdrv/rtcdrv/inc" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/emdrv/sleep/inc" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/emdrv/spidrv/inc" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/emdrv/uartdrv/inc" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/emdrv/ustimer/inc" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/bsp" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/drivers" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32TG/Include" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/reptile/glib" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/reptile/glib/glib" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/reptile/glib/dmd" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/reptile/glib/dmd/ssd2119" '-DEFM32TG840F32=1' -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

CMSIS/efm32tg/system_efm32tg.o: /Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32TG/Source/system_efm32tg.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32TG840F32=1' '-DNDEBUG=1' -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/EFM32TG_STK3300/examples/weatherstation" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/EFM32TG_STK3300/config" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/CMSIS/Include" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/emlib/inc" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/emdrv/common/inc" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/emdrv/config" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/emdrv/dmadrv/inc" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/emdrv/gpiointerrupt/inc" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/emdrv/nvm/inc" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/emdrv/rtcdrv/inc" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/emdrv/sleep/inc" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/emdrv/spidrv/inc" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/emdrv/uartdrv/inc" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/emdrv/ustimer/inc" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/bsp" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/drivers" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32TG/Include" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/reptile/glib" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/reptile/glib/glib" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/reptile/glib/dmd" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/reptile/glib/dmd/ssd2119" -I"/Users/imanolgo/Google Drive/Freelancing/2016/Elektrocouture/R&D/WirelessCharger/software/WirelessChargerEK/inc" -Os -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"CMSIS/efm32tg/system_efm32tg.d" -MT"CMSIS/efm32tg/system_efm32tg.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


