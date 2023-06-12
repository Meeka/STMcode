#ifndef __SCHEDULER_H
#define __SCHEDULER_H

#include <stddef.h>
#include "SysTick.h"
#include "Gpio.h"
#include "Uart.h"

#define NUM_OF_TASKS    5

//Task Control Blocks
typedef struct {
    void (*task_pointer)();  //function pointer to task
    void *arg_ptr;                  //argument pointer
    uint8_t state;                  //task state
    uint32_t delay;                 //task sleep delay
} TCB_TypeDef;

typedef enum {
    STATE_RUNNING,
    STATE_READY,
    STATE_WAITING,
    STATE_INACTIVE
} TCB_State_TypeDef;

void scheduler(void);
void start_task(uint8_t task_id);
void halt_task(void);
void sleep_task(uint32_t delay);
void scheduler_init(void);

void taskA();
void taskB();
void taskC();

#endif