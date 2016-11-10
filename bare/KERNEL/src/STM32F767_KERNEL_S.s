

.syntax unified

      .section ._ITCM.SCHEDULING

  .type  DelayMilli, %function
  .global DelayMilli
DelayMilli:
  
  ldr r1, =SysTick_MilliSec

  ldr r12, =0xE000ED04

  ldr r2, [r1] //get ref

  DelayMilli_Loop:

    mov r3, #1 << 26

    str r3, [r12]  //set systick pending bit

    ldr r3, [r1] //get millisec

    sub r3, r2  //get MilliSec - ref

    cmp r0, r3  //check if millisec is less than milli r0

  bhi DelayMilli_Loop

bx lr




  .type  CreateT, %function
  .global CreateT
CreateT:
 
push {r0-r12,lr} //push our registers and callee save registers onto stack
bl balloc
pop {r1-r4}

cbz r0, _NoSpace //if balloc did not return zero then space available 

ands r2, #1 //and compare to see if before bit is set

and r2, #~1 //Turn off Thread pause bit incase it is set

str r2, [r0, #12] //store flags into flag variable

mov r10, r3 //move function address into pc spot 

mov r8, #0            //set r12 to zero for new function

mov r11, #0x1000000   //set PSR Reset value 

ldr r9, =KERNEL_ThreadReturn  //set link register to thread return

add r1, r0 //set start location of task sp

stmdb r1!, {r4-r11} // push vital peices to new stack 
stmdb r1!, {r4-r11} // push rest of dont care registers to fill stack 

ldr r12, =0xfffffffD  //Generic Exception return. Would be used by starting task

vstmdb r1!, {d0-d15} //push FPU registers to stack

stmdb r1!, {r11 - r12}
//sets link register from expection return to start this task
//Use thread mode, PSP, FPU value doesnt matter because task just started

str r1, [r0, #8] //store stack pointer in sp of new thread

ldr r5, =SCHEDULER //load NSCHEDULER address

mov r7, r0            //store thread address into callee save variable so it is not deleted

ldr r1, [r5] //get address of current running thread



// ADD BEFORE 
beq _After

ldr r2, =DLL_AddNodeBefore
blx r2

bne _Before //if flags is 1 then branch

_After:

  // ADD AFTER 
ldr r2, =DLL_AddNodeAfter
blx r2

_Before:



_NoSpace:

pop {r4-r12, lr}
    bx lr

  .type  KERNEL_ThreadReturn, %function
KERNEL_ThreadReturn:

//  NONE OF THE REGISTERS MATTER BECAUSE WE WILL DELETE THREAD AT SCHEDULE SWITCH

ldr r4, =0xE000ED04 //Load ICSR address

mov r5, #0 //mov zero for setting the sp to zero

ldr r6, [r4] //get ICSR value

str r5, [r7, #8] //set thread sp zero

orr r6, #1 << 26       //Set SystickInterrupt bit. in callee save so it will be
                      //here after calling bree so we can officially load it.

str r6, [r4] //officially Call Scheduler for the switch and delete

lop: //never end because we need to kill it with the SCHEDULER
b lop


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
 
  ldr r2, [r3] //load value of SysTick_MilliSec

  ldr r12, [r0, #4] //load flags variable value
   
  add r2, #1 //increment systick_MilliSec by 1 
  
// ONLY RUNS IF SYSTICK IS CALLED BY REACHING ZERO
  beq _NotCalled //if systick call bit is not equal to zero (not set) then we skip the below code. We
                 //do not need to increment the clock this time.
  
    str r2, [r3] //store new SysTick_MilliSec value
  

    and r3, r12, #1 << 30 //scheduler switch hold flag test. if set then we dont schedule for one round. so we also clear the bit
    
    and r2, r12, #~(1 << 30) //clear switch hold bit.
    str r2, [r0, #4]      //str new flag value.

    cbnz r3,  __EXIT
    
  _NotCalled:

  and r3, r12, #1 << 31 //scheduler hold flag test. if set then we dont schedule
  
  ldr r2, [r1, #0] //load next thread to see if same

  cbnz r3, __EXIT

  cmp r2, r1 //compare to see if addresses are the same

  beq __EXIT //if thread and next thread are equal we don't need to do anything

  // START INLINE KERNEL_Scheduler function 
    ldr r3, [r1, #8] //load current thread stack pointer address

    ldr r12, [r1, #4]          // load current->prev for possible delete  

    cbnz r3, _KNoDel //if sp is not zero then dont delete the thread and thread to run
   
      str r12, [r2, #4] //set current->next->prev=current->prev
      str r2, [r12, #0] //set current->prev->next=current->next
    
    b _KDeleted
    
    _KNoDel:

      mrs r12, psp //get current thread sp memory address

      vmrs r2, FPSCR          //get FPSCR

      stmdb r12!, {r4-r11}     // save the context of the rest of the registers 
      vstmdb r12!, {d0-d15}   //store floating point registers

      stmdb r12!, {r2, lr}    //store fpscr and current lr value for task

      str r12, [r1, #8]            // save the address of the stack pointer to the sp variable
  
    _KDeleted:  

    //branch to kernel switch 
    //assumes the new sp is in r0 
   
    ldr r2, [r1, #12] //get current thread flags for function call



    bl KERNEL_Switch  //loads new thread values of threads stack



    ldmia r0!, {r2, lr}  //load FPSCR and link register for task

    vldmia r0!, {d0-d15}  //load floating point registers

    vmsr FPSCR, r2 //store FPSCR

    ldmia r0!, {r4-r11} // load thread values
 
    msr psp, r0 //store new stack pointer address into process stack pointer

  // END INLINE 

  __EXIT:

bx lr








