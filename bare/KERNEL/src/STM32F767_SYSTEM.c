//
///
//
//
//




#include "stm32f7xx.h"
#include "STM32F767_SYSTICK.h"
#include "STM32F767_KERNEL.h"
#include "STM32F767_BALLOC.h"
#include "STM32F767_FIL.h"
#include "stm32f7xx_it.h"

__attribute__((section("._isr.VECTOR")))
void *ISR_VECTORS[0];






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
#define PLL_Q 4

/* DSI = VCO / PLL_R */
#define PLL_R 7

void Reset_Handler(void);
void SysTick_Handler(void);
void PendSV_Handler(void);


void SystemInit(void)
{
	//disable Interrupts
  RCC->CIR = 0x00000000;
  
	//set sys clock 192mhz
	SetSysClock();

	//enable ITCM AND DTCM
  SCB->ITCMCR = 1;
  SCB->DTCMCR = 1;

	
	ISR_VECTORS_STRUCT->SysTick_Handler = SysTick_Handler;
	ISR_VECTORS_STRUCT->PendSV_Handler = PendSV_Handler;
	ISR_VECTORS_STRUCT->HardFault_Handler = HardFault_Handler;

	SCB->VTOR = (uint32_t)&ISR_VECTORS[-16];

	//enable FPU
	SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  
	
	//Start System Timer
  SysTick_EnableTimer();

	//init heap
	extern void *_edata asm("_edata");
	extern void *_eSRAM asm("_eSRAM");
	_edata = &_edata;
	_eSRAM = &_eSRAM;

	extern void *pheap asm("_SRAMend");
	KERNEL_ProcessHeap = (struct HEAP_TABLE *)&pheap;
	InitHeap(KERNEL_ProcessHeap, 0x20080000 - (uint32_t)_eSRAM);
	extern void *theap asm("_DTCMend");
	KERNEL_ThreadHeap =  (struct HEAP_TABLE *)&theap;
	InitHeap(KERNEL_ThreadHeap, 30*1024);
	KERNEL_FastHeap = (void *)((uint32_t)KERNEL_ThreadHeap + 30*1024 + 
		sizeof(struct HEAP_TABLE));
	InitHeap(KERNEL_FastHeap, 0x20020000 - (uint32_t)KERNEL_FastHeap - 30*1024 -
		sizeof(struct HEAP_TABLE));

	//Init FIL FILE System
	FIL_Init(10);
}

void SetSysClock(void)
{
    /*Enable the Power Controller Clock*/
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;

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


    PWR->CR1 |= PWR_CR1_VOS | PWR_CR1_ODEN;
		//Reset Voltage scaling to highest and enable overdrive mode.

		while((PWR->CSR1 & PWR_CSR1_ODRDY) == 0)
		{
			asm volatile("");
		}
		//wait for overdrive to be ready

    PWR->CR1 |= PWR_CR1_ODSWEN;
		//switch to overdrive regulator

		while((PWR->CSR1 & PWR_CSR1_ODSWRDY) == 0)
		{
			asm volatile("");
		}
		//wait till switch is done

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




