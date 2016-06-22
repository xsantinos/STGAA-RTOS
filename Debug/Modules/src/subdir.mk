################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Modules/src/Acquirer.c \
../Modules/src/Analyzer.c \
../Modules/src/Storer.c \
../Modules/src/Transceiver.c \
../Modules/src/UserIO.c 

OBJS += \
./Modules/src/Acquirer.o \
./Modules/src/Analyzer.o \
./Modules/src/Storer.o \
./Modules/src/Transceiver.o \
./Modules/src/UserIO.o 

C_DEPS += \
./Modules/src/Acquirer.d \
./Modules/src/Analyzer.d \
./Modules/src/Storer.d \
./Modules/src/Transceiver.d \
./Modules/src/UserIO.d 


# Each subdirectory must supply rules for building sources it contributes
Modules/src/%.o: ../Modules/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__USE_LPCOPEN -D__DEBUG_ON -DNO_BOARD_LIB -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\Prototipado\Documents\LPCXpresso_7.6.2_326\Workspace\STGA+RTOS\Data\inc" -I"C:\Users\Prototipado\Documents\LPCXpresso_7.6.2_326\Workspace\STGA+RTOS\Modules\inc" -I"C:\Users\Prototipado\Documents\LPCXpresso_7.6.2_326\Workspace\STGA+RTOS\Drivers\inc" -I"C:\Users\Prototipado\Documents\LPCXpresso_7.6.2_326\Workspace\STGA+RTOS\Board\inc" -I"C:\Users\Prototipado\Documents\LPCXpresso_7.6.2_326\Workspace\STGA+RTOS\freertos\inc" -I"C:\Users\Prototipado\Documents\LPCXpresso_7.6.2_326\Workspace\LIB_GL865\inc" -I"C:\Users\Prototipado\Documents\LPCXpresso_7.6.2_326\Workspace\Lib_FatFs_SD\inc" -I"C:\Users\Prototipado\Documents\LPCXpresso_7.6.2_326\Workspace\LIB_GLCDgui\inc" -I"C:\Users\Prototipado\Documents\LPCXpresso_7.6.2_326\Workspace\LIB_GLCDPrimitives\fonts" -I"C:\Users\Prototipado\Documents\LPCXpresso_7.6.2_326\Workspace\LIB_GLCDPrimitives\inc" -I"C:\Users\Prototipado\Documents\LPCXpresso_7.6.2_326\Workspace\Lib_GLCDLowLevel\inc" -I"C:\Users\Prototipado\Documents\LPCXpresso_7.6.2_326\Workspace\lpc_chip_175x_6x\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


