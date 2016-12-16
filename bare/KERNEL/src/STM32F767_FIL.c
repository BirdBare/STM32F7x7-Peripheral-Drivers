//
//
//
//
//



#include "STM32F767_FIL.h"
#include "STM32F767_STRING.h"
#include "STM32F767_BALLOC.h"
#include "STM32F767_KERNEL.h"
//#include "STM32F767_.h"

struct FIL **FIL_FAT = 0; //FIL File Allocation Table. Size set in Header file
/*

struct FIL
{
	uint8_t name[11]; // 8:3 name.ext 
	
	uint8_t attributes; //files directory. = 0 if file deleted
											//	[0] file attributes
											//	0 file
											//	1 folder
											//	[1:7] permissions.
											//	
	uint16_t calender; //		y[7]/m[4]/d[5]
	uint16_t time; //		h[5]/m[6]/s[5]
	
	void *memory; //512 byte memory area pointer.
								//if file is bigger than 512 bytes, Then the last 4 bytes 
								//of the memory area point to the next memory area. Also, 
								//the memory area now only holds 508 bytes. The next area
								//will hold 512 or 508 bytes depending on the file size.

	uint32_t size;
};
//size 24 bytes
*/

void FIL_Init(uint32_t size)
{
	FIL_FAT = fastballoc(FIL_FAT_SIZE(size));
	//get memory space for FIL_FATE
	
	((uint32_t *)FIL_FAT)[0] = size;
	((uint32_t *)FIL_FAT)[1] = (uint32_t)FIL_FAT + 12;
	//set size and start of first space free fat

	FIL_FAT = (void *)((uint32_t *)FIL_FAT + 2);
	//Increment over size and first space

	do
	{
		FIL_FAT[--size]->name[0] = '\0';
	} while(size != 0);
	//set all names zero
	

	//CREATE ROOT DIRECTORY

	String_SetString(FIL_FAT[0]->name,(uint8_t *)"root\0\0\0\0\0\0\0",11);
	///set name zero filled

	FIL_FAT[0]->attributes = 1;
	//set attributes

	//SET date and time

	FIL_FAT[0]->memory = balloc(512);
	//get and set memory

	FIL_FAT[0]->size = 0;
	//initial size always zero. 
}










