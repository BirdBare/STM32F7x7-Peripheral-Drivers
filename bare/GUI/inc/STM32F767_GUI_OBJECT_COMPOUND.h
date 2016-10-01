//
//
//
//
//



#ifndef STM32F767_GUI_OBJECT_COMPOUND_H
#define STM32F767_GUI_OBJECT_COMPOUND_H

#include "stm32f7xx.h"
#include "STM32F767_GUI_OBJECT.h"
#include "STM32F767_LCD.h"

/* COMPOUND OBJECT DEFINITIONS */

/* SIMPLE TEXT BOX */

#define GUI_OBJECT_FLAG_TEXTSIZE (uint32_t)0b11
#define GUI_OBJECT_FLAG_PRECISION (uint32_t)0b11100
#define GUI_OBJECT_FLAG_WRAPTEXT (uint32_t)0b100000
// 0 = Background color
// 1 = Text Color

static void GUI_PrintFunc_SimpleTextBox(struct GUI_OBJECT *object)
{
  uint16_t x = object->x0;
  uint16_t y = object->y0;
  uint16_t w = object->x1;
  uint16_t h = object->y1;
  uint8_t size = object->flags & GUI_OBJECT_FLAG_TEXTSIZE;

  if(object->flags & GUI_OBJECT_FLAG_ROUNDED)
  {
    LCD_FillRoundRect(x,y,w,h,object->x2,object->colors[0]);
  }
  else
  {
    LCD_FillRect(x,y,w,h,object->colors[0]); 
  }

  LCD_PrintfString(x,y,w,h,(char *)object->data,
    object->colors[1],size);
}
#define GUI_CreateSimpleSquareTextBox(TextBoxName, X, Y, W, H, Z, TextVariable,\
  TextSize) \
  uint16_t TextBoxName##Colors[2] = {0,0xffff}; \
  struct GUI_OBJECT TextBoxName = {.x0 = (X), .y0 = (Y), .x1 = (W), .y1 = (H), \
    .x2 = 0, .y2 = 0, .z = (Z), .colors = TextBoxName##Colors, \
    .flags = GUI_OBJECT_FLAG_RECT | TextSize | GUI_OBJECT_FLAG_RECT, \
    .data = &TextVariable[0], .PrintFunc = GUI_PrintFunc_SimpleTextBox, \
    .nextobj = 0, .prevobj = 0}

#define GUI_CreateSimpleRoundedTextBox(TextBoxName, X, Y, W, H, R, Z, \
  TextVariable, TextSize) \
  uint16_t TextBoxName##Colors[2] = {0,0xffff}; \
  struct GUI_OBJECT TextBoxName = {.x0 = (X), .y0 = (Y), .x1 = (W), .y1 = (H), \
    .x2 = (R), .y2 = 0, .z = (Z), .colors = TextBoxName##Colors, \
    .flags = GUI_OBJECT_FLAG_RECT | TextSize | GUI_OBJECT_FLAG_ROUNDED, \
    .data = &TextVariable[0], .PrintFunc = GUI_PrintFunc_SimpleTextBox, \
    .nextobj = 0, .prevobj = 0}


/* End Simple Text BOX */


static uint32_t STRING_GetStringLength(char string[])
{
  uint32_t count = 0;
  
  while(string[count] != '\0')
  {
    count++;
  }
  return count;
}

/* GUI push button with text or data */

static void GUI_PrintFunc_PushButton(struct GUI_OBJECT *object)
{
  uint16_t x = object->x0;
  uint16_t y = object->y0;
  uint8_t size = object->flags & GUI_OBJECT_FLAG_TEXTSIZE;
  char *string = (char *)object->data;
  
  
  if(object->flags & GUI_OBJECT_FLAG_CIRCLE)
  {
    LCD_FillCircle(x,y, object->x1,0xff);

    uint32_t stringlength = STRING_GetStringLength(string);

    LCD_PrintString(x - ((stringlength * size) * 3),y-(size <<
2),string,(uint32_t)object->colors,size);
    //size * 8 / 2 == size << 2
  }
}

/*static uint32_t GetIntLength(uint32_t num)
{
  uint32_t count = 0;

  do
  {
    num /= 10;
    count++;
  } while(num);
  return count;
}*/

static uint32_t GetFloatLength(float num, uint8_t precision)
{
 uint32_t numlength = precision + 1;
 
  if(num < 0.0)
  {
    numlength++;
    num *= -1;
  }
  
  numlength += GetIntLength((uint32_t)num);

  /*uint32_t precisionmult = MATH_EXP(10,precision);

  precisionmult = (uint32_t)(num * precisionmult) % precisionmult;
 
  if(precisionmult)
  {
    numlength += GetIntLength(precisionmult) + 1;
  }*/
  
  return numlength;
}

static uint32_t GetWordLength(char string[])
{
  uint32_t count = 0;

  do
  {
    count ++;
  } while(string[count] > ' ');

  return count;


}

#define GUI_CreatePrintArea(AreaName,X,Y,W,H,Z,TextSize) \
  uint16_t AreaName##Colors[2] = {0x0,0xffff}; \
  struct GUI_OBJECT AreaName = {.x0 = (X), .y0 = (Y), .x1 = (W), .y1 = (H), \
    .x2 = (X), .y2 = (Y), .z = (Z), .colors = AreaName##Colors, \
    .flags = GUI_OBJECT_FLAG_RECT | TextSize | (2 << 2), \
    .data = 0, .PrintFunc = GUI_PrintFunc_PrintArea, \
    .nextobj = 0, .prevobj = 0}

#define GUI_MESSAGE_PRINTNUM 0b1000000
#define GUI_MESSAGE_PRINTSTRING 0b0000000

#define GUI_PrintAreaSetMessage(Area,Message) \
  (Area).flags = Message | ((Area).flags & 0b11100000000000000000000000111111)
#define GUI_PrintArea

static void GUI_PrintAreaPrintNum(struct GUI_OBJECT *PrintArea, float num)
{
  GUI_PrintAreaSetMessage(*PrintArea, GUI_MESSAGE_PRINTNUM);
  PrintArea->data = &num;
  GUI_PrintObject(*PrintArea);
}

static void GUI_PrintAreaPrintString(struct GUI_OBJECT *PrintArea, char *string)
{
  GUI_PrintAreaSetMessage(*PrintArea, GUI_MESSAGE_PRINTSTRING);
  PrintArea->data = string;
  GUI_PrintObject(*PrintArea);
}

static void GUI_PrintAreaClear(struct GUI_OBJECT *PrintArea)
{
  LCD_FillRect(PrintArea->x0, PrintArea->y0, PrintArea->x1, PrintArea->y1,
    PrintArea->colors[0]);
  PrintArea->x2 = PrintArea->x0; 
  PrintArea->y2 = PrintArea->y0; 
}

static void GUI_PrintFunc_PrintArea(struct GUI_OBJECT *object)
{
  uint16_t x = object->x0;
  uint16_t y = object->y0;
  uint16_t w = object->x1;
  uint16_t h = object->y1;

  if((object->flags & GUI_MESSAGE_PRINTNUM) == GUI_MESSAGE_PRINTNUM)
  {
    float data = *(float *)(object->data);
    uint8_t textsize = object->flags & GUI_OBJECT_FLAG_TEXTSIZE;    
    uint8_t precision = (object->flags & GUI_OBJECT_FLAG_PRECISION) >> 2;
    uint32_t intlength = GetFloatLength(data,precision) * textsize * 6;

    if((intlength) + object->x2 > 
      x + w)
    {
      object->y2 += 8 * textsize;
      object->x2 = x; 
    } 
    if(object->y2 + 8*textsize > y + h)
      return;

    LCD_PrintFloat(object->x2, object->y2, data, precision, object->colors[1], 
      textsize);
    object->x2 += intlength;
  }
  else
  {
    uint32_t count = 0;
    char *string = (char *)object->data + count;    
    uint8_t textsize = object->flags & GUI_OBJECT_FLAG_TEXTSIZE;    

    while( (*string) != '\0')
    {
      uint16_t wordlength = 0, count = 0;
      do
      {
wordlength += LCD_FONT_WIDTHS[(uint8_t)string[count]][0] * textsize + 1;
        count++;
      } while(string[count] > ' ');

      if(wordlength + object->x2 > x + w || *string == '\n')
      {
        object->y2 += textsize * LCD_FONTHEIGHT;
        object->x2 = x;

        if(*string <= ' ')
          string++; 
      }
      
      if(object->y2 + 8*textsize > y + h || *string == '\0')
        return;

      do
      {
          object->x2 += LCD_DrawChar3(object->x2, object->y2, *string, object->colors[1],
            textsize) + 1;
          string++;
      } while(*string > ' ');

    }
  }
}















#endif
