#ifndef __TIMER_H
#define __TIMER_H

#include "stm32f446xx.h"


    /****** STEPS **********
     * 1. Enable timer clock
     * 2. Set the prescaler and the ARR
     * 3. Enable the Timer, and wait for the update Flag to set
     * *********************/
void TIM6Config (void);

    /*********STEPS*************
     * 1. RESET the counter
     * 2. Wait for the counter to reach the entered value as each count will take 1us,
     *    the total waiting time will be the required delay
     * *************************/
void delay_us (uint16_t us);
void delay_ms (uint16_t ms);

#endif