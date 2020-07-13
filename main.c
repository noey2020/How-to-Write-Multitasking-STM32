#include "stm32l1xx.h"
#include "nc_multitasking.h"
#include "nc_defines.h"

int counter_main  = 0;

int main(void){
    int k;
	  uint32_t var = 1;
	
	  tasks_init();
    new_task(my_task_1, (uint32_t)&var);   /* Initialize task 1 and one argument */
    new_task(my_task_2, (uint32_t)&var);   /* Initialize task 2 and one argument */ 

    SysTick_Init();                        /* SysTick timer for scheduler */
    NVIC_EnableIRQ(SysTick_IRQn);          /* Enable SysTick interrupt in NVIC */
  
    while(1){
        counter_main++;                    /* Increment global counter_main */
        for(k = 0; k < 1000; k++);         /* Delay */
    }
}
