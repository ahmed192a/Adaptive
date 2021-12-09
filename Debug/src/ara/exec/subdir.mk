################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ara/exec/deterministic_client.cpp \
../src/ara/exec/exec_error_domain.cpp \
../src/ara/exec/execution_client.cpp 

OBJS += \
./src/ara/exec/deterministic_client.o \
./src/ara/exec/exec_error_domain.o \
./src/ara/exec/execution_client.o 

CPP_DEPS += \
./src/ara/exec/deterministic_client.d \
./src/ara/exec/exec_error_domain.d \
./src/ara/exec/execution_client.d 


# Each subdirectory must supply rules for building sources it contributes
src/ara/exec/%.o: ../src/ara/exec/%.cpp src/ara/exec/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


