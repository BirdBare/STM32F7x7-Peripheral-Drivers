//
//
//
//
//



#ifndef STM32F767_RNG_H
#define STM32F767_RNG_H

#include "stm32f767xx.h"
#include "BARE_DEFINES.h"
//#include "STM32F767_.h"

struct RNGxo
{
	volatile uint32_t * const clockreg;
	const uint8_t clockbitoffset;
	uint8_t unused1;
	uint16_t unused2;

	volatile RNG_TypeDef * const RNGx;
};

extern struct RNGxo
	RNGo;

#define RNG_CONFIG_ENABLED 1
int RNG_Config(struct RNGxo *RNGo, int CR);
int RNG_ResetConfig(struct RNGxo *RNGo);
void RNG_Enable(struct RNGxo *RNGo);
void RNG_Disable(struct RNGxo *RNGo);

ALWAYS_INLINE int RNG_Get32(struct RNGxo *RNGo)
{
	uint32_t ret;
	ASM(" ldr %0, [%1, #0x8]" : "=r" (ret) : "r" (RNGo->RNGx));
	return ret;
}






#endif
