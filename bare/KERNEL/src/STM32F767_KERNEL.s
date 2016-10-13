

.syntax unified
.cpu cortex-m7
.fpu fpv5-d16
.thumb

      .section ._ITCM.SCHEDULING



  .type  CreateT, %function
  .global CreateT
CreateT:
 
push {r0-r12,lr} //push our registers and callee save registers onto stack
bl balloc
pop {r1-r4}

cbnz r0, _SpaceAvailable //if balloc did not return zero then space available 
b _NoSpace

_SpaceAvailable:

ands r5, #1 //and compare to see if before bit is set

ldr r5, =SCHEDULER //load NSCHEDULER address

mov r10, r3 //move function address into pc spot 

and r2, #~1 //Turn off Thread pause bit incase it is set

ldr r3, [r5] //get address of current running thread

str r2, [r0, #12] //store flags into flag variable


ldr r6, [r3, #4] //get current->next address

ldr r7, [r3, #8] //get current->prev address


// ADD BEFORE 
beq _After

str r6, [r0, #4] //store address of current->next into new next 

str r3, [r0, #8] //store address of current thread in new->prev 

str r0, [r6, #8] //store address of new thread in current->next->prev

str r0, [r3, #4] //store address of new thread in current->next

bne _Before //if flags is 1 then branch

_After:

  // ADD AFTER 
  str r3, [r0, #4] //store address of current thread in new->next 

  str r7, [r0, #8] //store address of current->prev into new prev 

  str r0, [r7, #4] //store address of newthread in current->prev->next

  str r0, [r3, #8] //store address of new thread in current->prev


_Before:

mov r8, #0            //set r12 to zero for new function

mov r7, r0            //store thread address into callee save variable so it is not
                        //deleted

mov r11, #0b100001   //start setting PSR value 

ldr r9, =KERNEL_ThreadReturn  //set link register to thread return

add r1, r0 //set start location of task sp

mov r11, r11, lsl #24 //set PSR to default value 

stmdb r1!, {r4-r11} // push vital peices to new stack 
stmdb r1!, {r4-r11} // push rest of dont care registers to fill stack 

str r1, [r0] //store stack pointer in sp of new thread

_NoSpace:

pop {r4-r12, lr}
    bx lr

  .type  KERNEL_ThreadReturn, %function
KERNEL_ThreadReturn:

//  NONE OF THE REGISTERS MATTER BECAUSE WE WILL DELETE THREAD AT SCHEDULE SWITCH

ldr r4, =0xE000ED04 //Load ICSR address

mov r5, #0 //mov zero for setting the sp to zero

ldr r6, [r4] //get ICSR value

str r5, [r7] //set thread sp zero

orr r6, #1 << 26       //Set SystickInterrupt bit. in callee save so it will be
                      //here after calling bree so we can officially load it.

str r6, [r4] //officially Call Scheduler for the switch and delete

lop: //never end because we need to kill it with the SCHEDULER
b lop


/*    INLINED IN SYSTICK HANDLER

    .section ._ITCM_RAM.SCHEDULING //(struct NEW_SCHEDULER *sched,
                         //   struct NEW_Thread *current) *
  .global KERNEL_Scheduler
  .type  KERNEL_Scheduler, %function
KERNEL_Scheduler:
  
  ldr r3, [r1, #4] //load current->next
  
  ldr r2, [r1] //get saved value of sp
  
  cmp r3, r1 //compare current and next to see if they are the same

  cbnz r2, _KNoDel //if sp is not zero then dont delete the thread and thread to run
  
  ldr r2, [r1, #8]          // load current->prev for possible delete  
  
  bne _KTestSafe
  
    b KERNEL_NoThreads // if sp is zero and next and current are same then all threads
                        //are gone so we need to do something about that 
  _KTestSafe:
    
    str r2, [r3, #8] //set next->prev=current->prev
    str r3, [r2, #4] //set prev->next=current->next
    
  b _KDeleted
    
  _KNoDel:
  
    mrs r12, psp //get current thread sp memory address
  
    it eq
    bxeq lr       //if current and next are same then quit since we dont need to switch
  
    stmdb r12!, {r4-r11}     // save the context of the rest of the registers 
    str r12, [r1]            // save the address of the stack pointer to the sp variable
  
  _KDeleted:  

   //branch to kernel switch 
   //assumes the new sp is in r0 
  
  push {ip,lr}
    ldr r1, [r1, #12]
  bl KERNEL_Switch

  ldmia r0!, {r4-r11}
  pop {ip,lr}
  msr psp, r0
  
bx lr
*/

/*  MEMORY USAGE STRUCTURE

END OF THREAD MEMORY (Higher Mem Address) 
----------------------    
  Start of stack
\/stack moves down\/
    -data-
    -data-
    -data-
  Current sp (somewhere in thread memory
  


  [thread flags]    4
  [prev thread *]   4
  [next thread *]   4
  [stack pointer] + 4
  Thread structure  16 bytes 
----------------------
START OF THREAD MEMORY (Lower Mem Address)
*/

  .type  SysTick_Handler, %function
  .global SysTick_Handler
SysTick_Handler:
  
  ldr r2, =0xE000E010 //load address of systick control register

  ldr r0, =SCHEDULER //gets address of NSCHEDULER 

  ldr r2, [r2] //load systick control register value

  ldr r3, =SysTick_MilliSec //gets address of SysTick_MilliSec variable 

  ldr r1, [r0] //load thread address to check if only one thread
  
  ands r2, #1 << 16 //test if countflag is set. The countflag gets set everytime  //the counter counts to zero. So we can make sure it was a
                    //counter interrupt or a program interrupt. That way we only
                    //need to write one interrupt handler for the scheduler.
 
  ldr r12, [r3] //load value of SysTick_MilliSec

  ldr r2, [r1, #4] //load next thread to see if same
   
  add r12, #1 //increment systick_MilliSec by 1 
  
  beq _NotCalled //if systick call bit is not equal to zero (not set) then we skip the below code. We
                 //do not need to increment the clock this time.
  
    str r12, [r3] //store new SysTick_MilliSec value
  
    ldr r12, [r0, #4] //load flags variable value
  

    and r3, r12, #1 << 31 //scheduler hold flag test. if set then we dont schedule
    cbnz r3, __EXIT

    ands r3, r12, #1 << 30 //scheduler switch hold flag test. if set then we dont schedule for one round. so we also clear the bit
    
    and r3, r12, #~(1 << 30) //clear switch hold bit.
    str r3, [r0, #4]      //str new flag value.

    bne __EXIT
    
  _NotCalled:

  cmp r2, r1 //compare to see if addresses are the same

  beq __EXIT //if thread and next thread are equal we don't need to do anything

  //it ne        //will always execute if SysTick is called without reaching zero.
 // bxne lr      //return if not equal to zero. Which means disable bit is set

  // START INLINE KERNEL_Scheduler function 

    push {ip,lr} //push lr for function return

    ldr r3, [r1] //load current thread stack pointer address

    ldr r12, [r1, #8]          // load current->prev for possible delete  

    cbnz r3, _KNoDel //if sp is not zero then dont delete the thread and thread to run
   
      str r12, [r2, #8] //set current->next->prev=current->prev
      str r2, [r12, #4] //set current->prev->next=current->next
    
    b _KDeleted
    
    _KNoDel:

//      ldr r2, =0xE000EF38 //get float point context address register

      mrs r12, psp //get current thread sp memory address
  
//      str r12, [r2] //set FPCAR to current psp value. Task Stack.

//      and r2, lr, #

      stmdb r12!, {r4-r11}     // save the context of the rest of the registers 
      str r12, [r1]            // save the address of the stack pointer to the sp variable
  
    _KDeleted:  

    //branch to kernel switch 
    //assumes the new sp is in r0 
   
    ldr r2, [r1, #12] //get current thread flags for function call

    
  
    bl KERNEL_Switch

    //loads new thread values of threads stack

    ldmia r0!, {r4-r11} // load thread values
    
    pop {ip,lr} 
    
    msr psp, r0 //store new stack pointer address into process stack pointer

  // END INLINE 

  __EXIT:

bx lr








