################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/myTasks/DetectionTask.c \
../Core/Src/myTasks/messageTask.c \
../Core/Src/myTasks/myTask03.c 

OBJS += \
./Core/Src/myTasks/DetectionTask.o \
./Core/Src/myTasks/messageTask.o \
./Core/Src/myTasks/myTask03.o 

C_DEPS += \
./Core/Src/myTasks/DetectionTask.d \
./Core/Src/myTasks/messageTask.d \
./Core/Src/myTasks/myTask03.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/myTasks/%.o Core/Src/myTasks/%.su: ../Core/Src/myTasks/%.c Core/Src/myTasks/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"D:/STM32CubeIDE_1.9.0/workspace/MotorCtrlSys_STM32F407ZET6/Core/Inc/myBSP" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-myTasks

clean-Core-2f-Src-2f-myTasks:
	-$(RM) ./Core/Src/myTasks/DetectionTask.d ./Core/Src/myTasks/DetectionTask.o ./Core/Src/myTasks/DetectionTask.su ./Core/Src/myTasks/messageTask.d ./Core/Src/myTasks/messageTask.o ./Core/Src/myTasks/messageTask.su ./Core/Src/myTasks/myTask03.d ./Core/Src/myTasks/myTask03.o ./Core/Src/myTasks/myTask03.su

.PHONY: clean-Core-2f-Src-2f-myTasks

