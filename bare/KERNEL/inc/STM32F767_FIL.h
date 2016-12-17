//
//
//
//
//



#ifndef STM32F767_FIL_H
#define STM32F767_FIL_H

#include "stm32f767xx.h"

#define FIL_MAXFATWIDTH 50
#define FIL_MOUNTFATWIDTH 10
#define FIL_FATWIDTHINC 10

extern void *FIL_FAT;

struct FIL
{
	uint8_t name[11];
	
	uint8_t attributes; //files directory

	uint16_t calender; //		y[7]/m[4]/d[5]
	uint16_t time; //		h[5]/m[6]/s[5]
	
	void *memory; //512 byte memory area pointer.
								//if file is bigger than 512 bytes, Then the last 4 bytes 
								//of the memory area point to the next memory area. Also, 
								//the memory area now only holds 508 bytes. The next area
								//will hold 512 or 508 bytes depending on the file size.

	uint32_t size; //used memory size in bytes.
};
//size 24 bytes

#define FIL_FAT_SIZE(FATWidth) (sizeof(struct FIL) * FATWidth + \
	sizeof(struct HEAP_TABLE))

uint32_t FIL_Init(uint32_t size);

#endif












