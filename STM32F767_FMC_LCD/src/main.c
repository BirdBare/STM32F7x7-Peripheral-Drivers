//
//
//
//
//

#include "stm32f7xx.h"
#include "STM32F767_KERNEL.h"
#include "STM32F767_SYSTICK.h"
#include "STM32F767_BALLOC.h"
#include "STM32F767_BUFFER.h"
#include "STM32F767_PERIPH.h" 
// Utilities

#include "STM32F767_GPIO.h"
//Core

#define FONT_ROCKWELL_18PT
#include "STM32F767_LCD.h"
#include "Mush2.h"
//LCD

#include "STM32F767_GUI_OBJECT.h"
#include "STM32F767_GUI_CONTAINER.h"
#include "STM32F767_GUI_OBJECT_COMPOUND.h"
//GUI

#include "STM32F767_XPT2046.h"
#include "STM32F767_HTU21D.h"
//External Devices



struct NEW_THREAD *A;
struct NEW_THREAD *B;
struct NEW_THREAD *C;

void Task1(void* args)
{
    uint32_t i = 0;
while(1)
{
    LCD_PrintInt(60,140,(uint32_t)(((uint32_t) i)),0xffff,1);
    SYSTICK();
    i++;
}
}
void Task2(void* args)
{
  uint32_t ref = MilliSec();

  while(MilliSec() - ref < 5000)
  asm("");



}
void Task3(void* args)
{
LCD_PrintInt(100,240,GetAxis(XPT2046_AXIS_X,1) ,0xffff,1);
}

void t(void* args)
{

}

int main(void)
{

SCB_EnableICache();


  for(uint32_t i = 0; i<240*320; i++)
    LCD_BUFFER[i] = i;

  SysTick_EnableTimer();
  
  HTU21D_EnableGeneral(200000);
  //HTU21D_Reset();

  DMA2D_EnableClock();
  DelayMilli(1);
  DMA2D_LoadCLUT();
  
  LCD_EnableDMA();
  LCD_EnableGeneralPins();
  LCD_EnableFMC(FMC_BusWidth_16,0,13,8); 
  LCD_InitLCD();
  LCD_SetWindow(0,0,239,319);
  
  XPT2046_EnableGeneral();
  XPT2046_Begin();

  InitHeap();

LCD_UpdateScreen();

DelayMilli(1000);
  //Init Code
uint16_t color = 0;


/*
uint8_t text[] = "Yolo MOTO HOW ARE you?";

GUI_CreateRect(Rect,25,25,50,50,3,0,&GUI_PrintFunc_Rect);
GUI_SetSimpleColor(Rect,0xffff);

GUI_CreateRect(Rect1,0,0,50,50,2,0,&GUI_PrintFunc_Rect);
GUI_SetSimpleColor(Rect1,0xff);

GUI_CreateSimpleRoundedTextBox(textbox,0,50,100,50,10,6,text,1);
textboxColors[0] = 0xfff;
textboxColors[1] = 0x0;

GUI_CreateContainer(Container,0,0,100,100,1,0xf0c9);
GUI_AddObject(&Container,&Rect);
GUI_AddObject(&Container,&Rect1);
GUI_AddObject(&Container,&textbox);

GUI_CreateContainer(Container1,25,50,100,100,2,0xff69);

GUI_CreatePage(page);

GUI_AddContainer(&page, &Container);
GUI_AddContainer(&page, &Container1);

GUI_SetContainerZ(&page,&Container,3);

GUI_AddClickableObject(&page,&Rect);
GUI_AddClickableObject(&page,&Rect1);

GUI_CreateCircle(circ,100,100,20,1,"Push",&GUI_PrintFunc_PushButton);
circ.flags |= 1;
circ.colors = (uint16_t *)0xffff;


GUI_CreatePrintArea(PA,85,0,100,120,1,1);
PA.colors[0] = 0xfc90;
PA.colors[1] = 0b0001111111100011;
*/

B = CreateT(500,0b111,Task1,(uint32_t *)color);
B = CreateT(500,0b111,Task2,(uint32_t *)color);

loop:
 
  LCD_FillRect(0,0,240,320,color);
  DMA2D_WaitTransfer();

B = CreateT(500,0b1,Task3,(uint32_t *)color);

SYSTICK();
SCHEDULER.flags=SCHEDULER_HOLD;






//LCD_PrintInt(100,260,HTU21D_GetTemp() ,0xffff,1);






//GUI_PrintPage(&page);
//DMA2D_CopyPixelMap(MUSH,0,0,240,320);


uint8_t little[4];
*(((uint32_t *)little)) = 256;

LCD_PrintInt(40,50,(uint32_t)(B->flags),0xffff,1);

LCD_PrintInt(40,200,(uint8_t)(little[0]),0xffff,1);
LCD_PrintInt(40,225,(uint8_t)(little[1]),0xffff,1);
LCD_PrintInt(40,250,(uint8_t)(little[2]),0xffff,1);
LCD_PrintInt(40,275,(uint8_t)(little[3]),0xffff,1);



LCD_UpdateScreen();
DMA_WaitTransfer(DMA2_Stream0);
while(color == 0xff)
color = 0;
color++;

DelayMilli(5);

// Microcontroller Repeat Code

goto loop;


  return 1;
}


