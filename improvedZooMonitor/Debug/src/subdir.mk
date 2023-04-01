################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/improvedZooMonitor.cpp 

C_SRCS += \
../src/shell.c \
../src/sqlite3.c 

CPP_DEPS += \
./src/improvedZooMonitor.d 

C_DEPS += \
./src/shell.d \
./src/sqlite3.d 

OBJS += \
./src/improvedZooMonitor.o \
./src/shell.o \
./src/sqlite3.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/improvedZooMonitor.d ./src/improvedZooMonitor.o ./src/shell.d ./src/shell.o ./src/sqlite3.d ./src/sqlite3.o

.PHONY: clean-src

