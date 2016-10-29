//
//
//
//
//




#include "STM32F767_LCD.h"


volatile uint16_t LCD_BUFFER[240*320] __attribute__((section("._frame_buf")));



void DMA2D_CopyPixelMapPFC(const uint8_t map[], uint16_t x, uint16_t y, uint16_t
w, uint16_t h)
{

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

  DMA2D_WaitTransfer();

  DMA2D->CR = (0b01 << 16) |DMA2D_CR_START;
  //enable register to memory mode. No need to clear bits because both are set.
}


void DMA2D_CopyPixelMap(const uint16_t map[], uint32_t x, uint32_t y, uint32_t
w, uint32_t h)
{

  DMA2D_Mem2Mem((uint32_t)&map[0], (uint32_t)&LCD_BUFFER[x + (LCD_WIDTH * y)], LCD_COLORMODE,
    (w << 16) | h, 0, LCD_WIDTH - w);
}



/*  Start LCD_UpdateScreen  */
void LCD_UpdateScreen(void)
{
  LCD_WriteCommand(0x2C);
  
  DMA2D_Mem2Mem((uint32_t)&LCD_BUFFER[0], (uint32_t)LCD_Data, LCD_COLORMODE,
    (240 << 16) | 320, 0, 0);
}
/*  End LCD_UpdateScreen  */


/* callback functions for MCUFONT decoder functions 
static void pixel(int16_t x, int16_t y, uint8_t count, uint8_t alpha,
void * state)
{
if(alpha >0x80)
LCD_DrawHLine(x++,y,count,0xffff);
}

  static uint8_t character(int16_t x, int16_t y, mf_char character,
  void *state)
  {
  
  return mf_render_character(state, x, y, character, pixel, 0);
  
  }
  
  static bool line(const char *line, uint16_t count, void *state)
  {
  
  static int y=0;
  mf_render_aligned(state,0,y++,0,line,7,character,state);
  
  
  return true;
  
  }


example function
mf_render_aligned(font,100,0,MF_ALIGN_CENTER,"HELLO MOTO
NIGGO",100,character,font    );

*/


void LCD_DrawVLine(uint32_t x, uint32_t y, uint32_t h, uint32_t color)
{
  if(LCD_XYOOR(x,y))
    return;

  if(y + h > 320)
    h = 320-y;

  DMA2D_Reg2Mem((uint32_t)&LCD_BUFFER[x + (LCD_WIDTH * y)],
    LCD_COLORMODE, color, 1 << 16 | h, LCD_WIDTH -1);
}

void LCD_DrawHLine(uint32_t x, uint32_t y, uint32_t w, uint32_t color)
{ 
  if(LCD_XYOOR(x,y))
    return;

  if(x + w > 240)
    w = 240-x;  

  DMA2D_Reg2Mem((uint32_t)&LCD_BUFFER[x + (LCD_WIDTH * y)],
    LCD_COLORMODE, color, w << 16 | 1, LCD_WIDTH -1);
}

void LCD_DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
  uint16_t color)
{

    if (x0 == x1) {
      if (y1 > y0)
        LCD_DrawVLine(x0, y0, y1-y0, color);
      else
        LCD_DrawVLine(x0, y1, y0-y1, color);
      return;
    }
    if (y0 == y1) {
      if (x1 > x0)
        LCD_DrawHLine(x0, y0, x1-x0, color);
      else
        LCD_DrawHLine(x1, y0, x0-x1, color);
      return;
    }
 
    uint8_t steep = MATH_abs(y1 - y0) > MATH_abs(x1 - x0);

    if (steep)
    {
      swap(x0,y0);
      swap(x1,y1);
    }
    if(x0 > x1)
    {
      swap(x0,x1);
      swap(y0,y1);    
    }

  int16_t dx, dy;
  dx = x1- x0;
  dy = MATH_abs(y1 - y0);

  int16_t err = dx / 2;
  int16_t ystep;

  if(y0 < y1)
  {
    ystep = 1;
  } else
  {
    ystep = -1;
  }

  while(x0 <= x1)
  {
    if(steep)
    {
      LCD_DrawPixel(y0, x0, color);
    } else
    {
      LCD_DrawPixel(x0, y0, color);
    }

    err -= dy;
    if(err < 0)
    {
      y0 += ystep;
      err += dx;
    }
  x0++;
  }
}

void LCD_DrawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h,
  uint16_t color)
{
  LCD_DrawHLine(x, y, w, color);
  LCD_DrawHLine(x, y + h, w, color);
  LCD_DrawVLine(x, y, h, color);
  LCD_DrawVLine(x + w, y, h, color);
}

void LCD_FillRect(uint32_t x, uint32_t y, uint32_t w, uint32_t h,
  uint32_t color)
{
  if(LCD_XYOOR(x,y))
    return;

  if(y + h > 320)
    h = 320-y;
  
  if(x + w > 240)
    w = 240-x;

  DMA2D_Reg2Mem((uint32_t)&LCD_BUFFER[x + (LCD_WIDTH * y)],
    LCD_COLORMODE, color, w << 16 | h, LCD_WIDTH - w);
}

void LCD_FillCircle(uint16_t x, uint16_t y, uint16_t r, uint16_t color)
{
  int16_t a, b, P;

  a = 0;
  b = r;
  P = 1 - r;
  
  do
  {
    LCD_DrawLine(x - a, y + b, x + a, y + b, color);
    LCD_DrawLine(x - a, y - b, x + a, y - b, color);
    LCD_DrawLine(x - b, y + a, x + b, y + a, color);
    LCD_DrawLine(x - b, y - a, x + b, y - a, color);
    
    if ( P < 0 )
    {
      P += 3 + 2 * a++;
    }
    else
    {
      P += 5 + 2 * (a++ - b--);
    }
  } while(a <= b);
}

void LCD_DrawCircle(int16_t x, int16_t y, int16_t r, uint16_t color)
{
  int16_t a, b, P;

  a = 0;
  b = r;
  P = 1 - r;

  do
  {
    LCD_DrawPixel(x + a, y + b, color);
    LCD_DrawPixel(x + b, y + a, color);
    LCD_DrawPixel(x - a, y + b, color);
    LCD_DrawPixel(x - b, y + a, color);
    LCD_DrawPixel(x + b, y - a, color);
    LCD_DrawPixel(x + a, y - b, color);
    LCD_DrawPixel(x - a, y - b, color);
    LCD_DrawPixel(x - b, y - a, color);
    
    if(P < 0)
    {
      P += 3 + 2 * a++;
    }
    else
    {
      P += 5 + 2 * (a++ - b--);
    }
  } while (a <= b);
}

void LCD_DrawEllipse(int16_t x, int16_t y, int16_t a, int16_t b,
  uint16_t color) 
{
  int32_t  dx = 0, dy = b; /* im I. Quadranten von links oben nach rechts unten
*/
  int32_t a2 = a*a, b2 = b*b;
  int32_t err = b2-(2*b-1)*a2, e2; /* Fehler im 1. Schritt */

  do 
  {
    LCD_DrawPixel(x+dx, y+dy, color); /* I. Quadrant */
    LCD_DrawPixel(x-dx, y+dy, color); /* II. Quadrant */
    LCD_DrawPixel(x-dx, y-dy, color); /* III. Quadrant */
    LCD_DrawPixel(x+dx, y-dy, color); /* IV. Quadrant */

    e2 = 2*err;
    if(e2 <  (2*dx+1)*b2) 
    {
      dx++;
      err += (2*dx+1)*b2;
    }
    if(e2 > -(2*dy-1)*a2)   
    {  
      dy--;
      err -= (2*dy-1)*a2;
    }
  } while(dy >= 0); 

  while(dx++ < a) 
  { /* fehlerhafter Abbruch bei flachen Ellipsen (b=1) */
    LCD_DrawPixel(x+dx, y, color); /* -> Spitze der Ellipse vollenden
*/
    LCD_DrawPixel(x-dx, y, color);
  }   
}

void LCD_FillEllipse(int16_t x, int16_t y, int16_t a, int16_t b, 
  uint16_t color) 
{
  int32_t  dx = 0, dy = b; /* im I. Quadranten von links oben nach rechts unten
*/
  int32_t a2 = a*a, b2 = b*b;
  int32_t err = b2-(2*b-1)*a2, e2; /* Fehler im 1. Schritt */

  do 
  {
    LCD_DrawLine(x-dx,y+dy,x+dx,y+dy, color);
    LCD_DrawLine(x-dx,y-dy,x+dx,y-dy, color);

    e2 = 2*err;
    if(e2 <  (2*dx+1)*b2) 
    {
      dx++;
      err += (2*dx+1)*b2;
    }
    if(e2 > -(2*dy-1)*a2) 
    {
      dy--;
      err -= (2*dy-1)*a2;
    }
  } while(dy >= 0); 

  while(dx++ < a) 
  { /* fehlerhafter Abbruch bei flachen Ellipsen (b=1) */
    LCD_DrawPixel(x+dx, y, color); /* -> Spitze der Ellipse vollenden
*/
    LCD_DrawPixel(x-dx, y, color);
  }   
}

void LCD_DrawRoundRect(int16_t x, int16_t y, int16_t w,
 int16_t h, int16_t r, uint16_t color) 
{
  // smarter version
  LCD_DrawHLine(x+r  , y    , w-2*r, color); // Top
  LCD_DrawHLine(x+r  , y+h-1, w-2*r, color); // Bottom
  LCD_DrawVLine(x    , y+r  , h-2*r, color); // Left
  LCD_DrawVLine(x+w-1, y+r  , h-2*r, color); // Right

  int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x0     = 0;
  int16_t y0     = r;

  while (x0<y0) 
  {
    if (f >= 0) 
    {
      y0--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x0++;
    ddF_x += 2;
    f     += ddF_x;

    LCD_DrawPixel(x + w - r - 1 + x0, y + h - r - 1 + y0, color);
    LCD_DrawPixel(x + w - r - 1 + y0, y + h - r - 1 + x0, color);
    LCD_DrawPixel(x + w - r - 1 + x0, y + r - y0, color);
    LCD_DrawPixel(x + w - r - 1 + y0, y + r - x0, color);
    LCD_DrawPixel(x + r - y0, y + h - r - 1 + x0, color);
    LCD_DrawPixel(x + r - x0, y + h - r - 1 + y0, color);
    LCD_DrawPixel(x + r - y0, y + r - x0, color);
    LCD_DrawPixel(x + r - x0, y + r - y0, color);
  }
}

void LCD_FillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h,
int16_t r, 
  uint16_t color) 
{
  // smarter version
  LCD_FillRect(x+r, y, w-2*r, h, color);

  // draw four corners

  int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x0     = 0;
  int16_t y0     = r;

  while (x0<y0) 
  {
    if (f >= 0) 
    {
      y0--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x0++;
    ddF_x += 2;
    f     += ddF_x;

    LCD_DrawVLine(x + w - r - 1 + x0, y + r -y0, 2 * y0 + h - 2 * r, color);
    LCD_DrawVLine(x + w - r - 1 + y0, y + r -x0, 2 * x0 + h - 2 * r, color);
    LCD_DrawVLine(x + r -x0, y + r-y0, 2* y0 + h - 2 * r, color);
    LCD_DrawVLine(x + r -y0, y + r-x0, 2* x0 + h - 2 * r, color);
  }
}

void LCD_DrawTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, 
  uint16_t x2, uint16_t y2, uint16_t color) 
{
  LCD_DrawLine(x0, y0, x1, y1, color);
  LCD_DrawLine(x1, y1, x2, y2, color);
  LCD_DrawLine(x2, y2, x0, y0, color);
}

void LCD_FillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, 
  int16_t x2, int16_t y2, uint16_t color) 
{
  int16_t a, b, y, last;

  // Sort coordinates by Y order (y2 >= y1 >= y0)
  if (y0 > y1) {
    swap(y0, y1); swap(x0, x1);
  }
  if (y1 > y2) {
    swap(y2, y1); swap(x2, x1);
  }
  if (y0 > y1) {
    swap(y0, y1); swap(x0, x1);
  }

  if(y0 == y2) { // Handle awkward all-on-same-line case as its own thing
    a = b = x0;
    if(x1 < a)      a = x1;
    else if(x1 > b) b = x1;
    if(x2 < a)      a = x2;
    else if(x2 > b) b = x2;
    LCD_DrawHLine(a, y0, b-a+1, color);
    return;
  }

  int16_t
    dx01 = x1 - x0,
    dy01 = y1 - y0,
    dx02 = x2 - x0,
    dy02 = y2 - y0,
    dx12 = x2 - x1,
    dy12 = y2 - y1;
  int32_t
    sa   = 0,
    sb   = 0;

  // For upper part of triangle, find scanline crossings for segments
  // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
  // is included here (and second loop will be skipped, avoiding a /0
  // error there), otherwise scanline y1 is skipped here and handled
  // in the second loop...which also avoids a /0 error here if y0=y1
  // (flat-topped triangle).
  if(y1 == y2) last = y1;   // Include y1 scanline
  else         last = y1-1; // Skip it

  for(y=y0; y<=last; y++) {
    a   = x0 + sa / dy01;
    b   = x0 + sb / dy02;
    sa += dx01;
    sb += dx02;
    /* longhand:
    a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
    */
    if(a > b) swap(a,b);
    LCD_DrawHLine(a, y, b-a+1, color);
  }

  // For lower part of triangle, find scanline crossings for segments
  // 0-2 and 1-2.  This loop is skipped if y1=y2.
  sa = dx12 * (y - y1);
  sb = dx02 * (y - y0);
  for(; y<=y2; y++) {
    a   = x1 + sa / dy12;
    b   = x0 + sb / dy02;
    sa += dx12;
    sb += dx02;
    /* longhand:
    a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
    */
    if(a > b) swap(a,b);
    LCD_DrawHLine(a, y, b-a+1, color);
  }
}

//Draw XBitMap Files (*.xbm), exported from GIMP,
//Usage: Export from GIMP to *.xbm, rename *.xbm to *.c and open in editor.
//C Array can be directly used with this function
void LCD_DrawXBitmap(uint16_t x, uint16_t y,
 const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color) {

  int16_t i, j, byteWidth = (w + 7) / 8;
  uint8_t byte = 0;

  for(j=0; j<h; j++) 
  {
    for(i=0; i<w; i++ ) 
    {
      if(i & 7) 
      {
        byte >>= 1;
      } else      
      {
        byte = *(bitmap + j * byteWidth + i / 8);
      }
      if(byte & 0x01) 
      {
        LCD_DrawPixel(x+i, y+j, color);
      }
    }
  }
}




/*
*******
*******
******

 START CHARACTER FUNCTIONS

*****
******
**
******
*/




/* USES BYTE WIDTH INSIDE OF BIT
uint32_t LCD_DrawChar4(uint16_t x, uint16_t y, uint16_t c, uint16_t color,
uint8_t size)
{
  if(c == ' ')
    return size << 2;

  c = c - LCD_FONTCHARMIN;

  uint32_t charbytes = LCD_FONT_WIDTHS[c][0];
  uint32_t maxwidth = 0;

  for(int32_t height = 0; height < LCD_FONTHEIGHT; height++ )
  {
    for(uint32_t i = 0; i< charbytes; i++)
    {
    int32_t width = i << 3; 

    uint8_t row = LCD_FONT[LCD_FONT_WIDTHS[c][1] + i + height*charbytes];

      while( row != 0)
      {
        if(row & 0x80)
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
        if(width > maxwidth)
          maxwidth = width;
      } 
    };
  };

return maxwidth * size;
}
*/

uint32_t LCD_DrawChar3(uint16_t x, uint16_t y, uint16_t c, uint16_t color,
uint8_t size)
{
  if(c == ' ')
    return size << 2;

  c = c - LCD_FONTCHARMIN;

  uint32_t charbytes = ((LCD_FONT_WIDTHS[c][0] - 1) >> 3) + 1;

  for(int32_t height = 0; height < LCD_FONTHEIGHT; height++ )
  {
    for(uint32_t i = 0; i< charbytes; i++)
    {
    int32_t width = i << 3; 

    uint8_t row = LCD_FONT[LCD_FONT_WIDTHS[c][1] + i + height*charbytes];

      while( row != 0)
      {
        if(row & 0x80)
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
    };
  };

return LCD_FONT_WIDTHS[c][0] * size;
}


/*
uint32_t Getlength(uint16_t c)
{
if(c == ' ')
    return  4;

  c = (c - '!');

  uint8_t charbytes = LCD_FONT_WIDTHS[c][0];
  uint32_t maxwidth = 0;

   for(int32_t height = 0; height < LCD_FONTHEIGHT; height++ )
  {
    for(int i = 0; i< charbytes; i++)
    {
    int16_t width = i << 3; 

    uint8_t row = LCD_FONT[LCD_FONT_WIDTHS[c][1] + i + height*charbytes];

      while( row != 0)
      {
        row <<= 1;
        width++;
        if(width > maxwidth)
          maxwidth = width;
      } 
    };
  };

return maxwidth;
} 

uint32_t Length(uint16_t c)
{

  if(c == ' ')
    return 4;

  c = (c - '!');

  uint8_t charbytes = LCD_FONT_WIDTHS[c][0];
  uint8_t maxwidth = 0;

  for(uint32_t height = 0; height < LCD_FONTHEIGHT; height++)
  {
    uint8_t row = LCD_FONT[LCD_FONT_WIDTHS[c][1] + charbytes - 1 + height*charbytes];
    uint16_t width = charbytes << 3;

    if(row != 0)
    {
      while((row & 0b1) == 0)
      {
        row >>= 1;
        width--;
      }
      if(width > maxwidth)
        maxwidth = width;
    }

  };

return maxwidth;

}
*/



struct MATH_POINT LCD_PrintString(uint16_t x, uint16_t y, char *string, 
   uint16_t color, uint8_t size)
{
  uint16_t xplace = 0, count = 0;

  while(string[count] != 0)
  {
      xplace += LCD_DrawChar3(x + xplace,y,string[count],color,size) + 1;
      count++;
  }
  return (struct MATH_POINT){xplace,1};
}

struct MATH_POINT LCD_PrintInt(int16_t x, int16_t y, uint32_t number, 
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
    xplace += LCD_DrawChar3(x, y, '0', color, size) + 1;
  }
  //if PIcounter is 0 at this point then the number was zero so print a zero.
  else
  {
    while(counter > 0)
    {
      counter--;
      //plus 48 because the zero character is decimal 48. We are turning int
      //into char
      xplace += LCD_DrawChar3(x + xplace, y, holder[counter] + '0', color, size)
+ 1;
    }
  }

  return (struct MATH_POINT){xplace,1};
}

uint32_t GetIntLength(uint32_t num)
{
  uint32_t count = 0;

  do
  {
    num /= 10;
    count++;
  } while(num);
  
  return count;
}

struct MATH_POINT LCD_PrintFloat(uint16_t x, uint16_t y, float number, 
  uint8_t precision, uint16_t color, uint8_t size)
{
 
  uint16_t xplace = 0;

  if(number < 0.0)
  {
    number *= -1;
    xplace += LCD_DrawChar3(x,y,'-',color,size) + 1;
  }


  xplace += LCD_PrintInt(x + xplace, y, number, color, size).x;
  
  
  uint32_t decimal = 
    (uint32_t)(number * MATH_EXP(10,precision)) % MATH_EXP(10,precision);

  
  if(precision > 0)
  {
    xplace += LCD_DrawChar3(x + xplace, y, '.', color, size);
   
    uint32_t declength = GetIntLength(decimal);
 
    //if(precision > 1 && decimal < 10.00)
    while(declength < precision)
    {
      xplace += LCD_DrawChar3(x + xplace, y, '0', color, size);
      precision--;
    }
      
    xplace += LCD_PrintInt(x + xplace, y, decimal, color, size).x; 
  }

  return (struct MATH_POINT){xplace,1};
}



struct MATH_POINT LCD_PrintfString(uint16_t x, uint16_t y, uint16_t w, 
  uint16_t h, char *string,  uint16_t color, uint8_t size)
{
  uint16_t xplace = 0, yplace = 0;
  
  while( *string != '\0' )
  {

  uint16_t count = 0, wordlength = 0;;
  do
  {
    wordlength += LCD_FONT_WIDTHS[(uint8_t)string[count]][0] * size + 1;
    count ++; 
  } while(string[count] > ' ');

  if(wordlength + xplace > w || *string == '\n')
  {
    yplace += LCD_FONTHEIGHT * size + 1;
    xplace = 0;

    if(*string <= ' ')
      string++;
  }
  if(yplace + 14*size > h || *string == '\0')
    return (struct MATH_POINT){xplace,yplace};

  do
  { 
    xplace += LCD_DrawChar3(x + xplace, y + yplace, *string, color, size) + 1;
    string++;
  } while(*string > ' ');

  }
  return (struct MATH_POINT){xplace,yplace};
}








