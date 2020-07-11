# How-to-Write-Multitasking-STM32

How to Write Multitasking STM32   July 11, 2020

I appreciate comments. Shoot me an email at noel_s_cruz@yahoo.com!

Hire me!

We've covered a lot of ground about STM32. We started from the basics and discussed
standard peripherals. We studied the microcontroller core, vector tables, memory maps,
booting, assembly, typedef structs, stacks, conditional logic, arithmetic functions,
comparisons, interrupts, system timer, gpio, general-purpose timers, exceptions, multiple
interrupts, context switching, and many more.

Up to now, we didn't yearn to dwell on multitasking but we will today. Multitasking, as 
it's name implies delves into managing multiple tasks. We know cpus processes tasks
sequentially but we know we can do interrupts. What if, we write a round-robin scheduler
where the cpu allocates or time slices time appropriately to each task? Before, when an
interrupt occurs, if services the interrupt handler and finishes. This time, each task is
an infinite loop asking for more cpu attention. But wait, we only give a time slice to be
fair and accomodating to other tasks.

From our previous tutorials, we can make use of the System timer, interrupt, context
switch by pushing onto stack and returning from the link register. Instead, we place the 
address of the next task instead of the previous task that was interrupted. And we do a 
round-robin scheduler that we mentioned earlier. We might have to hurdle supervisor calls
because they depart from the usual context switching which is written in microcode. I 
guess we bypass those by privileged instructions to accomplish multitasking.

But here's the pseudo multitasking to start with.

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


I included some posts for reference.

https://github.com/noey2020/How-to-Generate-Triangular-Wave-STM32-DAC

https://github.com/noey2020/How-to-Generate-Sine-Table-LUT

https://github.com/noey2020/How-to-Illustrate-Multiple-Exceptions-

https://github.com/noey2020/How-to-Blink-LED-using-Standard-Peripheral-Library

I appreciate comments. Shoot me an email at noel_s_cruz@yahoo.com!

Hire me!

Have fun and happy coding!
