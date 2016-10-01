//
//
//
//
//



#ifndef STM32F767_DMA2D_H
#define STM32F767_DMA2D_H

#include "stm32f7xx.h"
#include "STM32F767_FMC_LCD.h"


static const uint32_t DMA2D_CLUT [256] =
{
4278190080, //  00000000 
4278190162, //  00000001 
4278190253, //  00000010 
4278190335, //  00000011 
4278199296, //  00000100 
4278199378, //  00000101 
4278199469, //  00000110 
4278199551, //  00000111 
4278208768, //  00001000 
4278208850, //  00001001 
4278208941, //  00001010 
4278209023, //  00001011 
4278217984, //  00001100 
4278218066, //  00001101 
4278218157, //  00001110 
4278218239, //  00001111 
4278227456, //  00010000 
4278227538, //  00010001 
4278227629, //  00010010 
4278227711, //  00010011 
4278236672, //  00010100 
4278236754, //  00010101 
4278236845, //  00010110 
4278236927, //  00010111 
4278246144, //  00011000 
4278246226, //  00011001 
4278246317, //  00011010 
4278246399, //  00011011 
4278255360, //  00011100 
4278255442, //  00011101 
4278255533, //  00011110 
4278255615, //  00011111 
4280352768, //  00100000 
4280352850, //  00100001 
4280352941, //  00100010 
4280353023, //  00100011 
4280361984, //  00100100 
4280362066, //  00100101 
4280362157, //  00100110 
4280362239, //  00100111 
4280371456, //  00101000 
4280371538, //  00101001 
4280371629, //  00101010 
4280371711, //  00101011 
4280380672, //  00101100 
4280380754, //  00101101 
4280380845, //  00101110 
4280380927, //  00101111 
4280390144, //  00110000 
4280390226, //  00110001 
4280390317, //  00110010 
4280390399, //  00110011 
4280399360, //  00110100 
4280399442, //  00110101 
4280399533, //  00110110 
4280399615, //  00110111 
4280408832, //  00111000 
4280408914, //  00111001 
4280409005, //  00111010 
4280409087, //  00111011 
4280418048, //  00111100 
4280418130, //  00111101 
4280418221, //  00111110 
4280418303, //  00111111 
4283039744, //  01000000 
4283039826, //  01000001 
4283039917, //  01000010 
4283039999, //  01000011 
4283048960, //  01000100 
4283049042, //  01000101 
4283049133, //  01000110 
4283049215, //  01000111 
4283058432, //  01001000 
4283058514, //  01001001 
4283058605, //  01001010 
4283058687, //  01001011 
4283067648, //  01001100 
4283067730, //  01001101 
4283067821, //  01001110 
4283067903, //  01001111 
4283077120, //  01010000 
4283077202, //  01010001 
4283077293, //  01010010 
4283077375, //  01010011 
4283086336, //  01010100 
4283086418, //  01010101 
4283086509, //  01010110 
4283086591, //  01010111 
4283095808, //  01011000 
4283095890, //  01011001 
4283095981, //  01011010 
4283096063, //  01011011 
4283105024, //  01011100 
4283105106, //  01011101 
4283105197, //  01011110 
4283105279, //  01011111 
4285202432, //  01100000 
4285202514, //  01100001 
4285202605, //  01100010 
4285202687, //  01100011 
4285211648, //  01100100 
4285211730, //  01100101 
4285211821, //  01100110 
4285211903, //  01100111 
4285221120, //  01101000 
4285221202, //  01101001 
4285221293, //  01101010 
4285221375, //  01101011 
4285230336, //  01101100 
4285230418, //  01101101 
4285230509, //  01101110 
4285230591, //  01101111 
4285239808, //  01110000 
4285239890, //  01110001 
4285239981, //  01110010 
4285240063, //  01110011 
4285249024, //  01110100 
4285249106, //  01110101 
4285249197, //  01110110 
4285249279, //  01110111 
4285258496, //  01111000 
4285258578, //  01111001 
4285258669, //  01111010 
4285258751, //  01111011 
4285267712, //  01111100 
4285267794, //  01111101 
4285267885, //  01111110 
4285267967, //  01111111 
4287889408, //  10000000 
4287889490, //  10000001 
4287889581, //  10000010 
4287889663, //  10000011 
4287898624, //  10000100 
4287898706, //  10000101 
4287898797, //  10000110 
4287898879, //  10000111 
4287908096, //  10001000 
4287908178, //  10001001 
4287908269, //  10001010 
4287908351, //  10001011 
4287917312, //  10001100 
4287917394, //  10001101 
4287917485, //  10001110 
4287917567, //  10001111 
4287926784, //  10010000 
4287926866, //  10010001 
4287926957, //  10010010 
4287927039, //  10010011 
4287936000, //  10010100 
4287936082, //  10010101 
4287936173, //  10010110 
4287936255, //  10010111 
4287945472, //  10011000 
4287945554, //  10011001 
4287945645, //  10011010 
4287945727, //  10011011 
4287954688, //  10011100 
4287954770, //  10011101 
4287954861, //  10011110 
4287954943, //  10011111 
4290052096, //  10100000 
4290052178, //  10100001 
4290052269, //  10100010 
4290052351, //  10100011 
4290061312, //  10100100 
4290061394, //  10100101 
4290061485, //  10100110 
4290061567, //  10100111 
4290070784, //  10101000 
4290070866, //  10101001 
4290070957, //  10101010 
4290071039, //  10101011 
4290080000, //  10101100 
4290080082, //  10101101 
4290080173, //  10101110 
4290080255, //  10101111 
4290089472, //  10110000 
4290089554, //  10110001 
4290089645, //  10110010 
4290089727, //  10110011 
4290098688, //  10110100 
4290098770, //  10110101 
4290098861, //  10110110 
4290098943, //  10110111 
4290108160, //  10111000 
4290108242, //  10111001 
4290108333, //  10111010 
4290108415, //  10111011 
4290117376, //  10111100 
4290117458, //  10111101 
4290117549, //  10111110 
4290117631, //  10111111 
4292739072, //  11000000 
4292739154, //  11000001 
4292739245, //  11000010 
4292739327, //  11000011 
4292748288, //  11000100 
4292748370, //  11000101 
4292748461, //  11000110 
4292748543, //  11000111 
4292757760, //  11001000 
4292757842, //  11001001 
4292757933, //  11001010 
4292758015, //  11001011 
4292766976, //  11001100 
4292767058, //  11001101 
4292767149, //  11001110 
4292767231, //  11001111 
4292776448, //  11010000 
4292776530, //  11010001 
4292776621, //  11010010 
4292776703, //  11010011 
4292785664, //  11010100 
4292785746, //  11010101 
4292785837, //  11010110 
4292785919, //  11010111 
4292795136, //  11011000 
4292795218, //  11011001 
4292795309, //  11011010 
4292795391, //  11011011 
4292804352, //  11011100 
4292804434, //  11011101 
4292804525, //  11011110 
4292804607, //  11011111 
4294901760, //  11100000 
4294901842, //  11100001 
4294901933, //  11100010 
4294902015, //  11100011 
4294910976, //  11100100 
4294911058, //  11100101 
4294911149, //  11100110 
4294911231, //  11100111 
4294920448, //  11101000 
4294920530, //  11101001 
4294920621, //  11101010 
4294920703, //  11101011 
4294929664, //  11101100 
4294929746, //  11101101 
4294929837, //  11101110 
4294929919, //  11101111 
4294939136, //  11110000 
4294939218, //  11110001 
4294939309, //  11110010 
4294939391, //  11110011 
4294948352, //  11110100 
4294948434, //  11110101 
4294948525, //  11110110 
4294948607, //  11110111 
4294957824, //  11111000 
4294957906, //  11111001 
4294957997, //  11111010 
4294958079, //  11111011 
4294967040, //  11111100 
4294967122, //  11111101 
4294967213, //  11111110 
4294967295, //  11111111 
};











#define LCD_COLORMODE DMA2D_COLORMODE_RGB565
volatile uint16_t LCD_BUFFER[240*320] __attribute__ ((section ("._frame_buf")));
//Frame Buffer for the LCD

#define DMA2D_EnableClock(void) RCC->AHB1ENR |= RCC_AHB1ENR_DMA2DEN
#define DMA2D_DisableClock(void) RCC->AHB1ENR &= ~RCC_AHB1ENR_DMA2DEN

#define DMA2D_COLORMODE_RGB565 0b010

struct DMA2D_TransferStruct
{
  uint16_t x, y; //start location
  uint16_t w, h; //end location
  
  uint32_t OutputAddress, InputAddress[2]; //output address and two inputs
  uint32_t Flags; //flags for PFC, Blender, output format, input format

} DMA2D_TranferData;

#define LCD_XYOOR(x, y) ((x) > 239 || (y) > 319)

#define DMA2D_Start(void) DMA2D->CR |= DMA2D_CR_START

 static void DMA2D_DrawVLine(uint16_t x, uint16_t y, uint16_t h, uint16_t color)
{
  if(LCD_XYOOR(x,y))
    return;


  if(y + h > 320)
    h = 320-y;
  
  while((DMA2D->CR & DMA2D_CR_START) != 0)
    asm("");

  DMA2D->OPFCCR = LCD_COLORMODE;
  //color format DMA2D_OPFCCR

  DMA2D->OCOLR = color; 
  //color OCOLR

  DMA2D->OMAR = (uint32_t)&LCD_BUFFER[x + (LCD_WIDTH * y)];
  //Set starting memory address location

  DMA2D->OOR = LCD_WIDTH - 1;
  //OUTPUT OFFSET OOR

  DMA2D->NLR = ((uint32_t)1 << 16) | h;
  //NUM LINES AND PIXELS NLR

  DMA2D->CR |= DMA2D_CR_MODE | DMA2D_CR_START;
  //enable register to memory mode. No need to clear bits because both are set.
} 

static void DMA2D_DrawHLine(uint16_t x, uint16_t y, uint16_t w, uint16_t color)
{ 
  if(LCD_XYOOR(x,y))
    return;

  if(x + w > 240)
    w = 240-x;  

  while((DMA2D->CR & DMA2D_CR_START) != 0)
    asm("");

  DMA2D->OPFCCR = LCD_COLORMODE;
  //color format DMA2D_OPFCCR

  DMA2D->OCOLR = color; 
  //color OCOLR

  DMA2D->OMAR = (uint32_t)&LCD_BUFFER[x + (LCD_WIDTH * y)];
  //Set starting memory address location

  //DMA2D->OOR = LCD_WIDTH - 1;
  // not needed since horizontal line is one line

  DMA2D->NLR = ((uint32_t)w << 16) | 1;
  //NUM LINES AND PIXELS NLR

  DMA2D->CR |= DMA2D_CR_MODE | DMA2D_CR_START;
  //enable register to memory mode. No need to clear bits because both are set.
}

static void DMA2D_FillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h,
  uint16_t color)
{
  if(LCD_XYOOR(x,y))
    return;

  if(y + h > 320)
    h = 320-y;
  if(x + w > 240)
    w = 240-x;

  while((DMA2D->CR & DMA2D_CR_START) != 0)
    asm("");

  DMA2D->OPFCCR = LCD_COLORMODE;
  //color format DMA2D_OPFCCR

  DMA2D->OCOLR = color; 
  //color OCOLR

  DMA2D->OMAR = (uint32_t)&LCD_BUFFER[x + (LCD_WIDTH * y)];
  //Set starting memory address location

  DMA2D->OOR = LCD_WIDTH - w;
  //offset OOR

  DMA2D->NLR = ((uint32_t)w << 16) | h;
  //NUM LINES AND PIXELS NLR

  DMA2D->CR |= DMA2D_CR_MODE | DMA2D_CR_START;
  //enable register to memory mode. No need to clear bits because both are set.
}

static void DMA2D_CopyPixelMap(const uint16_t map[], uint16_t x, uint16_t y, uint16_t
w, uint16_t h)
{
  while((DMA2D->CR & DMA2D_CR_START) != 0)
    asm("");

  DMA2D->FGPFCCR = LCD_COLORMODE;
  //color format DMA2D_OPFCCR

  DMA2D->FGMAR = (uint32_t)&map[0];
  DMA2D->OMAR = (uint32_t)&LCD_BUFFER[x + (LCD_WIDTH * y)];
  //Set starting memory address location

  DMA2D->FGOR = 0; // 0 because map should be continuous array.
  DMA2D->OOR = LCD_WIDTH - w;
  //offset OOR

  DMA2D->NLR = ((uint32_t)w << 16) | h;
  //NUM LINES AND PIXELS NLR

  DMA2D->CR = DMA2D_CR_START;
  //enable register to memory mode. No need to clear bits because both are set.
}

static void DMA2D_WaitTransfer(void)
{
  while((DMA2D->CR & DMA2D_CR_START) != 0)
    asm("");
}

#define RGB565 0b010
#define RGB332 0b101

static void DMA2D_LoadCLUT(void)
{
  DMA2D->FGCMAR = (uint32_t)&DMA2D_CLUT[0];
  DMA2D->BGCMAR = (uint32_t)&DMA2D_CLUT[0];

  DMA2D->FGPFCCR = 255 << 8;
  DMA2D->BGPFCCR = 255 << 8;

  DMA2D->FGPFCCR |= DMA2D_FGPFCCR_START;
  while((DMA2D->FGPFCCR & DMA2D_FGPFCCR_START) != 0)
    asm("");

  DMA2D->BGPFCCR |= DMA2D_BGPFCCR_START;
  while((DMA2D->BGPFCCR & DMA2D_BGPFCCR_START) != 0)
    asm("");

  while(DMA2D->ISR & DMA2D_ISR_CAEIF)
    asm("");
}

static void DMA2D_CopyPixelMapPFC(const uint8_t map[], uint16_t x, uint16_t y, uint16_t
w, uint16_t h)
{
  while((DMA2D->CR & DMA2D_CR_START) != 0)
    asm("");

  DMA2D->FGPFCCR = 0b0101;
  DMA2D->OPFCCR = 0b010;
  //color format DMA2D_OPFCCR

  DMA2D->FGMAR = (uint32_t)&map[0];
  DMA2D->OMAR = (uint32_t)&LCD_BUFFER[x + (LCD_WIDTH * y)];
  //Set starting memory address location

  DMA2D->FGOR = 0; // 0 because map should be continuous array.
  DMA2D->OOR = LCD_WIDTH - w;
  //offset OOR

  DMA2D->NLR = ((uint32_t)w << 16) | h;
  //NUM LINES AND PIXELS NLR

  DMA2D->CR = (0b01 << 16) |DMA2D_CR_START;
  //enable register to memory mode. No need to clear bits because both are set.
}



#endif
