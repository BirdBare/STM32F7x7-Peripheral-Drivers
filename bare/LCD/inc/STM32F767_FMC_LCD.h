//
//
//
//
//



#ifndef STM32F767_FMC_LCD_H
#define STM32F767_FMC_LCD_H

#include "stm32f7xx.h"
#include "STM32F767_GPIO.h"
#include "STM32F767_FMC.h"
#include "STM32F767_MPU.h"
#include "STM32F767_SYSTICK.h"


#define LCD_RSTPIN GPIO_PIN_5

extern volatile uint16_t *LCD_Command;

extern volatile uint16_t *LCD_Data;

#define LCD_WriteCommand(Command) *LCD_Command = (Command)
#define LCD_WriteData(Data) *LCD_Data = (Data)
#define LCD_ReadData(void) *LCD_Data
#define LCD_WriteSetting(LCD_SETTINGREG, LCD_DATA) \
  do \
  { \
    LCD_WriteCommand(LCD_SETTINGREG); \
    LCD_WriteData(LCD_DATA); \
  } while(0)

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
#define LCD_EnablePins(LCD_GPIOx, LCD_Pins) \
  GPIO_Config(LCD_GPIOx, LCD_Pins, GPIO_MODE_ALTERNATE, \
  GPIO_OUTTYPE_PUSHPULL, GPIO_OUTSPEED_VHIGH, GPIO_PUPD_OFF, \
  GPIO_ALTFUNCTION_12); 

#define LCD_EnableGeneralPins(void) \
{ \
	RCC_EnableClock((struct RCCxo *)&GPIODo); \
	RCC_EnableClock((struct RCCxo *)&GPIOEo); \
  \
  LCD_EnablePins(&GPIODo, GPIO_PIN_5 | GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | \
    GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_14 | \
    GPIO_PIN_15);  \
  LCD_EnablePins(&GPIOEo, GPIO_PIN_3 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | \
    GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | \
    GPIO_PIN_15); \
\
  GPIO_Config(&GPIOEo, LCD_RSTPIN, GPIO_MODE_OUTPUT, GPIO_OUTTYPE_PUSHPULL,\
    GPIO_OUTSPEED_VHIGH, GPIO_PUPD_OFF, GPIO_NO_USE); \
  GPIO_SetOutput(&GPIOEo,LCD_RSTPIN); \
}

 

void LCD_EnableFMC(uint32_t FMC_BusWidth, uint32_t FMC_BusTurn,
  uint32_t FMC_DataSetup, uint32_t FMC_AddSetup);





#endif
