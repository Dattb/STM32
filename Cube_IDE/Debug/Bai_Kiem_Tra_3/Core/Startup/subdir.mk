################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Bai_Kiem_Tra_3/Core/Startup/startup_stm32f103c8tx.s 

OBJS += \
./Bai_Kiem_Tra_3/Core/Startup/startup_stm32f103c8tx.o 

S_DEPS += \
./Bai_Kiem_Tra_3/Core/Startup/startup_stm32f103c8tx.d 


# Each subdirectory must supply rules for building sources it contributes
Bai_Kiem_Tra_3/Core/Startup/startup_stm32f103c8tx.o: ../Bai_Kiem_Tra_3/Core/Startup/startup_stm32f103c8tx.s
	arm-none-eabi-gcc -mcpu=cortex-m3 -g3 -c -x assembler-with-cpp -MMD -MP -MF"Bai_Kiem_Tra_3/Core/Startup/startup_stm32f103c8tx.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"
