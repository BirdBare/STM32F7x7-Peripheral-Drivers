//
//
//
//
//


uint8_t LCD_FONTWIDTH = 5;
uint8_t **LCD_FONT = (uint8_t **)font;
#define LCD_ChangeFont(FontArray,FontWidth) \
  LCD_FONT = (uint8_t **)FontArray; \
  LCD_FONTWIDTH = FontWidth

static void LCD_DrawChar(uint16_t x, uint16_t y, uint8_t c, uint16_t color,
uint8_t size)
{
  uint8_t line;
  
  for(int8_t i=0; i<5; i++ ) 
  {
    line = font[c - LCD_CHARTABLEMIN][i];

    for(int8_t j=0; j<8; j++, line >>= 1) 
    {
      if(line & 0x1) 
      {  
        if(size == 1)
        { 
          LCD_DrawPixel(x+i, y+j, color);
        }
        else   
          LCD_FillRect(x+(i*size), y+(j*size), size, size, color);
      } 
    }
  }
}

static struct MATH_POINT LCD_PrintInt(int16_t x, int16_t y, uint32_t number, 
  uint16_t color, uint8_t size);
#include "/Users/bradleybare/Desktop/"SOMEFONT""
#define LCD_FONTHEIGHT 20
uint16_t *LCD_FONT2 = (uint16_t *)font2;

static uint32_t LCD_DrawChar2(uint16_t x, uint16_t y, uint16_t c, uint16_t color,
uint8_t size)
{
  if(c == ' ')
    return size << 2;

  uint32_t maxwidth = 0;

  c = (c - '!') * LCD_FONTHEIGHT;
  //sets c to the correct index value

  for(int32_t height = 0; height < LCD_FONTHEIGHT; )
  {
    uint16_t row, width = 0;
    do
    {
      row = LCD_FONT2[c];
      c++;
      height++;
    } while(row == 0 && height < LCD_FONTHEIGHT);

    while(row != 0)
    {
      if(row & 0x8000)
      {
        if(size == 1)
        { 
          LCD_DrawPixel(x+width, y+height, color);
        }
        else   
          LCD_FillRect(x+(width*size), y+(height*size), size, size, color);
      }
      row <<= 1;
      width++;
    }
    
    if(width > maxwidth)
    {
      maxwidth = width;
    }
  };

return maxwidth * size;
}

static uint32_t GetCharLength(uint16_t c)
{
  if(c == ' ')
    return  4;
 
  uint32_t maxwidth = 0;

  c = (c - '!') * LCD_FONTHEIGHT;
   
  for(int height = 15; height != 0;)
  {
    uint16_t row, width = 0;
    do
    {
      row = LCD_FONT2[c];
      c++;
      height--;
    } while(row == 0 && height != 0);

    while(row != 0)
    {
       row <<= 1;
      width++;
    }
    
    if(width > maxwidth)
    {
      maxwidth = width;
    }
  }
  return maxwidth;
}

static struct MATH_POINT LCD_PrintString(uint16_t x, uint16_t y, char *string, 
   uint16_t color, uint8_t size)
{
  uint16_t xplace = 0, count = 0;

  while(string[count] != 0)
  {
      LCD_DrawChar(x + xplace,y,string[count],color,size);
      xplace += 5 * size;
      if(string[count] != ' ')
      {
        xplace += size;
      }
      count++;
  }
  return (struct MATH_POINT){xplace,1};
}

static struct MATH_POINT LCD_PrintInt(int16_t x, int16_t y, uint32_t number, 
  uint16_t color, uint8_t size)
{
  uint8_t counter = 0, holder[10];
  uint16_t xplace = 0;
  
  while(number > 0)
  {
    holder[counter] = number % 10;
    number /= 10;
    counter++;
  }
  
  if(counter == 0)
  {
    LCD_DrawChar(x, y, '0', color, size);
    xplace += 6 * size;
  }
  //if PIcounter is 0 at this point then the number was zero so print a zero.
  else
  {
    while(counter > 0)
    {
      counter--;
      LCD_DrawChar(x + xplace, y, holder[counter] + '0', color, size);
      //plus 48 because the zero character is decimal 48. We are turning int
      //into char
      xplace += 6 * size;
    }
  }

  return (struct MATH_POINT){xplace,1};
}


static struct MATH_POINT LCD_PrintFloat(uint16_t x, uint16_t y, float number, 
  uint8_t precision, uint16_t color, uint8_t size)
{
 
  uint16_t xplace = 0;

  if(number < 0.0)
  {
    number *= -1;
    LCD_DrawChar(x,y,'-',color,size);
    xplace += 6*size;
  }


  xplace += LCD_PrintInt(x + xplace, y, number, color, size).x;
  
  
  uint32_t decimal = 
    (uint32_t)(number * MATH_EXP(10,precision)) % MATH_EXP(10,precision);

  
  if(precision > 0)
  {
    LCD_DrawChar(x + xplace, y, '.', color, size);
    xplace += 6 * size;
   
    uint32_t declength = GetIntLength(decimal);
 
    //if(precision > 1 && decimal < 10.00)
    while(declength < precision)
    {
      LCD_DrawChar(x + xplace, y, '0', color, size);
      xplace += 6 * size;
      precision--;
    }
      
    xplace += LCD_PrintInt(x + xplace, y, decimal, color, size).x; 
  }

  return (struct MATH_POINT){xplace,1};
}



static struct MATH_POINT LCD_PrintfString(uint16_t x, uint16_t y, uint16_t w, 
  uint16_t h, char *string,  uint16_t color, uint8_t size)
{
  uint16_t xplace = 0, yplace = 0, count = 0, numchars = 0;

  while(string[count] != '\0' && yplace < (h * (size << 3)))
  {
    while(string[count + numchars] >= ' ' && numchars < w)
    {
      numchars++;
    }
    //get line

    while(string[count + numchars] > ' ')
    {
      numchars--;
    }
    //if the line ends in the middle of the word. Go back to end of last word

    while(numchars > 0)
    {
      LCD_DrawChar(x + xplace,y + yplace,string[count],color,size);
      count++;
      numchars--;
      xplace += 5 * size; //size of char is 5 + one space. size of space is
                          //only 5 so we add 1 later if not space.
      if(string[count] != ' ')
      {
        xplace += size; //get rid of extra
      }
    }
    
    if(string[count] > '\0')
    {
      xplace = 0;
      yplace += size << 3;
      count++;
    }
  }
  return (struct MATH_POINT){xplace,yplace};
}

