//
//
//
//
//



#include "STM32F767_BUFFER.h"

//BUFFER 8

uint32_t BUFFER8_Write(struct BUFFER8 *buffer, uint32_t data)
{
  uint32_t next = (buffer->write + 1) & buffer->buffersize;

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
                                    
    buffer->read = readpos & buffer->buffersize; 
                                                    
    return 1;
  }

  return 0;
}


// BUFFER 16

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


//BUFFER 32

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


