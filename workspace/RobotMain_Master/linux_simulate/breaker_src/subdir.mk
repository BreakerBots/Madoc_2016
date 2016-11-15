################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:/Users/DS_2016/Desktop/breakerbots/breaker_src/Arm.cpp \
C:/Users/DS_2016/Desktop/breakerbots/breaker_src/DriveCalibrator.cpp \
C:/Users/DS_2016/Desktop/breakerbots/breaker_src/Indexer.cpp \
C:/Users/DS_2016/Desktop/breakerbots/breaker_src/Indexer_Bak.cpp \
C:/Users/DS_2016/Desktop/breakerbots/breaker_src/Motor.cpp \
C:/Users/DS_2016/Desktop/breakerbots/breaker_src/PrintStream.cpp \
C:/Users/DS_2016/Desktop/breakerbots/breaker_src/Utilities.cpp 

OBJS += \
./breaker_src/Arm.o \
./breaker_src/DriveCalibrator.o \
./breaker_src/Indexer.o \
./breaker_src/Indexer_Bak.o \
./breaker_src/Motor.o \
./breaker_src/PrintStream.o \
./breaker_src/Utilities.o 

CPP_DEPS += \
./breaker_src/Arm.d \
./breaker_src/DriveCalibrator.d \
./breaker_src/Indexer.d \
./breaker_src/Indexer_Bak.d \
./breaker_src/Motor.d \
./breaker_src/PrintStream.d \
./breaker_src/Utilities.d 


# Each subdirectory must supply rules for building sources it contributes
breaker_src/Arm.o: C:/Users/DS_2016/Desktop/breakerbots/breaker_src/Arm.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -I"C:\Users\DS_2016\Desktop\workspace\RobotMain_Master/src" -IC:\Users\DS_2016/wpilib/simulation/include -I/usr/include -I/usr/include/gazebo-6.5 -I/usr/include/ignition/math2 -I/usr/include/sdformat-3.7 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

breaker_src/DriveCalibrator.o: C:/Users/DS_2016/Desktop/breakerbots/breaker_src/DriveCalibrator.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -I"C:\Users\DS_2016\Desktop\workspace\RobotMain_Master/src" -IC:\Users\DS_2016/wpilib/simulation/include -I/usr/include -I/usr/include/gazebo-6.5 -I/usr/include/ignition/math2 -I/usr/include/sdformat-3.7 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

breaker_src/Indexer.o: C:/Users/DS_2016/Desktop/breakerbots/breaker_src/Indexer.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -I"C:\Users\DS_2016\Desktop\workspace\RobotMain_Master/src" -IC:\Users\DS_2016/wpilib/simulation/include -I/usr/include -I/usr/include/gazebo-6.5 -I/usr/include/ignition/math2 -I/usr/include/sdformat-3.7 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

breaker_src/Indexer_Bak.o: C:/Users/DS_2016/Desktop/breakerbots/breaker_src/Indexer_Bak.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -I"C:\Users\DS_2016\Desktop\workspace\RobotMain_Master/src" -IC:\Users\DS_2016/wpilib/simulation/include -I/usr/include -I/usr/include/gazebo-6.5 -I/usr/include/ignition/math2 -I/usr/include/sdformat-3.7 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

breaker_src/Motor.o: C:/Users/DS_2016/Desktop/breakerbots/breaker_src/Motor.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -I"C:\Users\DS_2016\Desktop\workspace\RobotMain_Master/src" -IC:\Users\DS_2016/wpilib/simulation/include -I/usr/include -I/usr/include/gazebo-6.5 -I/usr/include/ignition/math2 -I/usr/include/sdformat-3.7 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

breaker_src/PrintStream.o: C:/Users/DS_2016/Desktop/breakerbots/breaker_src/PrintStream.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -I"C:\Users\DS_2016\Desktop\workspace\RobotMain_Master/src" -IC:\Users\DS_2016/wpilib/simulation/include -I/usr/include -I/usr/include/gazebo-6.5 -I/usr/include/ignition/math2 -I/usr/include/sdformat-3.7 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

breaker_src/Utilities.o: C:/Users/DS_2016/Desktop/breakerbots/breaker_src/Utilities.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -I"C:\Users\DS_2016\Desktop\workspace\RobotMain_Master/src" -IC:\Users\DS_2016/wpilib/simulation/include -I/usr/include -I/usr/include/gazebo-6.5 -I/usr/include/ignition/math2 -I/usr/include/sdformat-3.7 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


