//
//
//
//
//



#include "STM32F767_DMA.h"
//#include "STM32F767_.h"




//******************************************************************************
//	
//										 
//	
//******************************************************************************
uint32_t DMA_Config(struct DMAx_Streamxo *DMAx_Streamo, uint32_t CR, 
	uint32_t NDTR, uint32_t PAR, uint32_t M0AR, uint32_t M1AR, uint32_t FCR)
{
	volatile DMA_Stream_TypeDef * const DMAx_Streamx = DMAx_Streamo->DMAx_Streamx;

	if((DMAx_Streamx->CR & DMA_SxCR_EN) == 0)
	{
		DMAx_Streamx->FCR = FCR;
		DMAx_Streamx->M1AR = M1AR;
		DMAx_Streamx->M0AR = M0AR;
		DMAx_Streamx->PAR = PAR;
		DMAx_Streamx->NDTR = NDTR;
		DMAx_Streamx->CR = CR;
	
		return 0;
	}
	return DMA_CONFIG_ENABLED;
}



//******************************************************************************
//	
//										 
//	
//******************************************************************************
uint32_t DMA_ResetConfig(struct DMAx_Streamxo *DMAx_Streamo)
{
	volatile DMA_Stream_TypeDef * const DMAx_Streamx = DMAx_Streamo->DMAx_Streamx;

	if((DMAx_Streamx->CR & DMA_SxCR_EN) == 0)
	{
		uint32_t *clearflagreg = 
			(void *)(((uint32_t)DMAx_Streamx & ~255) + 
				DMAx_Streamo->flagregoffset + 8);
	
		*clearflagreg = 0b111101 << DMAx_Streamo->flagflagsoffset;

		DMAx_Streamx->CR = 0;
		DMAx_Streamx->NDTR = 0;
		DMAx_Streamx->PAR = 0;
		DMAx_Streamx->M0AR = 0;
		DMAx_Streamx->M1AR = 0;
		DMAx_Streamx->FCR = 0;

		return 0;
	}
	return DMA_CONFIG_ENABLED;
}



//******************************************************************************
//	
//										 
//	
//******************************************************************************
uint32_t DMA_Enable(struct DMAx_Streamxo *DMAx_Streamo)
{
	DMAx_Streamo->DMAx_Streamx->CR |= DMA_SxCR_EN;

	return 0;
}


//******************************************************************************
//	
//										 
//	
//******************************************************************************
uint32_t DMA_Disable(struct DMAx_Streamxo *DMAx_Streamo)
{
	DMAx_Streamo->DMAx_Streamx->CR &= ~DMA_SxCR_EN;

	return 0;
}











