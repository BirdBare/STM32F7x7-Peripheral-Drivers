TARGET = main
#our final binary file

MUST_BE_INCLUDED_OBJECTS = \
  startup_stm32f767xx.o \
  system_stm32f7xx.o \
  STM32F767_PERIPH.o \

CORE_OBJECTS = \
  STM32F767_GPIO.o \
  STM32F767_SPI.o \
  STM32F767_I2C.o \
  STM32F767_SYSTICK.o \
  
SYSTEM_KERNEL_OBJECT = STM32F767_KERNEL.o

MAIN = main.o

OBJECTS = \
  $(CORE_OBJECTS) \
  $(SYSTEM_KERNEL_OBJECT) \
  $(MUST_BE_INCLUDED_OBJECTS) \
  STM32F767_BALLOC.o \
  STM32F767_XPT2046.o \
  STM32F767_HTU21D.o \
  $(MAIN) \
#object files that we will compile to

vpath %.c Src
vpath %.s Src
vpath %.c ../bare_include/
vpath %.s ../bare_include/
vpath %.c ../bare_include/Source/KERNEL
vpath %.s ../bare_include/Source/KERNEL
vpath %.c ../bare_include/Source/CORE
vpath %.s ../bare_include/Source/CORE
vpath %.c ../bare_include/Source/EXTERNAL 
vpath %.c ../bare_include/Source/EXTERNAL 
vpath %.c ../bare_include/Source/MATH
vpath %.s ../bare_include/Source/MATH
vpath %.c ../bare_include/Source/GUI
vpath %.s ../bare_include/Source/GUI
vpath %.c ../bare_include/Source/LCD
vpath %.s ../bare_include/Source/LCD
vpath %.c ../bare_include/Source/UTILITIES
vpath %.s ../bare_include/Source/UTILITIES
#set a prefix folder to the %.c variable

CC = arm-none-eabi-gcc
LD = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump
#create variables to use with compilers

CFLAGS = \
  -Wall -g -O2  -mcpu=cortex-m7 -mfpu=fpv5-sp-d16 -mfloat-abi=hard \
  -fdata-sections -ffunction-sections -ffast-math \
  -fomit-frame-pointer \
  -DSTM32F767xx \
  -mthumb -mtune=arm7m\
  -IDrivers/Core \
  -IInc \
  -Wno-unused-function \
  -I../bare_include/ \
  -I../bare_include/Header/KERNEL \
  -I../bare_include/Header/CORE \
  -I../bare_include/Header/EXTERNAL\ DEVICES \
  -I../bare_include/Header/MATH \
  -I../bare_include/Header/GUI \
  -I../bare_include/Header/LCD \
  -I../bare_include/Header/UTILITIES \

LDFLAGS = \
  -mthumb -mcpu=cortex-m7 -mfpu=fpv5-sp-d16 -mfloat-abi=hard \
  -fdata-sections -ffunction-sections -ffast-math \
  -specs=nano.specs -Wl,-T,STM32F767ZI_FLASH.ld -Wl,--gc-sections,-Map=map.txt \
  -lc -lm -lnosys

OBJDUMPFLAGS = \
  -D

all: clean $(TARGET).bin tidy

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
	$(OBJDUMP) $(OBJDUMPFLAGS) $@ > $@.txt
	@echo 
  
#compile all .c files in SRC/ to .o in current directory
#dissassemble each file for debugging

%.o: %.s
	$(CC) -c $(CFLAGS) $< -o $@
	$(OBJDUMP) $(OBJDUMPFLAGS) $@ > $@.txt
	@echo 
#compile all .s files in current directory to .o


$(TARGET).elf: $(OBJECTS)
	$(LD) $(OBJECTS) $(LDFLAGS) -o $@
#link objects together into a symbolic elf file

%.bin: %.elf
	$(OBJCOPY) -O binary -S $< $@
#create binary from elf

tidy:
	mkdir Debug/
	mv map.txt Debug/ 
	mv *.o.txt Debug/ 
	mkdir Object\ Files/
	mv *.o Object\ Files/ 
     
clean:
	rm -rf $(TARGET).elf $(TARGET).bin $(TARGET).o *.o.txt map.txt
	rm -rf Object\ Files/
	rm -rf Debug//
