################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Get_command.cpp \
../Handler.cpp \
../Message.cpp \
../MessageDbUp.cpp \
../MyTCPServerConnection.cpp \
../MyTCPServerConnectionFactory.cpp \
../New.cpp \
../Nick.cpp \
../Who.cpp \
../handler_factory.cpp \
../poco_server_framework.cpp 

OBJS += \
./Get_command.o \
./Handler.o \
./Message.o \
./MessageDbUp.o \
./MyTCPServerConnection.o \
./MyTCPServerConnectionFactory.o \
./New.o \
./Nick.o \
./Who.o \
./handler_factory.o \
./poco_server_framework.o 

CPP_DEPS += \
./Get_command.d \
./Handler.d \
./Message.d \
./MessageDbUp.d \
./MyTCPServerConnection.d \
./MyTCPServerConnectionFactory.d \
./New.d \
./Nick.d \
./Who.d \
./handler_factory.d \
./poco_server_framework.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


