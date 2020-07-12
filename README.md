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

The easy way is to use CMSIS-RTOS where we discuss threads:

#include <cmsis_os.h>

void main(void){

    osKernelInitialize();
    
    ...
    
    Init_Thread();
    
    osKernelStart();
    
}

We will do another tutorial for CMSIS-RTOS separately. But for the brute "from scratch way"
force, here's the pseudo multitasking C code to start with.

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

Remember that the building blocks of a typical "C" program are functions which we call to
perform a specific procedure  and which we then return to the calling function. In
contrast, the building block of Multitasking (or renamed RTOS) is a "thread" which is 
very similar to a "C" function but has some very fundamental differences, one of which,
is threads contain a while(1) infinite loop inside. Having threads with infinite loops
allows us to do continuing procedures within itself. Having a scheduler manage several
threads and give them the "threads" precious time slices means we should have a mechanism
to context switch between threads. Schedulers make good use of System timers to generate
periodic interrupts as time base and create those time slices servicing threads.

Illustration of "C" functions versus RTOS threads:

unsigned int my_task(void)

    int i;
    
    char ch;
    
    ...
    
    ...
    
    return (myUnsignedInt);
    
}

void my_task_1(void *data){

    int i;
    
    while(1){
    
        counter_task1++;
        
        for(i = 0; i < 1000; i++);
        
    }
    
}

Constructing our multitasking "C" program that allocates these slices of run-time to each
thread in a round-robin way, we achieve the illusion that all threads run in parallel.
In short, multitasking.

Threads makes us more object oriented as opposed to procedural. 

So how do we switch from one task to another? Hardware provides us with interrupts, NVIC,
timers and software provides us stack and data structures. We illustrated before how we
enter and exit interrupts and we will use that strategy which means we have to augment
it by writing the context switch between tasks. Before switching, we need to store the 
current stack pointer and the registers pushing them into the stack. In addition to what
the hardware push, we also have to push by software needed for the context switch.
Because of software, "we can skin a cat in many ways". We can use a dual stack and/or a
single stack. The proposed is:

typedef struct{

    // pushed by software
    
    uint32_t r4;
    
    uint32_t r3;
    
    ...
    
    ...
    
    // pushed by hardware
    
    uint32_t ro;
    
    uint32_t r1;
    
    ...
    
    ...
    
} stack_frame_t;

I included some posts for reference.

https://github.com/noey2020/How-to-Generate-Triangular-Wave-STM32-DAC

https://github.com/noey2020/How-to-Generate-Sine-Table-LUT

https://github.com/noey2020/How-to-Illustrate-Multiple-Exceptions-

https://github.com/noey2020/How-to-Blink-LED-using-Standard-Peripheral-Library

I appreciate comments. Shoot me an email at noel_s_cruz@yahoo.com!

Hire me!

Have fun and happy coding!
