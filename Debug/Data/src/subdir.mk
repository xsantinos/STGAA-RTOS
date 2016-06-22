################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Data/src/Alarms.c \
../Data/src/Descriptors.c \
../Data/src/Environmental.c \
../Data/src/GPRS.c \
../Data/src/Recipe.c \
../Data/src/Sprayer.c 

OBJS += \
./Data/src/Alarms.o \
./Data/src/Descriptors.o \
./Data/src/Environmental.o \
./Data/src/GPRS.o \
./Data/src/Recipe.o \
./Data/src/Sprayer.o 

C_DEPS += \
./Data/src/Alarms.d \
./Data/src/Descriptors.d \
./Data/src/Environmental.d \
./Data/src/GPRS.d \
./Data/src/Recipe.d \
./Data/src/Sprayer.d 


# Each subdirectory must supply rules for building sources it contributes
Data/src/%.o: ../Data/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__USE_LPCOPEN -D__DEBUG_ON -DNO_BOARD_LIB -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\Prototipado\Documents\LPCXpresso_7.6.2_326\Workspace\STGA+RTOS\Data\inc" -I"C:\Users\Prototipado\Documents\LPCXpresso_7.6.2_326\Workspace\STGA+RTOS\Modules\inc" -I"C:\Users\Prototipado\Documents\LPCXpresso_7.6.2_326\Workspace\STGA+RTOS\Drivers\inc" -I"C:\Users\Prototipado\Documents\LPCXpresso_7.6.2_326\Workspace\STGA+RTOS\Board\inc" -I"C:\Users\Prototipado\Documents\LPCXpresso_7.6.2_326\Workspace\STGA+RTOS\freertos\inc" -I"C:\Users\Prototipado\Documents\LPCXpresso_7.6.2_326\Workspace\LIB_GL865\inc" -I"C:\Users\Prototipado\Documents\LPCXpresso_7.6.2_326\Workspace\Lib_FatFs_SD\inc" -I"C:\Users\Prototipado\Documents\LPCXpresso_7.6.2_326\Workspace\LIB_GLCDgui\inc" -I"C:\Users\Prototipado\Documents\LPCXpresso_7.6.2_326\Workspace\LIB_GLCDPrimitives\fonts" -I"C:\Users\Prototipado\Documents\LPCXpresso_7.6.2_326\Workspace\LIB_GLCDPrimitives\inc" -I"C:\Users\Prototipado\Documents\LPCXpresso_7.6.2_326\Workspace\Lib_GLCDLowLevel\inc" -I"C:\Users\Prototipado\Documents\LPCXpresso_7.6.2_326\Workspace\lpc_chip_175x_6x\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


