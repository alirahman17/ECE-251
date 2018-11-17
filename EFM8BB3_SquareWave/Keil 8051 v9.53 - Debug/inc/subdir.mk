################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../inc/joystick.c 

OBJS += \
./inc/joystick.OBJ 


# Each subdirectory must supply rules for building sources it contributes
inc/%.OBJ: ../inc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Compiler'
	C51 "@$(patsubst %.OBJ,%.__i,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

inc/joystick.OBJ: C:/Users/Ali\ Rahman/SimplicityStudio/v4_workspace/EFM8BB3_DAC_2/lib/bsp/bsp.h C:/Users/Ali\ Rahman/SimplicityStudio/v4_workspace/EFM8BB3_DAC_2/inc/joystick.h C:/Users/Ali\ Rahman/SimplicityStudio/v4_workspace/EFM8BB3_DAC_2/inc/bsp_config.h C:/Users/Ali\ Rahman/SimplicityStudio/v4_workspace/EFM8BB3_DAC_2/inc/config/joystick_config.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.0.3/Device/EFM8BB3/inc/SI_EFM8BB3_Register_Enums.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.0.3/Device/EFM8BB3/inc/SI_EFM8BB3_Defs.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.0.3/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.0.3/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.0.3/Device/shared/si8051Base/stdbool.h


