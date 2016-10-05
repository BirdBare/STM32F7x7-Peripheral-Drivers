TARGET = main
#our final binary file

DRIVER_INC = -I../core/arm \
             -I../core/st \
#included header files directory for running microcontroller
vpath %.c src
vpath %.s src
vpath %.c driver
vpath %.s driver
#set path for c and s files. For finding main.c in src.
DRIVER_OBJECTS = \
  startup_stm32f767xx.o \
  system_stm32f7xx.o \
  stm32f7xx_it.o \
  STM32F767_PERIPH.o \
#object files required to be compiled to run microcontroller

CORE_INC = \
  -I../bare/CORE/inc \
  -I../bare/EXTERNAL/inc \
  -I../bare/GUI/inc \
  -I../bare/KERNEL/inc \
  -I../bare/LCD/inc \
  -I../bare/MATH/inc \
  -I../bare/UTILITIES/inc \
#included header files directory to find general peripheral header files
vpath %.c ../bare/CORE/src
vpath %.s ../bare/CORE/src
vpath %.c ../bare/EXTERNAL/src
vpath %.s ../bare/EXTERNAL/src
vpath %.c ../bare/GUI/src
vpath %.s ../bare/GUI/src
vpath %.c ../bare/KERNEL/src
vpath %.s ../bare/KERNEL/src
vpath %.c ../bare/LCD/src
vpath %.s ../bare/LCD/src
vpath %.c ../bare/MATH/src
vpath %.s ../bare/MATH/src
vpath %.c ../bare/UTILITIES/src
vpath %.s ../bare/UTILITIES/src
#set path so we can find c and s files for peripherals
CORE_OBJECTS = \
  STM32F767_GPIO.o \
  STM32F767_SPI.o \
  STM32F767_I2C.o \
  STM32F767_SYSTICK.o \
#peripheral object files that we are going to use
  
SYSTEM_KERNEL_OBJECT = STM32F767_KERNEL.o
#Kernel Object file. Either KERNEL.o or NO_KERNEL.o

MAIN = main.o

OBJECTS = \
  $(DRIVER_OBJECTS) \
  $(CORE_OBJECTS) \
  $(SYSTEM_KERNEL_OBJECT) \
  STM32F767_BALLOC.o \
  STM32F767_XPT2046.o \
  STM32F767_HTU21D.o \
  $(MAIN) \
#object files that we will compile to

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
  -mthumb -mtune=cortex-m7\
  -Wno-unused-function \
  -Iinc \
  $(DRIVER_INC)\
  $(CORE_INC) \

LDFLAGS = \
  -mthumb -mcpu=cortex-m7 -mfpu=fpv5-sp-d16 -mfloat-abi=hard \
  -fdata-sections -ffunction-sections -ffast-math \
  -specs=nano.specs -Wl,-T,driver/STM32F767ZI_FLASH.ld \
  -Wl,--gc-sections,-Map=map.txt \
  -lc -lm -lnosys

OBJDUMPFLAGS = \
  -D

all: clean $(TARGET).bin tidy

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
	$(OBJDUMP) $(OBJDUMPFLAGS) $@ > $@.txt
	@echo  
#compile all .c files to .o
#dissassemble each file for debugging

%.o: %.s
	$(CC) -c $(CFLAGS) $< -o $@
	$(OBJDUMP) $(OBJDUMPFLAGS) $@ > $@.txt
	@echo 
#compile all .s files to .o

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

flash:
	st-flash write main.bin 0x8000000






