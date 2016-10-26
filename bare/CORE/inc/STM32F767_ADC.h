//
//
//
//
//



#ifndef STM32F767_ADC_H
#define STM32F767_ADC_H

#include "BARE_STM32F767.h"
//#include "STM32F767_xxx.h"

#define ADC_SetCR2(ADCx, ADC_CR2) (ADCx)->CR2 = (ADC_CR2);

#define ADC_Configure(ADCx, ACR1, ACR2) \
  ADC_SetCR1(ADCx, ACR1); \
  ADC_SetCR2(ADCx,ACR2);

ALWAYS_INLINE void ADC_SetCR1(ADC_TypeDef *ADCx, uint32_t CR1)
{
  ASM("str r1, [r0, #4]"); 
}

ALWAYS_INLINE void SEND8(SPI_TypeDef *SPIx, uint8_t data)
{
  ASM("strb r1, [r0,#12]");
}







#endif
