#ifndef __SCHEDULER_H
#define __SCHEDULER_H

#include <stddef.h>
#include <stdlib.h>
#include "tasks.h"

typedef struct Node {
    Task_t* task;
    struct Node* next;
} Node_t;

void scheduler(Node_t** head);
void scheduler_init(Node_t** head);

void insert_task (Node_t** head, Task_t* task);
void remove_task (Node_t** head, Task_t* task);

#endif