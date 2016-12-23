//
//
//
//
//



#ifndef STM32F767_NEWKERNEL_H
#define STM32F767_NEWKERNEL_H
#define LOOP while(1) asm("");



#include "stm32f7xx.h"
#include "STM32F767_SYSTICK.h"
#include "STM32F767_BALLOC.h"
#include "STM32F767_DLL.h"


#define SVCall_Interrupt(void) __asm("svc 0")
#define PendSV_Interrupt(void) SCB->ICSR = 0b1 << 28
#define SysTick_Interrupt(void) SCB->ICSR = 0b1 << 26

#define PENDSV_PENDING(void) SCB->ICSR = 0b1 << 28
#define SYSTICK_PENDING(void) SCB->ICSR = 0b1 << 26






/* THREAD FLAGS 

  [0] - THREAD create placement. 1 - before, 0 - after. AND Thread Pause Bit

  [3:1] - THREAD LABEL BITS - USER CREATED

*/
enum THREAD_FLAGS
{
  THREAD_COMPSETRESET = 1 << 4, 
  THREAD_TIMEOUTMAX = 0b1111 << 0 
};

struct THREAD
{

  struct THREAD volatile *next; //next thread to be executed after this thread
  struct THREAD volatile *prev; //prev thread that was just executed
  
  void *sp; //current location of stack pointer 

  uint32_t flags;
  uint32_t timeoutcount;

  uint32_t temp1; 
  uint32_t temp2; 
  //general use
  //for DelayMilli: temp1 = Reference Time
  //                temp2 = Delay time in MilliSec
  //
  //for PERIPH_WaitTill: temp1 = status register address
  //                     temp2 = flag to wait for

} extern volatile MAIN;

ALWAYS_INLINE void THREAD_SetHold(volatile struct THREAD *thread)
{
  thread->temp2 = ~0; //set to max value so it never stops delay
}
ALWAYS_INLINE void THREAD_ResetHold(volatile struct THREAD *thread)
{
  thread->temp2 = 0; //set to min so it never delays
}
















/* SCHEDULER FLAGS 


  [30] - SCHEDULER SWITCH HOLD BIT - USED DURING SOFTWARE SCHEDULER SWITCH

  [31] - SCHEDULER HOLD BIT - PREVENTS SCHEDULER FROM SWITCHING TASK

*/
enum SCHEDULER_FLAGS
{
  SCHEDULER_HOLD = 1 << 31,
  SCHEDULER_SWHOLD = 1 << 30
};

struct SCHEDULER
{
  struct THREAD volatile *thread; //points to current running thread.
  uint32_t flags;

} extern volatile SCHEDULER;

ALWAYS_INLINE void SCHEDULER_SetHold(volatile struct SCHEDULER *SCHEDULER) 
{
  SCHEDULER->flags |= SCHEDULER_HOLD;
}
ALWAYS_INLINE void SCHEDULER_ResetHold(volatile struct SCHEDULER *SCHEDULER)
{
SCHEDULER->flags &= ~SCHEDULER_HOLD;
}
ALWAYS_INLINE void SCHEDULER_SetSwitchHold(volatile struct SCHEDULER *SCHEDULER) 
{
  SCHEDULER->flags |= SCHEDULER_SWHOLD;
}
ALWAYS_INLINE struct THREAD* SCHEDULER_CurrentThread(volatile struct SCHEDULER *SCHEDULER)
{
  struct THREAD* ret;
  ASM("ldr %0, [%1]" : "=r" (ret) : "r" (SCHEDULER));
  return ret;

}

#define SCHEDULER_CallScheduler(void) \
  do \
  { \
    SCHEDULER_SetSwitchHold(&SCHEDULER); \
    PendSV_Interrupt(); \
    ASM(""); \
  } while(0)


















	//KERNEL VARIABLES
	
	extern struct HEAP_TABLE *KERNEL_ProcessHeap, *KERNEL_ThreadHeap,
		*KERNEL_FastHeap;



	// DYNAMIC ALLOCATION	
		#define balloc(size) kballoc(size,KERNEL_ProcessHeap)
		#define fastballoc(size) kballoc(size,KERNEL_FastHeap)


  void* KERNEL_SwitchHandler(struct THREAD *current);

  struct THREAD* KERNEL_DeleteHandler(struct THREAD *current);

struct THREAD* KERNEL_CreateTask(uint32_t stacksize, uint32_t flags, void *func, void *args);

#define CreateT(stacksize,ThreadFlags,func,args) \
  do \
  { \
    struct THREAD* newthread = \
      KERNEL_CreateTask(stacksize + 224,ThreadFlags,func,args); \
		if(newthread != 0) \
		{ \
			newthread->flags = ThreadFlags; \
			newthread->timeoutcount = 0; \
			newthread->temp1 = 0; \
			newthread->temp2 = 0; \
			DLL_AddNodeAfter(newthread, \
				(void *)(SCHEDULER_CurrentThread(&SCHEDULER))); \
		} \
  } while(0);
/*

      TODO LIST

  add deallocation to KERNEL_ThreadReturn

  add move thread function

  add delete thread function

  add way to call the thread switcher without SysTick






*/



#endif
