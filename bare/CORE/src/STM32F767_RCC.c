//
//
//
//
//


#include "STM32F767_RCC.h"

#define RCC_EnableClockAHB1(AHB1_CLOCK_x) \
	RCC->AHB1ENR |= AHB1_CLOCK_x
#define RCC_EnableClockAHB2(AHB2_CLOCK_x) \
	RCC->AHB2ENR |= AHB2_CLOCK_x
#define RCC_EnableClockAPB1(APB1_CLOCK_x) \
	RCC->APB1ENR |= APB1_CLOCK_x
#define RCC_EnableClockAPB2(APB2_CLOCK_x) \
	RCC->APB2ENR |= APB2_CLOCK_x

#define RCC_DisableClockAHB1(AHB1_CLOCK_x) \
	RCC->AHB1RSTR &= ~AHB1_CLOCK_x
#define RCC_DisableClockAHB2(AHB2_CLOCK_x) \
	RCC->AHB2RSTR &= ~AHB2_CLOCK_x
#define RCC_DisableClockAPB1(APB1_CLOCK_x) \
	RCC->APB1RSTR &= ~APB1_CLOCK_x
#define RCC_DisableClockAPB2(APB2_CLOCK_x) \
	RCC->APB2RSTR &= ~APB2_CLOCK_x

