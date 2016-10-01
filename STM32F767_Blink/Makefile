TARGET = main
#our final binary file

OBJECTS = \
  main.o \
  system_stm32f7xx.o \
  startup_stm32f767xx.o \
  GPIO.o \
  SPI.o \
  I2C.o \
#object files that we will compile to

vpath %.c SRC
vpath %.s ../bare_include/
vpath %.s ../bare_include/Source/KERNEL
vpath %.s ../bare_include/Source/CORE
vpath %.s ../bare_include/Source/EXTERNAL\ DEVICES
vpath %.s ../bare_include/Source/MATH
vpath %.s ../bare_include/Source/GUI
vpath %.s ../bare_include/Source/LCD
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
  -I../Bare_include/ \
  -I../Bare_include/Header/KERNEL \
  -I../Bare_include/Header/CORE \
  -I../Bare_include/Header/EXTERNAL\ DEVICES \
  -I../Bare_include/Header/MATH \
  -I../Bare_include/Header/GUI \
  -I../Bare_include/Header/LCD \
  -I../Bare_include/Header/UTILITIES \

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
#compile all .c files in SRC/ to .o in current directory
#dissassemble each file for debugging

%.o: %.s
	$(CC) -c $(CFLAGS) $< -o $@
	$(OBJDUMP) $(OBJDUMPFLAGS) $@ > $@.txt
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
