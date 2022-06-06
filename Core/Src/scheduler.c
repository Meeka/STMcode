#include "scheduler.h"

//Tracks number of tasks to run
void (*task_list[NUM_OF_TASKS]) (void *p);

uint8_t task_index;

void scheduler_init(void) {
    //init array of task pointers
    task_list[0] = &taskA;
    task_list[1] = &taskB;
    task_list[2] = &taskA;
    task_list[3] = &taskC;
    task_list[4] = NULL;

    //init task index for scheduler
    task_index = 0;
}

void start_task(void (*task_p)()) {
    task_p();
}

void scheduler(void) {
    //if at end of task list go to start
    if (task_list[task_index] == NULL && task_index != 0) {
        task_index = 0;
    }
    //if no tasks, do nothing
    if (task_list[task_index] == NULL && task_index == 0) {
        return;
    }
    start_task(task_list[task_index]);
    task_index++;   //round robin for now...
    return;
}

void taskA(void *p) {
    GPIO_Toggle(GPIO_PIN_5, GPIOA);
}

void taskB(void *p) {
    UART_SendString("On\r\n", USART2);
}

void taskC(void *p) {
    UART_SendString("Off\r\n", USART2);
}