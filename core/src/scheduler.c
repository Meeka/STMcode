#include "scheduler.h"

void scheduler_init(Node_t** head) {
    
    Task_t* ledBlink = (Task_t*)malloc(sizeof(Task_t));
    Task_t* timer_5s = (Task_t*)malloc(sizeof(Task_t));
    Task_t* timer_10s = (Task_t*)malloc(sizeof(Task_t));

    ledBlink->taskPointer = &taskA;
    ledBlink->state = STATE_READY;
    ledBlink->delay = 0;

    timer_5s->taskPointer = &taskB;
    timer_5s->state = STATE_READY;
    timer_5s->delay = 0;

    timer_10s->taskPointer = &taskC;
    timer_10s->state = STATE_READY;
    timer_10s->delay = 0;

    insert_task(head, ledBlink);
    insert_task(head, timer_5s);
    insert_task(head, timer_10s);
}

void start_task(Task_t** task) {
    (*task)->state = STATE_READY;
}

void halt_task(Task_t** task) {
    (*task)->state = STATE_INACTIVE;
}

void sleep_task(Task_t** task, uint32_t delay) {
    (*task)->delay = delay;
    (*task)->state = STATE_WAITING;
}

void scheduler(Node_t** head) {
    Node_t* current = *head;
    
    while(current != NULL) {

        //if task is delayed, decrement delay value
        if(current->task->state == STATE_WAITING) {
            current->task->delay--;

            if (current->task->delay == 0) {
                current->task->state = STATE_READY;
            }
        }

        //if task is in ready state, run it
        if(current->task->state == STATE_READY) {
            current->task->taskPointer(current->task);
        }

        current = current->next;
    }

    return;
}

void taskA(Task_t* currentTask) {
    GPIO_Toggle(GPIO_PIN_5, GPIOA);
    sleep_task(&currentTask, 100); //flash every 1s
}

void taskB(Task_t* currentTask) {
    sleep_task(&currentTask, 500); //flash "5s" every 5s
    printf("5s\r\n");
}

void taskC(Task_t* currentTask) {
    sleep_task(&currentTask, 1000); //flash "10s" every 10s
    printf("10s\r\n");
}

void insert_task (Node_t** head, Task_t* task) {

    Node_t* new_node = (Node_t*)malloc(sizeof(Node_t));
    if(new_node == NULL)
        while(1);

    new_node->next = *head;
    new_node->task = task;

    *head =  new_node;
}

void remove_task (Node_t** head, Task_t* task) {
    if (head == NULL) {
        printf("Task list empty\n");
        return;
    }

    //handles case where the task to remove is at the head
    if ((*head)->task == task) {
        Node_t* temp = *head;
        *head = (*head)->next;
        free(temp->task);
        free(temp);
        return;
    }

    Node_t* temp = *head;
    Node_t* prev = NULL;

    while (temp != NULL && temp->task != task) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Task not found\n");
        return;
    }

    prev->next = temp->next;
    free(temp->task);
    free(temp);
}