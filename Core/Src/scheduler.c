#include "scheduler.h"

TCB_TypeDef TaskList[NUM_OF_TASKS];

uint8_t curr_task;

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
    //if at end of task list go to start
    if (TaskList[curr_task].task_pointer == NULL && curr_task != 0) {
        curr_task = 0;
        Delay(1);    //1ms delay for now...
    }
    //if no tasks, do nothing
    if (TaskList[curr_task].task_pointer == NULL && curr_task == 0) {
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
        Delay(1);    //1ms delay for now...
    }

    curr_task++;
    return;
}

void taskA() {
    GPIO_Toggle(GPIO_PIN_5, GPIOA);
    sleep_task(1000); //flash LED every 1s
}

void taskB() {
    UART_SendString("On\r\n", USART2);
    sleep_task(5000); //flash "On" every 5s
}

void taskC() {
    UART_SendString("Off\r\n", USART2);
    sleep_task(10000); //flash "Off" every 10s
}