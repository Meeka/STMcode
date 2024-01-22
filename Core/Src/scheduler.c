#include "scheduler.h"

TCB_TypeDef TaskList[NUM_OF_TASKS];

static uint8_t curr_task;

void scheduler_init(void) {
    uint8_t j = 0;

    TaskList[j].task_pointer = &taskA;
    TaskList[j].arg_ptr = NULL;
    TaskList[j].state = STATE_READY;
    TaskList[j].delay = 0;
    j++;

    TaskList[j].task_pointer = &taskB;
    TaskList[j].arg_ptr = NULL;
    TaskList[j].state = STATE_READY;
    TaskList[j].delay = 0;
    j++;

    TaskList[j].task_pointer = &taskC;
    TaskList[j].arg_ptr = NULL;
    TaskList[j].state = STATE_READY;
    TaskList[j].delay = 0;
    j++;

    TaskList[j].task_pointer = NULL;
}

void start_task(uint8_t task_id) {
    TaskList[task_id].state = STATE_READY;
}

void halt_task(void) {
    TaskList[curr_task].state = STATE_INACTIVE;
}

void sleep_task(uint32_t delay) {
    TaskList[curr_task].delay = delay;
    TaskList[curr_task].state = STATE_WAITING;
}

void scheduler(void) {
    for(curr_task = 0; curr_task < NUM_OF_TASKS; curr_task++) {
        //if no tasks, return
        if (TaskList[curr_task].task_pointer == NULL) {
            return;
        }

        //if task is delayed, decrement delay value
        //if delay value is 0, set task to ready state
        if (TaskList[curr_task].state == STATE_WAITING) {
            TaskList[curr_task].delay--;
            if (TaskList[curr_task].delay == 0) {
                TaskList[curr_task].state = STATE_READY;
            }
        }

        //if task is in ready state, run it
        if (TaskList[curr_task].state == STATE_READY) {
            TaskList[curr_task].task_pointer();
        }
    }
    
    return;
}

void taskA() {
    GPIO_Toggle(GPIO_PIN_5, GPIOA);
}

void taskB() {
    UART_SendString("5s\r\n", USART2);
    sleep_task(5); //flash "5s" every 5s
}

void taskC() {
    UART_SendString("10s\r\n", USART2);
    sleep_task(10); //flash "10s" every 10s
}