//
//
//
//
//



#ifndef STM32F767_DMA_H
#define STM32F767_DMA_H

#include "stm32f767xx.h"
#include "BARE_DEFINES.h"
//#include "STM32F767_.h"


//******************************************************************************
//
//		Redefinition of DMA structure to include stream.
//
//******************************************************************************

//to get DMA1 Base address. Take DMAx_Streamx & ~255.



struct DMAx_Streamxo
{
	volatile uint32_t * const clockreg;
	const uint8_t clockbitoffset;

	const uint8_t flagregoffset;
	const uint8_t flagflagsoffset;
	uint8_t unused1;

	volatile DMA_Stream_TypeDef * const DMAx_Streamx;
};

#define DMA_CONFIG_ENABLED 1

uint32_t DMA_Config(struct DMAx_Streamxo *DMAx_Streamo, uint32_t CR, 
	uint32_t NDTR, uint32_t PAR, uint32_t M0AR, uint32_t M1AR, uint32_t FCR);

uint32_t DMA_ResetConfig(struct DMAx_Streamxo *DMAx_Streamo);

uint32_t DMA_Enable(struct DMAx_Streamxo *DMAx_Streamo);

uint32_t DMA_Disable(struct DMAx_Streamxo *DMAx_Streamo);




#endif
