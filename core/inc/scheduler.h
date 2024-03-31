#ifndef __SCHEDULER_H
#define __SCHEDULER_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "sysTick.h"
#include "gpio.h"
#include "uart.h"

//Task Control Blocks
typedef struct Task {
    void (*taskPointer)(struct Task*);  //function pointer to task
    uint8_t state;                  //task state
    uint32_t delay;                 //task sleep delay
} Task_t;

typedef struct Node {
    Task_t* task;
    struct Node* next;
} Node_t;

enum {
    STATE_READY,
    STATE_WAITING,
    STATE_INACTIVE
};

void scheduler(Node_t** head);
void start_task(Task_t** task);
void halt_task(Task_t** task);
void sleep_task(Task_t** task, uint32_t delay);
void scheduler_init(Node_t** head);

void insert_task (Node_t** head, Task_t* task);
void remove_task (Node_t** head, Task_t* task);

void taskA(Task_t* currentTask);
void taskB(Task_t* currentTask);
void taskC(Task_t* currentTask);

#endif