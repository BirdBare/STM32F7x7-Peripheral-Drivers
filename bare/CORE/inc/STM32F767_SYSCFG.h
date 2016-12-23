//
//
//
//
//



#ifndef STM32F767_SYSCFG_H
#define STM32F767_SYSCFG_H

#include "stm32f767xx.h"
#include "BARE_DEFINES.h"
//#include "STM32F767_.h"

struct SYSCFGxo
{
	volatile uint32_t * const clockreg;
	const uint8_t clockbitoffset;
	uint8_t unused1;
	uint16_t unused2;

	volatile SYSCFG_TypeDef * const SYSCFGx;
};

extern struct SYSCFGxo
	SYSCFGo;

int SYSCFG_Config(struct SYSCFGxo *SYSCFGo, int MEMRMP, int CBR, int CMPCR);

ALWAYS_INLINE int SYSCFG_ConfigMode(struct SYSCFGxo *SYSCFGo, int PMC)
{
	ASM(" str %0, [%1, #0x4]" :: "r" (PMC), "r" (SYSCFGo->SYSCFG);
}

int SYSCFG_ConfigEXTI(struct SYSCFGxo *SYSCFGo, int EXTIHigh, int EXTIMidHigh, 
	int EXTIMidLow, int EXTILow);





#endif
