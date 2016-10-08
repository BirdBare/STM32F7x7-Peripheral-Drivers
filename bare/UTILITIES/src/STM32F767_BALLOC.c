//
//
//
//
//



#ifndef STM32F767_MALLOC_H
#define STM32F767_MALLOC_H

#include "stm32f7xx.h"

#define HEAPMINBOUNDRY 0x20000000

#define HEAPMAXSIZE (1024 * 50)
#define MAXSIZE_BITS (MALLOC_BIT31 - 1)
#define MALLOC_BIT31 ((uint32_t)0x80000000)
void *FIRSTSPACEFREEHEAP = 0;

struct ALLOC_TABLE
{
  uint32_t size; //bit [31] is the free flag. 0 == in use, 1 == free
  struct ALLOC_TABLE *next;
};

/* BLOCK STRUCTURE

----- Dynamic block

  ALLOC_TABLE 12bytes
  Dynamically allocated data

----- end of block

*/


__attribute__((section("._ITCM.balloc"))) void InitHeap(void)
{
  extern void *start asm("_end"); //start of heap section of memory
    FIRSTSPACEFREEHEAP = start = (uint8_t *)&start + 4; 
    //four bytes after the end symbol is into heap memory and is aligned

    ((struct ALLOC_TABLE *)start)->size = MALLOC_BIT31 | HEAPMAXSIZE;
    //Set Max Size and memory Free flag

    ((struct ALLOC_TABLE *)start)->next = 0; 
}

__attribute__((section("._ITCM.balloc"))) void* balloc(uint32_t size)
{
  if((uint32_t)FIRSTSPACEFREEHEAP < HEAPMINBOUNDRY)
    return 0;

  size += sizeof(struct ALLOC_TABLE); //add size of allocation table to data

  while(size & 3) // size % 4. Makes sure we are aligned by four
  {
    size++;
  }
  //aligns the end of the block to keep memory straight

  void *start = FIRSTSPACEFREEHEAP;

  while(start)//while we are not past the end empty block
  {
  if((((struct ALLOC_TABLE *)start)->size & MALLOC_BIT31))
  {
    if(((struct ALLOC_TABLE *)start)->next && 
      (((struct ALLOC_TABLE *)start)->next->size & MALLOC_BIT31))
    //only run if current memory and next memory is flagged free.
    {
      ((struct ALLOC_TABLE *)start)->size +=
      ((struct ALLOC_TABLE *)start)->next->size & MAXSIZE_BITS;
      //add the size of both blocks together      

      ((struct ALLOC_TABLE *)start)->next = 
      ((struct ALLOC_TABLE *)start)->next->next;
      //connect the chain by making next equal to the added blocks next 
    }
 
    uint32_t blocksize = ((struct ALLOC_TABLE *)start)->size & MAXSIZE_BITS;
    //Bring out of memory into local variable for speed

    if( (blocksize >= size + sizeof(struct ALLOC_TABLE)))
    //only run if current block is free and it is big enough
    {
      ((struct ALLOC_TABLE *)(start + size))->size = (blocksize - size) |
MALLOC_BIT31;
      ((struct ALLOC_TABLE *)(start + size))->next = ((struct ALLOC_TABLE
*)start)->next;
      //construct a new empty block following the used block

      ((struct ALLOC_TABLE *)start)->next = (struct ALLOC_TABLE *)(start +
size);
      //setup new block for user by connection chain

      done:
      ((struct ALLOC_TABLE *)start)->size = size ;
      //always equate size to reset the free flag to used

      if(!(((struct ALLOC_TABLE *)FIRSTSPACEFREEHEAP)->size & MALLOC_BIT31) && 
        ((struct ALLOC_TABLE *)start)->next !=0)
      {  
        FIRSTSPACEFREEHEAP = start + size;
      }
      //if the newly created spot is the current free heap spot procede to next
      // free spot

      return start + sizeof(struct ALLOC_TABLE);
      //finished so return address of user block but skip over ALLOC_TABLE
    }
    else if(blocksize == size)
    {
      goto done;
    }
    //if the size is exactly the same we can return without creating an
    // empty block
    
    }
    start = (uint8_t *)((struct ALLOC_TABLE *)start)->next;
  }
return 0;
}

__attribute__((section("._ITCM.balloc"))) void bree(void *blockaddress)
{
  blockaddress = (struct ALLOC_TABLE *)blockaddress - 1;
  //decrement to get to beginning of ALLOC_TABLE

   ((struct ALLOC_TABLE *)blockaddress)->size |= MALLOC_BIT31;
  
  if(blockaddress < FIRSTSPACEFREEHEAP)
  {
    FIRSTSPACEFREEHEAP = blockaddress;
  }

}




/* Old Free If statement
  if(((struct ALLOC_TABLE *)blockaddress)->start && 
    (((struct ALLOC_TABLE *)blockaddress)->start->size & MALLOC_BIT31))
  {
    ((struct ALLOC_TABLE *)blockaddress)->start->size +=
      ((struct ALLOC_TABLE *)blockaddress)->size & MAXSIZE_BITS;

    ((struct ALLOC_TABLE *)blockaddress)->start->next = 
      ((struct ALLOC_TABLE *)blockaddress)->next;

    blockaddress -= ((struct ALLOC_TABLE *)blockaddress)->size & MAXSIZE_BITS;
  }
  else
  {
*/
 


#endif
