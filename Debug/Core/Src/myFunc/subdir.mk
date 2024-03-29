################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/myFunc/FDC2112.c \
../Core/Src/myFunc/MotorCtrl.c \
../Core/Src/myFunc/PressureSensor.c \
../Core/Src/myFunc/ScheduleTable.c \
../Core/Src/myFunc/myADC.c \
../Core/Src/myFunc/pid.c 

OBJS += \
./Core/Src/myFunc/FDC2112.o \
./Core/Src/myFunc/MotorCtrl.o \
./Core/Src/myFunc/PressureSensor.o \
./Core/Src/myFunc/ScheduleTable.o \
./Core/Src/myFunc/myADC.o \
./Core/Src/myFunc/pid.o 

C_DEPS += \
./Core/Src/myFunc/FDC2112.d \
./Core/Src/myFunc/MotorCtrl.d \
./Core/Src/myFunc/PressureSensor.d \
./Core/Src/myFunc/ScheduleTable.d \
./Core/Src/myFunc/myADC.d \
./Core/Src/myFunc/pid.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/myFunc/%.o Core/Src/myFunc/%.su Core/Src/myFunc/%.cyclo: ../Core/Src/myFunc/%.c Core/Src/myFunc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"D:/STM32CubeIDE_1.9.0/workspace/MotorCtrlSys_STM32F407ZET6/Core/Inc/myBSP" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-myFunc

clean-Core-2f-Src-2f-myFunc:
	-$(RM) ./Core/Src/myFunc/FDC2112.cyclo ./Core/Src/myFunc/FDC2112.d ./Core/Src/myFunc/FDC2112.o ./Core/Src/myFunc/FDC2112.su ./Core/Src/myFunc/MotorCtrl.cyclo ./Core/Src/myFunc/MotorCtrl.d ./Core/Src/myFunc/MotorCtrl.o ./Core/Src/myFunc/MotorCtrl.su ./Core/Src/myFunc/PressureSensor.cyclo ./Core/Src/myFunc/PressureSensor.d ./Core/Src/myFunc/PressureSensor.o ./Core/Src/myFunc/PressureSensor.su ./Core/Src/myFunc/ScheduleTable.cyclo ./Core/Src/myFunc/ScheduleTable.d ./Core/Src/myFunc/ScheduleTable.o ./Core/Src/myFunc/ScheduleTable.su ./Core/Src/myFunc/myADC.cyclo ./Core/Src/myFunc/myADC.d ./Core/Src/myFunc/myADC.o ./Core/Src/myFunc/myADC.su ./Core/Src/myFunc/pid.cyclo ./Core/Src/myFunc/pid.d ./Core/Src/myFunc/pid.o ./Core/Src/myFunc/pid.su

.PHONY: clean-Core-2f-Src-2f-myFunc

