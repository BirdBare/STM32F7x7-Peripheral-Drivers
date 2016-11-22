

.syntax unified

      .section ._ITCM.SCHEDULING

  .type  KERNEL_CreateTask, %function
  .global KERNEL_CreateTask
KERNEL_CreateTask:
 
push {r0-r4,lr} //push our registers and callee save registers onto stack
bl balloc
pop {r1-r4}

cbz r0, _NoSpace //if balloc did not return zero then space available 

mov r12, r4 //mov void *args to "r0"

add lr, r1, r0 //set start location of task sp

mov r1, #0            //set r12 to zero for new function

ldr r2, =KERNEL_ThreadReturn  //set link register to thread return

//r3 set by pop

mov r4, #0x1000000   //set PSR Reset value 

stmdb lr!, {r1-r4} // push vital peices to new stack 

mov r1, r12

stmdb lr!, {r1-r4} // push vital peices to new stack 
stmdb lr!, {r1-r8} // push rest of dont care registers to fill stack 

ldr r4, =0xfffffffD  //Generic Exception return. Would be used by starting task

vstmdb lr!, {d0-d15} //push FPU registers to stack

stmdb lr!, {r3 - r4}
//sets link register from expection return to start this task
//Use thread mode, PSP, FPU value doesnt matter because task just started

str lr, [r0, #8] //store stack pointer in sp of new thread

_NoSpace:

pop {r4, lr}
    bx lr

  .type  KERNEL_ThreadReturn, %function
KERNEL_ThreadReturn:

//  NONE OF THE REGISTERS MATTER BECAUSE WE WILL DELETE THREAD AT SCHEDULE SWITCH

ldr r12, =0xE000ED04 //Load ICSR address

ldr r0, =SCHEDULER

mov r2, #0 //mov zero for setting the sp to zero

ldr r8, [r0, #4] //load scheduler flags

ldr r1, [r0] //load current thread address

and r8, #~(0b1 << 31) //disable hold
orr r8, #(0b1 << 30) //set switch hold

ldr lr, [r12] //get ICSR value

str r8, [r0, #4] //store scheduler flags

str r2, [r1, #8] //set thread sp zero

orr lr, #1 << 28       //Set Interrupt bit.

str lr, [r12] //officially Call Scheduler for the switch and delete

1: //never end because we need to kill it with the SCHEDULER
b 1b


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

  .type  PendSV_Handler, %function
  .global PendSV_Handler
PendSV_Handler:
  
  ldr r1, =SCHEDULER //gets address of NSCHEDULER 

  ldr r0, [r1] //load thread address to check if only one thread
  
  ldr r12, [r1, #4] //load flags variable value

  ldr r2, [r0, #0] //load next thread to see if same
   
  ands r3, r12, #1 << 31 //scheduler hold flag. if set then dont schedule
  
  bne __EXIT

  cmp r2, r0 //compare to see if addresses are the same

  ldr r3, [r0, #8] //load current thread stack pointer address

  beq __EXIT //if thread and next thread are equal we don't need to do anything

    cbz r3, _KDeleted //if sp is zero then dont save the thread

      mrs r12, psp //get current thread sp memory address

      vmrs r2, FPSCR          //get FPSCR

      stmdb r12!, {r4-r11}     // save the context of the rest of the registers 
      vstmdb r12!, {d0-d15}   //store floating point registers

      stmdb r12!, {r2, lr}    //store fpscr and current lr value for task

      str r12, [r0, #8]            // save the address of the stack pointer to the sp variable
  
    _KDeleted:  

    //branch to kernel switch 
    //assumes the new sp is in r0 

//    bl KERNEL_SwitchHandler  //loads new thread values of threads stack

/* ********** SWITCH HANDLER ************** */

  ldr r4, =SCHEDULER

  1:
//DELETE
    ldr r1, [r0, #8] //load sp address
    
    ldr r8, =SysTick_Ticks

    cmp r1, #0

    it eq
      bleq KERNEL_DeleteHandler

    ldr r0, [r0] //current->next

  beq 1b
//END DELETE

//TIMEOUT
  ldr r5, [r0, #16] //get timeoutcount

  ldr r9, =SysTick_TicksPerMilli
  
  ldr r6, [r0, #20] //get temp1

  ldr r7, [r0, #24] //get temp2

  ldr r8, [r8] //get SysTick_Ticks value

  ldr r9, [r9] //get TIcksPerMilli Value

  cbz r5, 2f //if timeoutcount is 0 then skip this

    ldr r10, [r0, #12] //load flags

    ldr r1, [r6] //load flag check register value

    ubfx r2, r10,  #4, #1 //move bit to zero position

    tst r1, r7 //*temp1 & temp2
   
    ite ne
    movne r1, #1
    moveq r1, #0

    cmp r1, r2

    bne 1b

    sub r5, r8, r5 //SysTick_Ticks - timeoutcount(ref)

    and r1, r10, #0xf //0b1111 //get timeoutmax bits

    mov r2, #50

    lsl r1, r2, r1 //get timeoutmax 

    cmp r5, r1

    it hi
      blhi KERNEL_TimeoutHandler //branch if timeout(r5) is greater than timeoutmax(r1)
    
  2: 

//END TIMEOUT


//DELAY
  udiv r8, r9 //get SYsTick_MilliSec

  sub r8, r6 //get SysTick - ref

  cmp r8, r7 

  blo 1b  //if SysTick_MilliSec is greater than Milli

//END DELAY


    str r0, [r4] //store new current thread

    ldr r0, [r0, #8] //load current thread stack pointer


/* ********** SWITCH HANDLER ************** */

    ldmia r0!, {r2, lr}  //load FPSCR and link register for task

    vldmia r0!, {d0-d15}  //load floating point registers

    vmsr FPSCR, r2 //store FPSCR

    ldmia r0!, {r4-r11} // load thread values
 
    msr psp, r0 //store new stack pointer address into process stack pointer

  __EXIT:

bx lr






