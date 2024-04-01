#include "scheduler.h"

void scheduler_init(Node_t** head) {
    
    Task_t* ledBlink = (Task_t*)malloc(sizeof(Task_t));
    //Task_t* timer5s = (Task_t*)malloc(sizeof(Task_t));
    Task_t* writeUart = (Task_t*)malloc(sizeof(Task_t));

    ledBlink->taskPointer = led_blink;
    ledBlink->state = STATE_READY;
    ledBlink->delay = 0;

    //timer5s->taskPointer = timer_5s;
    //timer5s->state = STATE_READY;
    //timer5s->delay = 0;

    writeUart->taskPointer = write_uart;
    writeUart->state = STATE_READY;
    writeUart->delay = 0;

    insert_task(head, ledBlink);
    //insert_task(head, timer5s);
    insert_task(head, writeUart);
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
            current->task->taskPointer(&(current->task->state), &(current->task->delay));
        }

        current = current->next;
    }

    return;
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