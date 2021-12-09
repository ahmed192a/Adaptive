################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ara/core/error_code.cpp \
../src/ara/core/error_domain.cpp \
../src/ara/core/exception.cpp 

OBJS += \
./src/ara/core/error_code.o \
./src/ara/core/error_domain.o \
./src/ara/core/exception.o 

CPP_DEPS += \
./src/ara/core/error_code.d \
./src/ara/core/error_domain.d \
./src/ara/core/exception.d 


# Each subdirectory must supply rules for building sources it contributes
src/ara/core/%.o: ../src/ara/core/%.cpp src/ara/core/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


