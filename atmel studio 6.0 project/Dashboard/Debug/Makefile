################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../includes \
../sources


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../main.c \
../sources/adc.c \
../sources/Button.c \
../sources/Buzzer.c \
../sources/CAN.c \
../sources/can_drv.c \
../sources/can_lib.c \
../sources/Display.c \
../sources/Error.c \
../sources/Event.c \
../sources/Led.c \
../sources/MyCommon.c \
../sources/Timer.c \
../sources/WatchDog.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
main.o \
sources/adc.o \
sources/Button.o \
sources/Buzzer.o \
sources/CAN.o \
sources/can_drv.o \
sources/can_lib.o \
sources/Display.o \
sources/Error.o \
sources/Event.o \
sources/Led.o \
sources/MyCommon.o \
sources/Timer.o \
sources/WatchDog.o


OBJS_AS_ARGS +=  \
main.o \
sources/adc.o \
sources/Button.o \
sources/Buzzer.o \
sources/CAN.o \
sources/can_drv.o \
sources/can_lib.o \
sources/Display.o \
sources/Error.o \
sources/Event.o \
sources/Led.o \
sources/MyCommon.o \
sources/Timer.o \
sources/WatchDog.o


C_DEPS +=  \
main.d \
sources/adc.d \
sources/Button.d \
sources/Buzzer.d \
sources/CAN.d \
sources/can_drv.d \
sources/can_lib.d \
sources/Display.d \
sources/Error.d \
sources/Event.d \
sources/Led.d \
sources/MyCommon.d \
sources/Timer.d \
sources/WatchDog.d


C_DEPS_AS_ARGS +=  \
main.d \
sources/adc.d \
sources/Button.d \
sources/Buzzer.d \
sources/CAN.d \
sources/can_drv.d \
sources/can_lib.d \
sources/Display.d \
sources/Error.d \
sources/Event.d \
sources/Led.d \
sources/MyCommon.d \
sources/Timer.d \
sources/WatchDog.d


OUTPUT_FILE_PATH +=libDashboard.a

OUTPUT_FILE_PATH_AS_ARGS +=libDashboard.a

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

# AVR32/GNU C Compiler





























./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : (AVR_8_bit_GNU_Toolchain_3.4.1_830) 4.6.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-gcc.exe$(QUOTE) -funsigned-char -funsigned-bitfields -O1 -fpack-struct -fshort-enums -g2 -Wall -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"  -mmcu=at90can128   -o"$@" "$<" 
	@echo Finished building: $<

sources/%.o: ../sources/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : (AVR_8_bit_GNU_Toolchain_3.4.1_830) 4.6.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-gcc.exe$(QUOTE) -funsigned-char -funsigned-bitfields -O1 -fpack-struct -fshort-enums -g2 -Wall -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"  -mmcu=at90can128   -o"$@" "$<" 
	@echo Finished building: $<



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)


$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Archiver : GNU ar (AVR_8_bit_GNU_Toolchain_3.4.1_830) 2.22
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-ar.exe$(QUOTE) -r  -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS)
	@echo Finished building target: $@
	




# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS)$(C_DEPS_AS_ARGS) $(EXECUTABLES) 
	rm -rf "libDashboard.elf" "libDashboard.a" "libDashboard.hex" "libDashboard.lss" "libDashboard.eep" "libDashboard.map" "libDashboard.srec"
	