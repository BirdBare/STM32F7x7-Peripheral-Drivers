//
//
//
//
//



#ifndef STM32F767_BUFFER_H
#define STM32F767_BUFFER_H

#include "stm32f7xx.h"
#include "STM32F767_BALLOC.h"

#define CreateBuffer(BufferName, BufferSize, DataSize) \
  uint##DataSize##_t BufferName##_MemArea[BufferSize];\
  struct BUFFER##DataSize BufferName = \
    {(uint8_t *)BufferName##_MemArea,0,0,BufferSize}

struct BUFFER8
{
  uint8_t *buffer;
        
  uint32_t write;
  uint32_t read;
                    
  uint32_t buffersize;
};

uint32_t BUFFER8_Write(struct BUFFER8 *buffer, uint32_t data)
{
  uint32_t next = (buffer->write + 1) % buffer->buffersize;

  if(next != buffer->read)
  {
    *(buffer->buffer + buffer->write) = data;
                            
    buffer->write = next;
                                        
    return 1;
  }
  return 0;
}

uint32_t BUFFER8_Read(struct BUFFER8 *buffer, uint8_t *data)
{
  uint32_t readpos = buffer->read;

  if(readpos != buffer->write)
  {
    *data = *(buffer->buffer + readpos);
                        
    readpos++;
                                    
    buffer->read = readpos % buffer->buffersize; 
                                                    
    return 1;
  }

  return 0;
}

struct BUFFER16
{
  uint16_t *buffer;
        
  uint32_t write;
  uint32_t read;
                    
  uint32_t buffersize;
};

uint32_t BUFFER16_Write(struct BUFFER16 *buffer, uint32_t data)
{
  uint32_t next = (buffer->write + 1) % buffer->buffersize;

  if(next != buffer->read)
  {
    *(buffer->buffer + buffer->write) = data;
                            
    buffer->write = next;
                                        
    return 1;
  }
  return 0;
}

uint32_t BUFFER16_Read(struct BUFFER16 *buffer, uint16_t *data)
{
  uint32_t readpos = buffer->read;

  if(readpos != buffer->write)
  {
    *data = *(buffer->buffer + readpos);
                        
    readpos++;
                                    
    buffer->read = readpos % buffer->buffersize; 
                                                    
    return 1;
  }

  return 0;
}


struct BUFFER32
{
  uint32_t *buffer;
        
  uint32_t write;
  uint32_t read;
                    
  uint32_t buffersize;
};

uint32_t BUFFER32_Write(struct BUFFER32 *buffer, uint32_t data)
{
  uint32_t next = (buffer->write + 1) % buffer->buffersize;

  if(next != buffer->read)
  {
    *(buffer->buffer + buffer->write) = data;
                            
    buffer->write = next;
                                        
    return 1;
  }
  return 0;
}

uint32_t BUFFER32_Read(struct BUFFER32 *buffer, uint32_t *data)
{
  uint32_t readpos = buffer->read;

  if(readpos != buffer->write)
  {
    *data = *(buffer->buffer + readpos);
                        
    readpos++;
                                    
    buffer->read = readpos % buffer->buffersize; 
                                                    
    return 1;
  }

  return 0;
}


#endif
