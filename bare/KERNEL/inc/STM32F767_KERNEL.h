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



#define SVCall(void) __asm("svc 0")
#define PENDSV(void) SCB->ICSR = 0b1 << 28
#define SYSTICK_Interrupt(void) SCB->ICSR = 0b1 << 26

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












/* THREAD FLAGS 

  [0] - THREAD create placement. 1 - before, 0 - after. AND Thread Pause Bit

  [3:1] - THREAD LABEL BITS - USER CREATED

*/
enum THREAD_FLAGS
{
  THREAD_HOLD = 1 << 31
  
};

struct THREAD
{

  struct THREAD volatile *next; //next thread to be executed after this thread
  struct THREAD volatile *prev; //prev thread that was just executed
  
  void *sp; //current location of stack pointer 

  uint32_t flags;
  uint32_t idlequit; //time thread is idle until in systick ticks

} extern volatile MAIN;

ALWAYS_INLINE void THREAD_SetHold(volatile struct THREAD *thread)
{
  thread->flags |= THREAD_HOLD;
}
ALWAYS_INLINE void THREAD_ResetHold(volatile struct THREAD *thread)
{
  thread->flags |= THREAD_HOLD;
}
ALWAYS_INLINE void THREAD_SetIdleQuit(volatile struct THREAD *thread,
  uint32_t QuitTime)
{
  thread->idlequit = QuitTime;
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
    SYSTICK_Interrupt(); \
    ASM(""); \
  } while(0)























// THE THREAD SWITCH FUNCTION.
  void* KERNEL_SwitchHandler(volatile struct THREAD *current);

  void KERNEL_DeleteHandler(volatile struct THREAD *current);

struct THREAD* KERNEL_CreateTask(uint32_t stacksize, uint32_t flags, void *func, void *args);

#define CreateT(stacksize,ThreadFlags,func,args) \
  do \
  { \
    struct THREAD* newthread = \
      KERNEL_CreateTask(stacksize,ThreadFlags,func,args); \
    newthread->flags = ThreadFlags; \
    newthread->idlequit = 0; \
    DLL_AddNodeAfter(newthread, \
      (void *)(SCHEDULER_CurrentThread(&SCHEDULER))); \
  } while(0);
/*

      TODO LIST

  add deallocation to KERNEL_ThreadReturn

  add move thread function

  add delete thread function

  add way to call the thread switcher without SysTick






*/



#endif
