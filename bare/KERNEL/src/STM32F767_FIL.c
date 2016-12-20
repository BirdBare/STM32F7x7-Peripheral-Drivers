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

void *FIL_FAT = 0; //FIL File Allocation Table. Size set in Header file
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
uint32_t FIL_CreateFile(); 

#define FIL_ERROR_MKFAT 1 //error creating FAT table

uint32_t FIL_Init(uint32_t size)
{
	
	if(!(FIL_FAT = fastballoc(FIL_FAT_SIZE(size))))
		return FIL_ERROR_MKFAT;
	//get memory space for FIL_FATE. return if no ram available.
	
	struct FIL *FIL = (void *)((uint32_t)FIL_FAT + sizeof(struct HEAP_TABLE));
	//set FIL pointer for emptying each file space
	
	((struct HEAP_TABLE *)FIL_FAT)->freeheap = (void *)FIL + sizeof(struct FIL);
	((struct HEAP_TABLE *)FIL_FAT)->size = size;
	//set size and start of first space free fat

	uint32_t count = 1;	
	do
	{
		*(uint32_t *)(&FIL[count]) = (uint32_t)&FIL[count + 1];
		//set empty flag and next empty space address
		
		count = count + 1;
	} while(count < size);
	//Set next empty space in chain

	*((uint32_t *)(&FIL[count - 1])) = 0;
	//set last empty space in chain


	//CREATE ROOT DIRECTORY

	String_SetString(FIL->name,(uint8_t *)"/",2);
	//copy 11 chars. will copy whole

	FIL->attributes = 1;

	//date and time

	FIL->memory = balloc(512);

	FIL->size = 0;
	//root directory always starts as zero size

	return 0;
}

uint32_t FIL_CreateFile(uint8_t *path, uint32_t attributes, 
	uint32_t size)
{
	//CHECK HERE
	struct FIL *FIL = (void *)(uint32_t)FIL_FAT + sizeof(struct HEAP_TABLE);
		
	
	
	//check if path is valid to new file



	if(!(FIL = ((struct HEAP_TABLE *)FIL_FAT)->freeheap))
		return 1;
	//get first free space. return error if no space available.
	//soon resize.

	((struct HEAP_TABLE *)FIL_FAT)->freeheap = (void *)*(uint32_t *)FIL;
	//set next free heap

	//Set New File into Fil Structure
	String_SetString(FIL->name,path,11);
		//copy 11 chars. will copy whole

	FIL->attributes = attributes;

	//date and time

	FIL->memory = balloc(512);

	FIL->size = size;

	return 0;
}

uint32_t FIL_DeleteFile(uint8_t *path)
{


	return 0;
}



//uint32_t FIL_DIRECTORY_WRITE(void memeory,dd









