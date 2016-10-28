//
//
//
//
//



#ifndef STM32F767_ADC_H
#define STM32F767_ADC_H

#include "stm32f7xx.h"
#include "BARE_STM32F767.h"
//#include "STM32F767_xxx.h"

  //Register Functions
ALWAYS_INLINE void ADC_SetSR(ADC_TypeDef *ADCx, uint32_t Data);
ALWAYS_INLINE uint32_t ADC_GetSR(ADC_TypeDef *ADCx);

ALWAYS_INLINE void ADC_SetCR1(ADC_TypeDef *ADCx, uint32_t Data);
ALWAYS_INLINE uint32_t ADC_GetCR1(ADC_TypeDef *ADCx);
ALWAYS_INLINE void ADC_SetBitsCR1(ADC_TypeDef *ADCx, uint32_t Data);
ALWAYS_INLINE void ADC_ResetBitsCR1(ADC_TypeDef *ADCx, uint32_t Data);

ALWAYS_INLINE void ADC_SetCR2(ADC_TypeDef *ADCx, uint32_t Data);
ALWAYS_INLINE uint32_t ADC_GetCR2(ADC_TypeDef *ADCx);
ALWAYS_INLINE void ADC_SetBitsCR2(ADC_TypeDef *ADCx, uint32_t Data);
ALWAYS_INLINE void ADC_ResetBitsCR2(ADC_TypeDef *ADCx, uint32_t Data);

ALWAYS_INLINE void ADC_SetSMPR1(ADC_TypeDef *ADCx, uint32_t Data);
ALWAYS_INLINE uint32_t ADC_GetSMPR1(ADC_TypeDef *ADCx);
ALWAYS_INLINE void ADC_SetBitsSMPR1(ADC_TypeDef *ADCx, uint32_t Data);
ALWAYS_INLINE void ADC_ResetBitsSMPR1(ADC_TypeDef *ADCx, uint32_t Data);

ALWAYS_INLINE void ADC_SetSMPR2(ADC_TypeDef *ADCx, uint32_t Data);
ALWAYS_INLINE uint32_t ADC_GetSMPR2(ADC_TypeDef *ADCx);
ALWAYS_INLINE void ADC_SetBitsSMPR2(ADC_TypeDef *ADCx, uint32_t Data);
ALWAYS_INLINE void ADC_ResetBitsSMPR2(ADC_TypeDef *ADCx, uint32_t Data);

ALWAYS_INLINE void ADC_SetJOFR1(ADC_TypeDef *ADCx, uint32_t Data);
ALWAYS_INLINE uint32_t ADC_GetJOFR1(ADC_TypeDef *ADCx);
ALWAYS_INLINE void ADC_SetBitsJOFR1(ADC_TypeDef *ADCx, uint32_t Data);
ALWAYS_INLINE void ADC_ResetBitsJOFR1(ADC_TypeDef *ADCx, uint32_t Data);

ALWAYS_INLINE void ADC_SetJOFR2(ADC_TypeDef *ADCx, uint32_t Data);
ALWAYS_INLINE uint32_t ADC_GetJOFR2(ADC_TypeDef *ADCx);
ALWAYS_INLINE void ADC_SetBitsJOFR2(ADC_TypeDef *ADCx, uint32_t Data);
ALWAYS_INLINE void ADC_ResetBitsJOFR2(ADC_TypeDef *ADCx, uint32_t Data);

ALWAYS_INLINE void ADC_SetJOFR3(ADC_TypeDef *ADCx, uint32_t Data);
ALWAYS_INLINE uint32_t ADC_GetJOFR3(ADC_TypeDef *ADCx);
ALWAYS_INLINE void ADC_SetBitsJOFR3(ADC_TypeDef *ADCx, uint32_t Data);
ALWAYS_INLINE void ADC_ResetBitsJOFR3(ADC_TypeDef *ADCx, uint32_t Data);

ALWAYS_INLINE void ADC_SetJOFR4(ADC_TypeDef *ADCx, uint32_t Data);
ALWAYS_INLINE uint32_t ADC_GetJOFR4(ADC_TypeDef *ADCx);
ALWAYS_INLINE void ADC_SetBitsJOFR4(ADC_TypeDef *ADCx, uint32_t Data);
ALWAYS_INLINE void ADC_ResetBitsJOFR4(ADC_TypeDef *ADCx, uint32_t Data);

ALWAYS_INLINE void ADC_SetHTR(ADC_TypeDef *ADCx, uint32_t Data);
ALWAYS_INLINE uint32_t ADC_GetHTR(ADC_TypeDef *ADCx);
ALWAYS_INLINE void ADC_SetBitsHTR(ADC_TypeDef *ADCx, uint32_t Data);
ALWAYS_INLINE void ADC_ResetBitsHTR(ADC_TypeDef *ADCx, uint32_t Data);

ALWAYS_INLINE void ADC_SetLTR(ADC_TypeDef *ADCx, uint32_t Data);
ALWAYS_INLINE uint32_t ADC_GetLTR(ADC_TypeDef *ADCx);
ALWAYS_INLINE void ADC_SetBitsLTR(ADC_TypeDef *ADCx, uint32_t Data);
ALWAYS_INLINE void ADC_ResetBitsLTR(ADC_TypeDef *ADCx, uint32_t Data);

ALWAYS_INLINE void ADC_SetSQR1(ADC_TypeDef *ADCx, uint32_t Data);
ALWAYS_INLINE uint32_t ADC_GetSQR1(ADC_TypeDef *ADCx);
ALWAYS_INLINE void ADC_SetBitsSQR1(ADC_TypeDef *ADCx, uint32_t Data);
ALWAYS_INLINE void ADC_ResetBitsSQR1(ADC_TypeDef *ADCx, uint32_t Data);

ALWAYS_INLINE void ADC_SetSQR2(ADC_TypeDef *ADCx, uint32_t Data);
ALWAYS_INLINE uint32_t ADC_GetSQR2(ADC_TypeDef *ADCx);
ALWAYS_INLINE void ADC_SetBitsSQR2(ADC_TypeDef *ADCx, uint32_t Data);
ALWAYS_INLINE void ADC_ResetBitsSQR2(ADC_TypeDef *ADCx, uint32_t Data);

ALWAYS_INLINE void ADC_SetSQR3(ADC_TypeDef *ADCx, uint32_t Data);
ALWAYS_INLINE uint32_t ADC_GetSQR3(ADC_TypeDef *ADCx);
ALWAYS_INLINE void ADC_SetBitsSQR3(ADC_TypeDef *ADCx, uint32_t Data);
ALWAYS_INLINE void ADC_ResetBitsSQR3(ADC_TypeDef *ADCx, uint32_t Data);

ALWAYS_INLINE void ADC_SetJSQR(ADC_TypeDef *ADCx, uint32_t Data);
ALWAYS_INLINE uint32_t ADC_GetJSQR(ADC_TypeDef *ADCx);
ALWAYS_INLINE void ADC_SetBitsJSQR(ADC_TypeDef *ADCx, uint32_t Data);
ALWAYS_INLINE void ADC_ResetBitsJSQR(ADC_TypeDef *ADCx, uint32_t Data);

ALWAYS_INLINE uint32_t ADC_GetJDR1(ADC_TypeDef *ADCx);

ALWAYS_INLINE uint32_t ADC_GetJDR2(ADC_TypeDef *ADCx);

ALWAYS_INLINE uint32_t ADC_GetJDR3(ADC_TypeDef *ADCx);

ALWAYS_INLINE uint32_t ADC_GetJDR4(ADC_TypeDef *ADCx);

ALWAYS_INLINE uint32_t ADC_GetDR(ADC_TypeDef *ADCx);


#define ADC1_CLOCK RCC_APB2ENR_ADC1
#define ADC2_CLOCK RCC_APB2ENR_ADC2
#define ADC3_CLOCK RCC_APB2ENR_ADC3

#define ADC_EnableClock(ADCx_CLOCK) \
  RCC_SetBitsAPB2ENR(RCC,ADCx_CLOCK)

#define ADC_DisableClock(ADCx_CLOCK) \
  RCC_SetAPB2RSTR(RCC,ADCx_CLOCK)


#define ADC_On(ADCx) ADC_SetBitsCR2(ADCx, ADC_CR2_ADON)
#define ADC_Off(ADCx) ADC_ResetBitsCR2(ADCx, ~ADC_CR2_ADON)

#define ADC_ConfigADC(ADCx,ADC_CR1_x,ADC_CR2_x) \
  do \
  { \
    ADC_SetCR2(ADCx,ADC_CR2_x); \
    ADC_SetCR1(ADCx,ADC_CR1_x); \
  }while(0)
 
#define ADC_ConfigRegularSequence(ADCx, SequenceLength, \
                                   SequenceHigh,SequenceMed,SequenceLow) \
  do \
  { \
    ADC_SETSQR1(ADCx, (SequenceHigh) | (SequenceLength)); \
    ADC_SETSQR2(ADCx, SequenceMed); \
    ADC_SETSQR3(ADCx, SequenceLow); \
  }while(0)

#define ADC_ConfigInjectedSequence(ADCx,SequenceLength, Sequence) \
  ADC_SetJSQR(ADCx,(Sequence) | (SequenceLength))

#define ADC_StartRegularConversion(ADCx) \
  ADC_SetBitsCR2(ADCx,ADC_CR2_SWSTART)

#define ADC_StartInjectedConversion(ADCx) \
  ADC_SetBitsCR2(ADCx,ADC_CR2_JSWSTART)

#define ADC_GetRegularData(ADCx) \
ADC_GetDR(ADCx)

#define ADC_GetInjectedData1(ADCx) \
ADC_GetJDR1(ADCx)

#define ADC_GetInjectedData2(ADCx) \
ADC_GetJDR2(ADCx)

#define ADC_GetInjectedData3(ADCx) \
ADC_GetJDR3(ADCx)

#define ADC_GetInjectedData4(ADCx) \
ADC_GetJDR4(ADCx)

#define ADC_EnableWatchdog(ADCx,ADC_CR1_x,ADC_HIGH,ADC_LOW) \
do \
{ \
  ADC_SetBitsCR1(ADCx,ADC_CR1_x); \
  ADC_SetHTR(ADCx,ADC_HIGH); \
  ADC_SetLTR(ADCx,ADC_LOW); \
}while(0)

#define ADC_DisableWatchdog(ADCx) \
  ADC_ResetBitsCR1(ADCx, ~(ADC_CR2_JAWDEN | ADC_CR2_AWDEN))

#define ADC_ResetWatchdog(ADCx) \
  ADC_ResetBitsCR1(ADCx, ~(ADC_CR2_AWDCH | ADC_CR2_AWDSGL \
    | ADC_CR2_AWDIE | ADC_CR2_AWDEN | ADC_CR2_JAWDEN))




















  //  ADCx->SR Functions 
ALWAYS_INLINE void ADC_SetSR(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->SR = Data;
}
ALWAYS_INLINE uint32_t ADC_GetSR(ADC_TypeDef *ADCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x0]" : "=r" (ret) : "r" (ADCx));
  return ret;
}


  //  ADCx->CR1 Functions 
ALWAYS_INLINE void ADC_SetCR1(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->CR1 = Data;
}
ALWAYS_INLINE uint32_t ADC_GetCR1(ADC_TypeDef *ADCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x4]" : "=r" (ret) : "r" (ADCx));
  return ret;
}
ALWAYS_INLINE void ADC_SetBitsCR1(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->CR1 |= Data;
}
ALWAYS_INLINE void ADC_ResetBitsCR1(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->CR1 &= Data;
}



  //  ADCx->CR2 Functions 
ALWAYS_INLINE void ADC_SetCR2(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->CR2 = Data;
}
ALWAYS_INLINE uint32_t ADC_GetCR2(ADC_TypeDef *ADCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x8]" : "=r" (ret) : "r" (ADCx));
  return ret;
}
ALWAYS_INLINE void ADC_SetBitsCR2(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->CR2 |= Data;
}
ALWAYS_INLINE void ADC_ResetBitsCR2(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->CR2 &= Data;
}



  //  ADCx->SMPR1 Functions 
ALWAYS_INLINE void ADC_SetSMPR1(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->SMPR1 = Data;
}
ALWAYS_INLINE uint32_t ADC_GetSMPR1(ADC_TypeDef *ADCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0xc]" : "=r" (ret) : "r" (ADCx));
  return ret;
}
ALWAYS_INLINE void ADC_SetBitsSMPR1(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->SMPR1 |= Data;
}
ALWAYS_INLINE void ADC_ResetBitsSMPR1(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->SMPR1 &= Data;
}



  //  ADCx->SMPR2 Functions 
ALWAYS_INLINE void ADC_SetSMPR2(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->SMPR2 = Data;
}
ALWAYS_INLINE uint32_t ADC_GetSMPR2(ADC_TypeDef *ADCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x10]" : "=r" (ret) : "r" (ADCx));
  return ret;
}
ALWAYS_INLINE void ADC_SetBitsSMPR2(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->SMPR2 |= Data;
}
ALWAYS_INLINE void ADC_ResetBitsSMPR2(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->SMPR2 &= Data;
}



  //  ADCx->JOFR1 Functions 
ALWAYS_INLINE void ADC_SetJOFR1(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->JOFR1 = Data;
}
ALWAYS_INLINE uint32_t ADC_GetJOFR1(ADC_TypeDef *ADCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x14]" : "=r" (ret) : "r" (ADCx));
  return ret;
}
ALWAYS_INLINE void ADC_SetBitsJOFR1(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->JOFR1 |= Data;
}
ALWAYS_INLINE void ADC_ResetBitsJOFR1(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->JOFR1 &= Data;
}



  //  ADCx->JOFR2 Functions 
ALWAYS_INLINE void ADC_SetJOFR2(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->JOFR2 = Data;
}
ALWAYS_INLINE uint32_t ADC_GetJOFR2(ADC_TypeDef *ADCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x18]" : "=r" (ret) : "r" (ADCx));
  return ret;
}
ALWAYS_INLINE void ADC_SetBitsJOFR2(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->JOFR2 |= Data;
}
ALWAYS_INLINE void ADC_ResetBitsJOFR2(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->JOFR2 &= Data;
}



  //  ADCx->JOFR3 Functions 
ALWAYS_INLINE void ADC_SetJOFR3(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->JOFR3 = Data;
}
ALWAYS_INLINE uint32_t ADC_GetJOFR3(ADC_TypeDef *ADCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x1c]" : "=r" (ret) : "r" (ADCx));
  return ret;
}
ALWAYS_INLINE void ADC_SetBitsJOFR3(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->JOFR3 |= Data;
}
ALWAYS_INLINE void ADC_ResetBitsJOFR3(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->JOFR3 &= Data;
}



  //  ADCx->JOFR4 Functions 
ALWAYS_INLINE void ADC_SetJOFR4(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->JOFR4 = Data;
}
ALWAYS_INLINE uint32_t ADC_GetJOFR4(ADC_TypeDef *ADCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x20]" : "=r" (ret) : "r" (ADCx));
  return ret;
}
ALWAYS_INLINE void ADC_SetBitsJOFR4(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->JOFR4 |= Data;
}
ALWAYS_INLINE void ADC_ResetBitsJOFR4(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->JOFR4 &= Data;
}



  //  ADCx->HTR Functions 
ALWAYS_INLINE void ADC_SetHTR(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->HTR = Data;
}
ALWAYS_INLINE uint32_t ADC_GetHTR(ADC_TypeDef *ADCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x24]" : "=r" (ret) : "r" (ADCx));
  return ret;
}
ALWAYS_INLINE void ADC_SetBitsHTR(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->HTR |= Data;
}
ALWAYS_INLINE void ADC_ResetBitsHTR(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->HTR &= Data;
}



  //  ADCx->LTR Functions 
ALWAYS_INLINE void ADC_SetLTR(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->LTR = Data;
}
ALWAYS_INLINE uint32_t ADC_GetLTR(ADC_TypeDef *ADCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x28]" : "=r" (ret) : "r" (ADCx));
  return ret;
}
ALWAYS_INLINE void ADC_SetBitsLTR(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->LTR |= Data;
}
ALWAYS_INLINE void ADC_ResetBitsLTR(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->LTR &= Data;
}



  //  ADCx->SQR1 Functions 
ALWAYS_INLINE void ADC_SetSQR1(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->SQR1 = Data;
}
ALWAYS_INLINE uint32_t ADC_GetSQR1(ADC_TypeDef *ADCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x2c]" : "=r" (ret) : "r" (ADCx));
  return ret;
}
ALWAYS_INLINE void ADC_SetBitsSQR1(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->SQR1 |= Data;
}
ALWAYS_INLINE void ADC_ResetBitsSQR1(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->SQR1 &= Data;
}



  //  ADCx->SQR2 Functions 
ALWAYS_INLINE void ADC_SetSQR2(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->SQR2 = Data;
}
ALWAYS_INLINE uint32_t ADC_GetSQR2(ADC_TypeDef *ADCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x30]" : "=r" (ret) : "r" (ADCx));
  return ret;
}
ALWAYS_INLINE void ADC_SetBitsSQR2(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->SQR2 |= Data;
}
ALWAYS_INLINE void ADC_ResetBitsSQR2(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->SQR2 &= Data;
}



  //  ADCx->SQR3 Functions 
ALWAYS_INLINE void ADC_SetSQR3(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->SQR3 = Data;
}
ALWAYS_INLINE uint32_t ADC_GetSQR3(ADC_TypeDef *ADCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x34]" : "=r" (ret) : "r" (ADCx));
  return ret;
}
ALWAYS_INLINE void ADC_SetBitsSQR3(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->SQR3 |= Data;
}
ALWAYS_INLINE void ADC_ResetBitsSQR3(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->SQR3 &= Data;
}



  //  ADCx->JSQR Functions 
ALWAYS_INLINE void ADC_SetJSQR(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->JSQR = Data;
}
ALWAYS_INLINE uint32_t ADC_GetJSQR(ADC_TypeDef *ADCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x38]" : "=r" (ret) : "r" (ADCx));
  return ret;
}
ALWAYS_INLINE void ADC_SetBitsJSQR(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->JSQR |= Data;
}
ALWAYS_INLINE void ADC_ResetBitsJSQR(ADC_TypeDef *ADCx, uint32_t Data)
{
  ADCx->JSQR &= Data;
}



  //  ADCx->JDR1 Functions 
ALWAYS_INLINE uint32_t ADC_GetJDR1(ADC_TypeDef *ADCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x3c]" : "=r" (ret) : "r" (ADCx));
  return ret;
}
ALWAYS_INLINE uint32_t ADC_GetJDR2(ADC_TypeDef *ADCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x40]" : "=r" (ret) : "r" (ADCx));
  return ret;
}
ALWAYS_INLINE uint32_t ADC_GetJDR3(ADC_TypeDef *ADCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x44]" : "=r" (ret) : "r" (ADCx));
  return ret;
}
ALWAYS_INLINE uint32_t ADC_GetJDR4(ADC_TypeDef *ADCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x48]" : "=r" (ret) : "r" (ADCx));
  return ret;
}
ALWAYS_INLINE uint32_t ADC_GetDR(ADC_TypeDef *ADCx)
{
  uint32_t ret;
  ASM(" ldr %0, [%1, #0x4c]" : "=r" (ret) : "r" (ADCx));
  return ret;
}







#endif
