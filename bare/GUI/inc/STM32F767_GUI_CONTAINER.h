//
//
//
//
//



#ifndef STM32F767_GUI_CONTAINER_H
#define STM32F767_GUI_CONTAINER_H

#include "stm32f7xx.h"
 #include "STM32F767_GUI_OBJECT.h"
 #include "STM32F767_LCD.h"

//must have atleast one object
struct GUI_CONTAINER
{
    uint16_t color; //0x0 for transparent
    int16_t z;
    uint32_t flags;
    //common variables first

    uint16_t x;
    uint16_t y;
 
    uint16_t w;
    uint16_t h;
    //coordinate variables next

    struct GUI_OBJECT *lowestobj;
    struct GUI_CONTAINER *nextcon;
    //Pointers 
};

static void GUI_PrintFunc_Rect(struct GUI_OBJECT *object)
{
  LCD_FillRect(object->x0, object->y0, object->x1, object->y1, 
    (uint32_t)object->colors);
}

#define GUI_CreateContainer(ContainerName, X, Y, W, H, Z, BackgroundColor) \
  struct GUI_CONTAINER ContainerName = {.x = (X), .y = (Y), .w = (W), \
    .h = (H), .z = (Z), .color = (BackgroundColor), .flags = 0, \
    .lowestobj = 0, .nextcon = 0}

struct GUI_PAGE
{
  struct GUI_CONTAINER *lowestcon;
  struct GUI_PAGE *nextpage;
  struct GUI_OBJECT *highestclickable;
};
#define GUI_CreatePage(PageName) struct GUI_PAGE PageName = { .lowestcon = 0, \
  .nextpage = 0, .highestclickable = 0}

#define GUI_Same(same1,same2) ((same1) == (same2))

/* OBJECT FUNCTIONS */

static void GUI_AddObject(struct GUI_CONTAINER *container,
  struct GUI_OBJECT *object)
{
  
  if(object->data == 0 && object->y2 != 0)
  {
    object->x1 += container->x;
    object->y1 += container->y;
    object->x2 += container->x;
    object->y2 += container->y; 
  }
  object->x0 += container->x;
  object->y0 += container->y;
 
  object->z += container->z;
 
  struct GUI_OBJECT *findspot = container->lowestobj;  
 
  if(object->z < findspot->z || findspot == 0)
  {
    object->nextobj = container->lowestobj;
    container->lowestobj = object;
    return;
  }
 
  while(findspot->nextobj && findspot->nextobj->z < object->z) // != 0
  {
    findspot= findspot->nextobj;
  }
  object->nextobj = findspot->nextobj;
  findspot->nextobj = object;
}

static void GUI_RemoveObject(struct GUI_CONTAINER *container,
  struct GUI_OBJECT *object)
{
  struct GUI_OBJECT *up = container->lowestobj;

  if(object == up)
  {
    container->lowestobj = up->nextobj;
  }
  else
  {
    while( object != up->nextobj)
    {
      up = up->nextobj;
    }
    
    up->nextobj = object->nextobj;
  } 

  if(object->data == 0 && object->y2 != 0)
  {
    object->x1 -= container->x;
    object->y1 -= container->y;
    object->x2 -= container->x;
    object->y2 -= container->y; 
  }
  object->x0 -= container->x;
  object->y0 -= container->y;

  object->z -= container->z;

  object->nextobj = 0;
}

static uint8_t GUI_PointInsideRect(struct MATH_POINT *p, void *rect)
{
  uint8_t ret = 0;

  uint16_t px = p->x;
  uint16_t py = p->y;


  if( (px >= (*(struct GUI_OBJECT *) rect).x0 && 
       px <= (*(struct GUI_OBJECT *) rect).x0 + (*(struct GUI_OBJECT *)
rect).x1) &&
      (py >= (*(struct GUI_OBJECT *) rect).y0 && 
       py <= (*(struct GUI_OBJECT *) rect).y0 + (*(struct GUI_OBJECT *)
rect).y1) )
  ret = 1; 
 
  return ret;
}

static uint8_t GUI_PointInsideCircle(struct MATH_POINT *p,
  struct GUI_OBJECT *circle)
{
  uint8_t ret = 0;

  int32_t circlex = circle->x0;
  int32_t circley = circle->y0;
  int32_t circler = circle->x1;

  if(circler * circler >= ((circlex - p->x) * (circlex - p->x)) +
    ((circley - p->y) * (circley - p->y)))
    ret = 1;

  return ret;
}

static uint8_t GUI_PointInsideTriangle(struct MATH_POINT *p, 
  struct GUI_OBJECT *triangle)
{
  uint8_t ret = 0;

  int32_t trianglex0 = triangle->x0;
  int32_t triangley0 = triangle->y0;
  int32_t trianglex1 = triangle->x1;
  int32_t triangley1 = triangle->y1;
  int32_t trianglex2 = triangle->x2;
  int32_t triangley2 = triangle->y2;

  float trianglearea = ((trianglex2 * -triangley1) + 
    (triangley0 * (trianglex2 - trianglex1)) +
    (trianglex0 * (triangley1 - triangley2)) +
    (trianglex1 * triangley2)) ;

  if(trianglearea < 0.0)
    trianglearea *= -1.0;

  float s = ((triangley0 * trianglex2) - (trianglex0 * triangley2) +
    (p->x * (triangley2 - triangley0)) +
    (p->y * (trianglex0 - trianglex2))) / (trianglearea);

  float t = ((trianglex0 * triangley1) - (triangley0 * trianglex1) +
    (p->x * (triangley0 - triangley1)) +
    (p->y * (trianglex1 - trianglex0))) / (trianglearea);

  float st = -s - t + 1;

if( s > 0.0 && t > 0.0 && st > 0.0)
  ret = 1;

  return ret;
}

static struct GUI_OBJECT * GUI_GetObjectTouched(struct GUI_PAGE *page, 
  struct MATH_POINT *p)
{
  struct GUI_OBJECT *down = page->highestclickable;


  while( down )
  {
    if(down->flags & GUI_OBJECT_FLAG_TRIANGLE) 
    {
      if(GUI_PointInsideTriangle(p,down))
      {
        return down;
      }
    }
    else if(down->flags & GUI_OBJECT_FLAG_CIRCLE)
    {
      if(GUI_PointInsideCircle(p,down))
      {
        return down;
      }
    }
    else //if(down->flags & GUI_OBJECT_FLAG_RECT) 
    {
      if(GUI_PointInsideRect(p,down))
      {
        return down;
      }
    }
  
    down = down->prevobj;
  }
  return 0;
}

static void GUI_AddClickableObject(struct GUI_PAGE *page, struct GUI_OBJECT
*object)
{
  struct GUI_OBJECT *down = page->highestclickable;

  if(down == 0 || object->z > down->z)
  {
    object->prevobj = page->highestclickable;
    page->highestclickable = object;
    return;
  }

  while(down->prevobj && down->prevobj->z > object->z) // != 0
  {
    down= down->prevobj;
  }
  object->prevobj = down->prevobj;
  down->prevobj = object;
}

#define GUI_CreateClickable(ClickableName, Page, Object) \
  struct GUI_CLICKABLE ClickableName = { Object, 0 }; \
  GUI_AddClickableObject(Page,&ClickableName);

/* END OBJECT FUNCTIONS */


/* CONTAINER FUNCTIONS */

static void GUI_InitContainer(struct GUI_CONTAINER *container, uint16_t x, 
  uint16_t y, int16_t z, uint16_t w, uint16_t h, uint16_t color)
{
  container->x = x;
  container->y = y;
  container->z = z;
  container->w = w;
  container->h = h;
  container->color = color;
  container->lowestobj = 0;
}

static void GUI_MoveContainer(struct GUI_CONTAINER *container, uint16_t x, 
  uint16_t y)
{
  struct GUI_OBJECT *up = container->lowestobj;

  while(up) //!= 0
  {
    up->x0 = up->x0 - container->x + x;
    up->y0 = up->y0 - container->y + y;
  
  //old ==== up->x0 = up->x0 - container->x + x + page->x;

    if(up->data == 0 && up->y2 != 0)
    {
      up->x1 = up->x1 - container->x + x;
      up->y1 = up->y1 - container->y + y;
      up->x2 = up->x2 - container->x + x;
      up->y2 = up->y2 - container->y + y;
    }

    up = up->nextobj;
  } 

  container->x = x;
  container->y = y; 
}

static void GUI_AddContainer(struct GUI_PAGE *page, struct GUI_CONTAINER
*container)
{
  struct GUI_CONTAINER *up = page->lowestcon;

  if(container->z < up->z || up == 0)
  {
    container->nextcon = page->lowestcon;
    page->lowestcon = container;
    return;
  }

  while(up->nextcon && up->nextcon->z < container->z) // != 0
  {
    up= up->nextcon;
  }
  container->nextcon = up->nextcon;
  up->nextcon = container;
}

static void GUI_SetContainerZ(struct GUI_PAGE *page, struct GUI_CONTAINER
*container, 
  int16_t zval)
{

  struct GUI_OBJECT *up = container->lowestobj;

  while( up )
  {
    up->z = up->z - container->z + zval;
    up = up->nextobj;
  }
  //change z value for each object in container too

  struct GUI_CONTAINER *conup = page->lowestcon;

  if(GUI_Same(container,conup))
  {
    page->lowestcon = container->nextcon;
  }
  else
  {
    while(!GUI_Same(container,conup->nextcon))
    {
      conup = conup->nextcon;
    }
    conup->nextcon = container->nextcon;
    //Take container out of link list
  }
  
  container->z = zval;
  GUI_AddContainer(page,container);  
}

static uint8_t GUI_ContainerOverlap(struct GUI_CONTAINER *ob1, struct
GUI_CONTAINER *ob2)
{
  uint8_t ret = 0;

  if( (ob1->x < ob2->x + ob2->w) && (ob1->x + ob1->w > ob2->x) &&
      (ob1->y < ob2->y + ob2->h) && (ob1->y + ob1->h > ob2->y) )
    ret = 1;

    return ret;
}

static uint8_t GUI_ContainerInside(struct GUI_CONTAINER *outside, struct
GUI_CONTAINER *inside)
{
  uint8_t ret=0;

  uint16_t insidex = inside->x;
  uint16_t insidey = inside->y;
  uint16_t insidew = inside->w;
  uint16_t insideh = inside->h;
  
  uint16_t outsidex = outside->x;
  uint16_t outsidey = outside->y;
  uint16_t outsidew = outside->w;
  uint16_t outsideh = outside->h;


  if( (insidex >= outsidex && insidex <= outsidex + outsidew) &&
      (insidex + insidew >= outsidex && insidex + insidew <= outsidex +
outsidew) &&
      (insidey >= outsidey && insidey <= outsidey + outsideh) &&
      (insidey + insideh >= outsidey && insidey + insideh <= outsidey +
outsideh) )
  {
    ret = 1;
  }
  return ret;
}

static void GUI_PrintContainer(struct GUI_CONTAINER *container)
{  
  struct GUI_CONTAINER *conup = container;
 
  uint16_t conx = container->x;
  uint16_t cony = container->y;
  uint16_t conw = container->w;
  uint16_t conh = container->h;
 
  while(conup)
  {
    uint16_t conupx = conup->x;
    uint16_t conupy = conup->y;
    uint16_t conupw = conup->w;
    uint16_t conuph = conup->h;
    uint16_t conupcolor = conup->color;  

    if( (conupx < conx + conw) && (conupx + conupw > conx) &&
        (conupy < cony + conh) && (conupy + conuph > cony) )   
    {
      if(conupcolor) // != 0
      {
        LCD_FillRect(conupx, conupy, conupw, conuph, conupcolor);
      } 
    
      struct GUI_OBJECT *up = conup->lowestobj;
      while(up) //!= 0
      {
        GUI_PrintObject(*up);
        up = up->nextobj;
      }
    }
  conup = conup->nextcon;
  }
}


static void GUI_PrintCont(struct GUI_CONTAINER *container)
{  
 
      if(container->color) // != 0
      {
        LCD_FillRect(container->x, container->y, container->w, container->h, 
          container->color);
      } 
    
      struct GUI_OBJECT *up = container->lowestobj;
      while(up) //!= 0
      {
        GUI_PrintObject(*up);
        up = up->nextobj;
      }
}



static void GUI_UpdateContainerArea(struct GUI_PAGE *page, struct GUI_CONTAINER
*container)
{
  struct GUI_CONTAINER *conup, *backgroundcon;
  conup = backgroundcon = page->lowestcon;

  int32_t containerspot = 0;
  
  while(!GUI_Same(container,conup))
  {
    if(conup->color && GUI_ContainerInside(conup,container))
    {
      backgroundcon = conup;
    }
    conup = conup->nextcon;  
  }

  conup = backgroundcon;
  containerspot = conup->z;
  while(conup)
  {
    if(!GUI_Same(container,conup))
    {
      if(conup->color) // != 0
      {
        LCD_FillRect(conup->x, conup->y,  conup->w,  conup->h,
        conup->color);
      } 
      
      struct GUI_OBJECT *up = conup->lowestobj;
      while(up) //!= 0
      {
        GUI_PrintObject(*up);
        up = up->nextobj;
      }
      
      while(conup->nextcon && conup->nextcon->z == containerspot)
      {
        conup = conup->nextcon;
      }
    }
    conup = conup->nextcon;
  }
}

/* END CONTAINER FUNCTIONS */

static void GUI_PrintPage(struct GUI_PAGE *page)
{
  struct GUI_CONTAINER *up = page->lowestcon;

  while(up)
  {
    GUI_PrintCont(up);
    up = up->nextcon;
  }
}



#endif
