//
//
//
//
//



#ifndef STM32F767_TIM_H
#define STM32F767_TIM_H

#include "stm32f7xx.h"
//#include "STM32F767_xxx.h"

#define RCC_TIM1 RCC_APB2ENR_TIM1EN
#define RCC_TIM8 RCC_APB2ENR_TIM8EN
#define RCC_TIM9 RCC_APB2ENR_TIM9EN
#define RCC_TIM10 RCC_APB2ENR_TIM10EN
#define RCC_TIM11 RCC_APB2ENR_TIM11EN
//APB2 max 108mhz


#define RCC_TIM2 RCC_APB1ENR_TIM2EN
#define RCC_TIM3 RCC_APB1ENR_TIM3EN
#define RCC_TIM4 RCC_APB1ENR_TIM4EN
#define RCC_TIM5 RCC_APB1ENR_TIM5EN
#define RCC_TIM6 RCC_APB1ENR_TIM6EN
#define RCC_TIM7 RCC_APB1ENR_TIM7EN
#define RCC_TIM12 RCC_APB1ENR_TIM12EN
#define RCC_TIM13 RCC_APB1ENR_TIM13EN
#define RCC_TIM14 RCC_APB1ENR_TIM14EN
//APB1 max 54mhz

#define TIM_EnableTimer(TIMx, TIM_CR1, TIM_CR2, TIM_DIER, TIM_PSC, TIM_ARR)\
  _TIM_EnableTimer(TIMx, ((uint32_t)((TIM_CR1) | 1) << 16) | (TIM_CR2), \
    (TIM_DIER), ((uint32_t)(TIM_PSC) << 16) | (TIM_ARR))
void _TIM_EnableTimer(TIM_TypeDef *TIMx, uint32_t TIM_CR1_CR2,
   uint16_t TIM_DIER, uint32_t TIM_PSC_ARR);

#define TIM_EnableUpCounter(TIMx, InterruptEnable, DMAEnable, \
  UpdateOnOverflowOnly, Master, Prescaler, NumTicks) \
    TIM_EnableTimer(TIMx, UpdateOnOverflowOnly << 2, Master << 4, \
      InterruptEnable | DMAEnable, Prescaler, NumTicks)

#define TIM_EnablePulse(TIMx, InterruptEnable, DMAEnable, \
  UpdateOnOverflowOnly, Master, Prescaler, NumTicks) \
    TIM_EnableTimer(TIMx, TIM_CR1_OPM | (UpdateOnOverflowOnly << 2), \
    Master << 4, InterruptEnable | DMAEnable, Prescaler, NumTicks)






#endif
