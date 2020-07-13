#include "stm32l1xx.h"
#include "nc_multitasking.h"

void my_task_1(void *data);
void my_task_2(void *data);

//extern uint32_t w;              /* main.c(3): error: unknown type name 'uint32_t'. #include "stm32l1xx.h" and declare extern or unsigned long int. */

int counter_main  = 0;
int counter_task1 = 0;
int counter_task2 = 0;

int main(void){
    int k;
    
    /* .... more initialization... cpu, stack, interrupts, tasks init ...*/
    
    while(1){
        counter_main++;
        for(k = 0; k < 1000; k++);
    }
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
