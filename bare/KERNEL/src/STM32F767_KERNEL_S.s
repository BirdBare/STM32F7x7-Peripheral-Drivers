

.syntax unified

      .section ._ITCM.SCHEDULING

  .type  KERNEL_CreateTask, %function
  .global KERNEL_CreateTask
KERNEL_CreateTask:
 
push {r0-r8,lr} //push our registers and callee save registers onto stack
bl balloc
pop {r1-r4}

cbz r0, _NoSpace //if balloc did not return zero then space available 

add r12, r1, r0 //set start location of task sp

mov r1, r4 //mov void *args to "r0"

mov r7, r3 //move function address into pc spot 

mov r5, #0            //set r12 to zero for new function

mov r8, #0x1000000   //set PSR Reset value 

ldr r6, =KERNEL_ThreadReturn  //set link register to thread return


stmdb r12!, {r1-r8} // push vital peices to new stack 
stmdb r12!, {r1-r8} // push rest of dont care registers to fill stack 

ldr r6, =0xfffffffD  //Generic Exception return. Would be used by starting task

vstmdb r12!, {d0-d15} //push FPU registers to stack

stmdb r12!, {r5 - r6}
//sets link register from expection return to start this task
//Use thread mode, PSP, FPU value doesnt matter because task just started

str r12, [r0, #8] //store stack pointer in sp of new thread

_NoSpace:

pop {r4-r8, lr}
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

orr lr, #1 << 28       //Set Interrupt bit. in callee save so it will be
                      //here after calling bree so we can officially load it.

str lr, [r12] //officially Call Scheduler for the switch and delete

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

  .type  PendSV_Handler, %function
  .global PendSV_Handler
PendSV_Handler:
  

  ldr r1, =SCHEDULER //gets address of NSCHEDULER 

  ldr r0, [r1] //load thread address to check if only one thread
  
  ldr r12, [r1, #4] //load flags variable value
   
  and r3, r12, #1 << 31 //scheduler hold flag test. if set then we dont schedule
  
  ldr r2, [r0, #0] //load next thread to see if same

  cbnz r3, __EXIT

  cmp r2, r0 //compare to see if addresses are the same

  beq __EXIT //if thread and next thread are equal we don't need to do anything

  // START INLINE KERNEL_Scheduler function 
    ldr r3, [r0, #8] //load current thread stack pointer address

    cbz r3, _KDeleted //if sp is not zero then dont delete the thread and thread to run
   
      mrs r12, psp //get current thread sp memory address

      vmrs r2, FPSCR          //get FPSCR

      stmdb r12!, {r4-r11}     // save the context of the rest of the registers 
      vstmdb r12!, {d0-d15}   //store floating point registers

      stmdb r12!, {r2, lr}    //store fpscr and current lr value for task

      str r12, [r0, #8]            // save the address of the stack pointer to the sp variable
  
    _KDeleted:  

    //branch to kernel switch 
    //assumes the new sp is in r0 

    bl KERNEL_SwitchHandler  //loads new thread values of threads stack



    ldmia r0!, {r2, lr}  //load FPSCR and link register for task

    vldmia r0!, {d0-d15}  //load floating point registers

    vmsr FPSCR, r2 //store FPSCR

    ldmia r0!, {r4-r11} // load thread values
 
    msr psp, r0 //store new stack pointer address into process stack pointer

  // END INLINE 

  __EXIT:

bx lr








