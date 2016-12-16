//
//
//
//
//

#include "stm32f7xx.h"
#include "STM32F767_BALLOC.h"
#include "STM32F767_KERNEL.h"


__attribute__((section("._ITCM.balloc"))) void InitHeap(void *start,
	uint32_t size)
{
		size -= sizeof(struct HEAP_TABLE);

    ((struct HEAP_TABLE *)start)->freeheap = 
			(start + sizeof(struct HEAP_TABLE)); 

    ((struct HEAP_TABLE *)start)->size = size; 

		start += sizeof(struct HEAP_TABLE);

    ((struct ALLOC_TABLE *)start)->size = size;
    //Set Max Size and memory Free flag

    ((struct ALLOC_TABLE *)start)->next = 0; 
    ((struct ALLOC_TABLE *)start)->heap = 0; 
}

__attribute__((section("._ITCM.balloc"))) void* kballoc(uint32_t size,
	struct HEAP_TABLE *MemArea)
{
  size += sizeof(struct ALLOC_TABLE); //add size of allocation table to data

  while(size & 3) // size % 4. Makes sure we are aligned by four
  {
    size++;
  }
  //aligns the end of the block to keep memory straight

  void *start = MemArea->freeheap;

  while(start)//while we are not past the end empty block
  {
		if((((struct ALLOC_TABLE *)start)->heap == 0))
		{
			while(((struct ALLOC_TABLE *)start)->next && 
				(((struct ALLOC_TABLE *)start)->next->heap == 0))
			//only run if current memory and next memory is flagged free.
			{
				((struct ALLOC_TABLE *)start)->size +=
					((struct ALLOC_TABLE *)start)->next->size;
				//add the size of both blocks together      

				((struct ALLOC_TABLE *)start)->next = 
					((struct ALLOC_TABLE *)start)->next->next;
				//connect the chain by making next equal to the added blocks next 
			}
 
			uint32_t blocksize = ((struct ALLOC_TABLE *)start)->size;
			//Bring out of memory into local variable for speed

			if( (blocksize >= size + sizeof(struct ALLOC_TABLE)))
			//only run if current block is free and it is big enough
			{
				((struct ALLOC_TABLE *)(start + size))->size = (blocksize - size);
				((struct ALLOC_TABLE *)(start + size))->heap = 0;
				((struct ALLOC_TABLE *)(start + size))->next = 
					((struct ALLOC_TABLE *)start)->next;
				//construct a new empty block following the used block

				((struct ALLOC_TABLE *)start)->next =	
					(struct ALLOC_TABLE *)(start + size);
				//setup new block for user by connection chain

				done:
				((struct ALLOC_TABLE *)start)->size = size ;
				//always equate size to reset the free flag to used
				((struct ALLOC_TABLE *)start)->heap = MemArea ;

				if((((struct ALLOC_TABLE *)*(uint32_t *)MemArea)->heap) != 0 && 
					((struct ALLOC_TABLE *)start)->next !=0)
				{  
					MemArea->freeheap = (start + size);
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

	void *heap = ((struct ALLOC_TABLE *)blockaddress)->heap;

  ((struct ALLOC_TABLE *)blockaddress)->heap = 0;
  
  if(blockaddress < (void *)*(uint32_t *)heap)
  {
    *(uint32_t *)heap = (uint32_t)blockaddress;
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
 

