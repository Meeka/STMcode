#ifndef __TASKS_H
#define __TASKS_H

#include <stdint.h>
#include <stdio.h>
#include "gpio.h"

typedef struct Task {
    void (*taskPointer)(uint8_t*, uint32_t*);
    uint8_t state;
    uint32_t delay;
} Task_t;

enum {
    STATE_READY,
    STATE_WAITING,
    STATE_INACTIVE
};

void led_blink(uint8_t* taskState, uint32_t* taskDelay);
void timer_5s(uint8_t* taskState, uint32_t* taskDelay);
void timer_10s(uint8_t* taskState, uint32_t* taskDelay);
void start_task(uint8_t* taskState);
void halt_task(uint8_t* taskState);
void sleep_task(uint32_t* taskDelay, uint8_t* taskState, uint32_t delay);

#endif