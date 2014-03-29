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
../sources/spi_lib.c \
../sources/Timer.c \
../sources/WatchDog.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
main.o \
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
sources/spi_lib.o \
sources/Timer.o \
sources/WatchDog.o


OBJS_AS_ARGS +=  \
main.o \
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
sources/spi_lib.o \
sources/Timer.o \
sources/WatchDog.o


C_DEPS +=  \
main.d \
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
sources/spi_lib.d \
sources/Timer.d \
sources/WatchDog.d


C_DEPS_AS_ARGS +=  \
main.d \
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
sources/spi_lib.d \
sources/Timer.d \
sources/WatchDog.d


OUTPUT_FILE_PATH +=Dashboard.elf

OUTPUT_FILE_PATH_AS_ARGS +=Dashboard.elf

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
	@echo Invoking: AVR/GNU Linker : (AVR_8_bit_GNU_Toolchain_3.4.1_830) 4.6.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="Dashboard.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,-L"../Libraries" -Wl,-L"../Libraries/aux_libs/includes"   -mmcu=at90can128  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature  "Dashboard.elf" "Dashboard.hex"
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "Dashboard.elf" "Dashboard.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-objdump.exe" -h -S "Dashboard.elf" > "Dashboard.lss"
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature  "Dashboard.elf" "Dashboard.srec"
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-size.exe" "Dashboard.elf"
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS)$(C_DEPS_AS_ARGS) $(EXECUTABLES) 
	rm -rf "Dashboard.elf" "Dashboard.a" "Dashboard.hex" "Dashboard.lss" "Dashboard.eep" "Dashboard.map" "Dashboard.srec"
	