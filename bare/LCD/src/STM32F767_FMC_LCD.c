//
//
//
//
//




#include "STM32F767_FMC_LCD.h"
#include "STM32F767_RCC.h"
#include "STM32F767_FMC.h"

volatile uint16_t *LCD_Command = (volatile uint16_t *)0x60000000;

volatile uint16_t *LCD_Data = 
  (volatile uint16_t*)0b01100000000100000000000000000000;

/*void LCD_WriteSetting(uint16_t LCD_SETTINGREG, uint16_t LCD_DATA)
{
  *LCD_Command = (uint16_t)LCD_SETTINGREG;
  *LCD_Data = (uint16_t)LCD_DATA;
}*/

/*
  LCD_EnableGeneralPins(); 
Address Pin = PE3  

D0 = PD14
D1 = PD15
D2 = PD0
D3 = PD1
D4 = PE7
D5 = PE8
D6 = PE9
D7 = PE10
D8 = PE11
D9 = PE12
D10 = PE13
D11 = PE14
D12 = PE15
D13 = PD8
D14 = PD9
D15 = PD10

NE1 = PD7

NOE = PD4
NWE = PD5
*/

void LCD_EnableFMC(uint32_t FMC_BusWidth, uint32_t FMC_BusTurn,
  uint32_t FMC_DataSetup, uint32_t FMC_AddSetup)
{
   __DSB();
  MPU_Enable();
  MPU_SetRegion(7,0x60000000,1,0b11,0b010000,27);
  MPU_EnableRegion(7);
  __DSB();
  //Makes Bank1 a device so all commands and data will be sent.  

  RCC_EnableClock((struct RCCxo *)&NOR_PSRAM1o);

	NOR_PSRAM1o.NOR_PSRAMx->BCR = 0;

	NOR_PSRAM_Config(&NOR_PSRAM1o, 
		FMC_AsyncWait_OFF | FMC_ExtendedMode_OFF | FMC_WriteEnable_ON | 
			FMC_WaitPolarity_LOW | FMC_BusWidth, 
    FMC_AccessMode_A | FMC_BusTurn | FMC_DataSetup | FMC_AddSetup, 0);

  NOR_PSRAM_Enable(&NOR_PSRAM1o);

}









