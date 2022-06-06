#ifndef __SCHEDULER_H
#define __SCHEDULER_H

#include <stddef.h>
#include "Gpio.h"
#include "Uart.h"

#define NUM_OF_TASKS    5

//Tasks
void taskA(void *p);
void taskB(void *p);
void taskC(void *p);
void taskD(void *p);

void scheduler(void);
void start_task(void (*task_p)());
void scheduler_init(void);


#endif