/** 
 * @file		nc_multitasking.c
 * @author  Noel Cruz   
 * @email   noel_s_cruz@yahoo.com
 * @github  https://github.com/noey2020
 * @version v1.0
 * @ide     Keil uVision
 * @license GNU GPL v3
 * @brief   Multitasking for STM32L1xx devices
 *
@verbatim
----------------------------------------------------------------------
Copyright (C) 2020, Noel Cruz

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge,
publish, distribute, sublicense, and/or sell copies of the Software, 
and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
----------------------------------------------------------------------
@endverbatim
 */
	
#include "nc_multitasking.h"


int counter_task1 = 0;
int counter_task2 = 0;

void new_task(void (* func)(void *), uint32_t args){
	  int i;
	  stack_frame_t * frame;
	
	  for(i = 1; i < MAX_TASKS; i++){
		    if(task_table[i].flags == 0){
				    frame = (stack_frame_t *)(task_table[i].sp - sizeof(stack_frame_t));
            frame->r4   = 0;
            frame->r5   = 0;					
            frame->r6   = 0;
            frame->r7   = 0;					
            frame->r8   = 0;
            frame->r9   = 0;					
            frame->r10  = 0;
            frame->r11  = 0;						
            frame->r0   = (uint32_t)args;
            frame->r1   = 0;					
            frame->r2   = 0;
            frame->r3   = 0;					
            frame->r12  = 0;
            frame->pc   = ((uint32_t)func);
					  frame->lr   = 0;					
            frame->psr  = 0x21000000;    /* Set default PSR value */
            task_table[i].sp = (uint32_t) frame;
            task_table[i].flags = TASK_FLAG_EXEC | TASK_FLAG_INIT;
					  set_PSP(task_table[i].sp);
					  break;
				}
		}
}

__asm uint32_t get_MSP(void){     /* Read main stack pointer */
	  MRS r0, msp    ; copy msp to r0
	  BX  lr         ; r0 holds result returned					  
}

__asm void set_MSP(void){         /* Write main stack pointer */
	  MSR msp, r0    ; copy r0 to msp 
	  BX  lr         ; r0 holds result returned					  
}

__asm uint32_t get_PSP(void){     /* Read process stack pointer */
	  MRS r0, psp    ; copy psp to r0
	  BX  lr         ; r0 holds result returned					  
}

__asm void set_PSP(void){         /* Write process stack pointer */
	  MSR r0, psp    ; copy r0 to psp 
	  BX  lr         ; r0 holds result returned					  
}

void my_task_1(void *data){
    int i;
    while(1){
        counter_task1++;
        for(i = 0; i < 1000; i++);
    }
}

void my_task_2(void *data){
    int j;
    while(1){
        counter_task2++;
        for(j = 0; j < 1000; j++);
    }
}

__asm void SysTick_Handler(void){
    IMPORT get_next_task
	  IMPORT update_sp
	
	  CPSID  I     ; SET PRIMASK to disable IRQ
	
	  TST    lr, #0x04       ; LR = 0xFFFFFFF9 -> MSP; LR = 0xFFFFFFFD -> PSP
	  MRSEQ  r0, msp         ; Get MSP if LR = 0xFFFFFFF9
	  MRSNE  r0, psp         ; Get PSP if LR = 0xFFFFFFFD
	  STMDB  r0!, {r4-r11}   ; Save partial context (r4-r11) onto stack
		MSREQ  msp, r0         ; Update MSP if LR = 0xFFFFFFF9
		MSRNE  psp, r0         ; Update PSP if LR = 0xFFFFFFFD

	  BL     update_sp
	  BL     get_next_task   ; r0 = 0xFFFFFFF9 or 0xFFFFFFFD
		MOV    lr, r0          ; Set the link register
	
	  ; load context of new task
	  TST    lr, #0x04       ; LR = 0xFFFFFFF9 -> MSP; LR = 0xFFFFFFFD -> PSP
	  MRSEQ  r0, msp         ; Get MSP if LR = 0xFFFFFFF9
	  MRSNE  r0, psp         ; Get PSP if LR = 0xFFFFFFFD
	  STMDB  r0!, {r4-r11}   ; Save partial context (r4-r11) onto stack
		MSREQ  msp, r0         ; Update MSP if LR = 0xFFFFFFF9
		MSRNE  psp, r0         ; Update PSP if LR = 0xFFFFFFFD
	
	  CPSIE  I     ; Clear PRIMASK to enable IRQ
	  BX     lr    ; Trigger unstacking (r0-r3, r12, LR, PSR, PC)
}	

/* Update the stack table */
void update_sp(void){
    /* Save current task's stack pointer */
	  if(current_task == 0){
		    task_table[current_task].sp = get_MSP();
		} else if ((task_table[current_task].flags & TASK_FLAG_INIT) == 0){
			  task_table[current_task].sp = get_PSP();
		}
}

/* Identify the next task to be executed */
uint32_t get_next_task(void){
	  current_task++;
	
    if(current_task == MAX_TASKS){
			  current_task = 0;
		    set_MSP(task_table[current_task].sp);
			  return 0xFFFFFFF9;  /* Exit interrupt using main stack */
		} else if (task_table[current_task].flags & TASK_FLAG_EXEC){
			  set_PSP(task_table[current_task].sp);
			  if(task_table[current_task].flags & TASK_FLAG_INIT)
				    task_table[current_task].flags &= ~TASK_FLAG_INIT;
				return 0xFFFFFFFD;  /* Exit interrupt using process stack */
		}
}

//#endif /* NC_MULTITASKING_C */
/**
  * @}
  */
/************************ Copyright (C) 2020, Noel Cruz *****END OF FILE****/