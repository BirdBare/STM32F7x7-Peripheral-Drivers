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



#define SVCall(void) __asm("svc 0")
#define PENDSV(void) SCB->ICSR = 0b1 << 28
#define SYSTICK(void) SCB->ICSR = 0b1 << 26

#define PENDSV_PENDING(void) SCB->ICSR = 0b1 << 28
#define SYSTICK_PENDING(void) SCB->ICSR = 0b1 << 26




/* DESIGN OF THREAD STACK 

8 Thread example adding thread

     <-Thread execution moves this way
     ^
<-|  |  |  |  |  |  |<-wrap around
    ^
    new thread addred here if high priority

     <-Thread execution moves this way
     ^
<-|  |  |  |  |  |  |<-wrap
      ^
      new thread added here if low priority

Can also:
Place next to certain thread if required.
Choose next thread to execute regaurdless of thread order

*/

/*    FLAGS

    [31] = SCHEDULER HOLD BIT

*/



/* THREAD FLAGS 

  [0] - THREAD create placement. 1 - before, 0 - after. AND Thread Pause Bit

  [3:1] - THREAD LABEL BITS - USER CREATED

*/
#define THREAD_PAUSE ((uint32_t)1)
#define THREAD_LABEL ((uint32_t)0b111 << 1)

struct NEW_THREAD
{
  void *sp; //current location of stack pointer 

  struct NEW_THREAD volatile *next; //next thread to be executed after this thread
  struct NEW_THREAD volatile *prev; //prev thread that was just executed
  
  uint32_t flags;
} extern volatile MAIN;

/* SCHEDULER FLAGS 


  [30] - SCHEDULER SWITCH HOLD BIT - USED DURING SOFTWARE SCHEDULER SWITCH

  [31] - SCHEDULER HOLD BIT - PREVENTS SCHEDULER FROM SWITCHING TASK

*/
#define SCHEDULER_SWH ((uint32_t)1 << 30)
#define SCHEDULER_HOLD ((uint32_t)1 << 31)

struct NEW_SCHEDULER
{
  struct NEW_THREAD volatile *thread; //points to current running thread.
  uint32_t flags;


} extern volatile SCHEDULER;



// THE THREAD SWITCH FUNCTION.
  void* KERNEL_Switch(volatile struct NEW_SCHEDULER *sched,
    volatile struct NEW_THREAD *current, uint32_t currentthreadflags, 
    volatile struct NEW_THREAD *next);

struct NEW_THREAD* CreateT(uint32_t stacksize, uint32_t flags, void *func, void *args);

/*

      TODO LIST

  add deallocation to KERNEL_ThreadReturn

  add move thread function

  add delete thread function

  add way to call the thread switcher without SysTick






*/



#endif
