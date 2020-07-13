/** 
 * @file		nc_multitasking.h
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
 /* Define to prevent recursive inclusion -- */
#ifndef NC_MULTITASKING_H
#define NC_MULTITASKING_H 100

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif /* NC_MULTITASKING_H */

#include "stm32l1xx.h"

//uint32_t w;              /* main.c(3): error: unknown type name 'uint32_t'. #include "stm32l1xx.h" and declare extern or unsigned long int. */

/* Context Switch Stack Frame */
typedef struct{
    /* Pushed by software */
    uint32_t r4;           /* 16th item */
    uint32_t r5;           /* 15th item */
    uint32_t r6;           /* 14th item */
    uint32_t r7;           /* 13th item */
    uint32_t r8;           /* 12th item */
    uint32_t r9;           /* 11th item */
    uint32_t r10;          /* 10th item */
    uint32_t r11;          /*  9th item */ 
    /* Pushed by hardware */
    uint32_t r0;           /*  8th item */
    uint32_t r1;           /*  7th item */
    uint32_t r2;           /*  6th item */
    uint32_t r3;           /*  5th item */
    uint32_t r12;          /*  4th item */
    uint32_t lr;           /*  3rd item */
    uint32_t pc;           /*  2nd item */
    uint32_t psr;          /*  1st item */ 
} stack_frame_t;

/* Task table Structure */
typedef struct{
	  uint32_t sp;           /* Task stack pointer */
	  int flags;             /* Task status flags */
} task_table_t;

/* Allocate task table */
task_table_t task_table[3];

/* task_table[0]: stack of main task */
/* task_table[1]: stack of task 1 */
/* task_table[2]: stack of task 2 */

/* Keep track of which task is running */
int current_task = 0;

/* Initialization and Configuration functions *********************************/
void my_task_1(void *data);
void my_task_2(void *data);

int MAX_TASKS = 3;
int TASK_FLAG_EXEC = 1, TASK_FLAG_INIT = 1;

/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif /* NC_MULTITASKING_H */
