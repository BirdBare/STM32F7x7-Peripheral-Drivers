//
///
//
//
//




#include "stm32f7xx.h"
#include "STM32F767_SYSTICK.h"

  #define HSI_VALUE    ((uint32_t)16000000) /*!< Value of the Internal oscillator in Hz*/



#define VECT_TAB_OFFSET  0x00 /*!< Vector Table base offset field. 
  */
#undef FLASH_BASE
#define FLASH_BASE FLASHITCM_BASE


  #define _FCPU_INITIAL 192000000
  uint32_t _FCPU = _FCPU_INITIAL;
  uint32_t _FAHB = _FCPU_INITIAL;
  uint32_t _FAPB1 = _FCPU_INITIAL / 4;
  uint32_t _FAPB2 = _FCPU_INITIAL / 2;
  


/* VCO = inputFreq / PLL_M * PLL_N */
#define PLL_M 8
#define PLL_N 192

/* HCLK = VCO / PLL_P */
#define PLL_P 2

/* USB, SDIO, RNG = VCO / PLL_Q */
#define PLL_Q 8

/* DSI = VCO / PLL_R */
#define PLL_R 7


void SystemInit(void)
{
	//disable Interrupts
  RCC->CIR = 0x00000000;

	// Vector Table Relocation in Internal FLASH
  SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET; 
  
	//set sys clock 192mhz
	SetSysClock();

	//enable ITCM AND DTCM
  SCB->ITCMCR = 1;
  SCB->DTCMCR = 1;

	//enable FPU
	SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  
	
  SysTick_EnableTimer();


}

void SetSysClock(void)
{
  /* Enable HSI */
  RCC->CR |= ((uint32_t)RCC_CR_HSION);
 
    /* HCLK = SYSCLK / 1*/
    RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
      
    /* PCLK2 = HCLK / 2*/
    RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;
    
    /* PCLK1 = HCLK / 4*/
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;

    /* Configure the main PLL */
    RCC->PLLCFGR = PLL_M | (PLL_N << 6) | (((PLL_P >> 1) -1) << 16) |
                   (RCC_PLLCFGR_PLLSRC_HSI) | (PLL_Q << 24) | (PLL_R << 28);

    /* Enable the main PLL */
    RCC->CR |= RCC_CR_PLLON;

    /*Enable the Power Controller Clock*/
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;

    /* Disable Voltage scaling bit*/
    PWR->CR1 |= PWR_CR1_VOS;

    /* OVERDRIVE MODE NOT NEEDED UNLESS 216Mhz */

    /* Configure Flash wait state */
    FLASH->ACR |= FLASH_ACR_LATENCY_6WS |  FLASH_ACR_ARTEN | FLASH_ACR_PRFTEN;    

    /* Wait till the main PLL is ready */
    while((RCC->CR & RCC_CR_PLLRDY) == 0)
    { 
      asm("");
    }

    /* Select the main PLL as system clock source */
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
    RCC->CFGR |= RCC_CFGR_SW_PLL;

    /* Wait till the main PLL is used as system clock source */
    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS ) != RCC_CFGR_SWS_PLL);
    {
    }
}




