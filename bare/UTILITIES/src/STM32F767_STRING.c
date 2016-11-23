//
//
//
//
//



#include "STM32F767_STRING.h"

void String_IntToString(uint32_t intnumber, uint8_t chararray[])
{
  uint32_t charspot = 0;

  uint8_t charholder[10];

  do
  {
    charholder[charspot] = '0' + (intnumber % 10);

    intnumber /= 10;
    charspot++;

  } while(intnumber != 0);

  uint32_t spot = 0;

  do
  {
    charspot--;
    chararray[spot] = charholder[charspot];
    spot++;
  } while(charspot != 0);

  chararray[spot] = '\n';
}







