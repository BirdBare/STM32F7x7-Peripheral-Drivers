//
//
//
//
//




#include "STM32F767_CRC.h"


struct CRCxo
	CRCo = {&RCC->AHB1ENR,12,0,0,CRC};





int CRC_Config(struct CRCxo *CRCo, int CR, int INIT)
{
	volatile CRC_TypeDef * const CRCx = CRCo->CRCx;
	
	CRCx->INIT = INIT;
	CRCx->CR = CR;

	return 0;
}

void CRC_ConfigPolynomial(struct CRCxo *CRCo, int POL)
{
	CRCo->CRCx->POL = POL;
}

int CRC_ResetConfig(struct CRCxo *CRCo)
{
	CRCo->CRCx->CR |= CRC_CR_RESET;
	return 0;
}








