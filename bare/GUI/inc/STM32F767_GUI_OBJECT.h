//
//
//
//
//



#ifndef STM32F767_GUI_OBJECT_H
#define STM32F767_GUI_OBJECT_H

#include "stm32f7xx.h"


#define GUI_OBJECT_FLAG_RECT (uint32_t)0x00000000
#define GUI_OBJECT_FLAG_ROUNDED (uint32_t)0x40000000
#define GUI_OBJECT_FLAG_CIRCLE (uint32_t)0x80000000
#define GUI_OBJECT_FLAG_TRIANGLE (uint32_t)0xC0000000

struct GUI_OBJECT
{
  uint16_t *colors;
  int16_t z;
  uint32_t flags;
  //Common variables come first

  uint16_t x0, y0; //always x, y starting coordinates
  uint16_t x1, y1; //x1 is width, radius. y1 is height. 
                   //OR x1, y1 are vertice 2 of triangle.
  uint16_t x2, y2; // vertice 3 of triangle
  //coordinate variables next

  void *data;
  void (*PrintFunc)(struct GUI_OBJECT *);
  struct GUI_OBJECT *nextobj;
  struct GUI_OBJECT *prevobj;
  //Pointers

};
/* GUI OBJECT member description
  "data" is the data that changes or a string inside an object. It is used by 
  PrintFloat, PrintInt, and PrintfString to update the screen with a variable.

  "PrintFunc" is the function that prints the entire object. The object
  can be compound. By compound I mean multiple objects or shapes. The 
  PrintFunc is written by the object or shape creator and can include many
  simple functions to form objects such as buttons, gradient areas, fading, etc.

  "z" is the z coordinate on the 3d axis of the gui. This is used to define draw
  order in the parent container to create object layers.

  "colors: are a single color or an array of colors. The number of colors is
  defined by the person writing the PrintFunc. And is also handled by that 
  person in PrintFunc. Assigning colors to an object is also handled by the
  person writing PrintFunc.
*/


#define GUI_PrintObject(Object) (Object).PrintFunc(&Object);

#define GUI_CreateRect(RectName, x, y, w, h, Z, Data, Func) \
  struct GUI_OBJECT RectName = {.x0 = (x), .y0 = (y), .x1 = (w), .y1 = (h), \
    .x2 = 0, .y2 = 0, .z = (Z), .colors = 0, .flags = GUI_OBJECT_FLAG_RECT, \
    .data = Data, .PrintFunc = Func, .nextobj = 0, .prevobj = 0}
/*
  This can be compound. If compound, you can write your own PrintFunc or 
  use the compound draw functions. It can contain one object. If you want to 
  use more you need to use GUI_DATA struct and account for the extras in your 
  PrintFunc. If you dont need to show data, then set as 0
*/

#define GUI_CreateCircle(CircleName, x, y, r, Z, Data, Func) \
  struct GUI_OBJECT CircleName = {.x0 = (x), .y0 = (y), .x1 = (r), .y1 = 0, \
    .x2 = 0, .y2 = 0, .z = (Z), .colors = 0, .flags = GUI_OBJECT_FLAG_CIRCLE, \
    .data = Data, .PrintFunc = Func, .nextobj = 0, .prevobj = 0}
/*Same as Rect*/

#define GUI_CreateTriangle(TriangleName, X0, Y0, X1, Y1, X2, Y2, Z, Data, \
  Func) \
    struct GUI_OBJECT TriangleName = {.x0 = (X0), .y0 = (Y0), .x1 = (X1), \
      .y1 = (Y1), .x2 = (X2), .y2 = (Y2), .z = (Z), .colors = 0, .data = Data, \
      .PrintFunc = Func, .nextobj = 0, .prevobj = 0}
/*Same as Rect*/

#define GUI_SetSimpleColor(Object, Color) (Object).colors = (uint16_t *)Color

/*
TO DO!!!!

Create Variable Argument PrintF with a float array. The float array can then
hold any value we need. Example is number, or string. I think that is all we
need.

To put a string into the float array we need to split it into 4 bytes with a
function or macro. This is because the float is gaurenteed to be 4 bytes.

*/





















#endif
