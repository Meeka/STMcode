#ifndef __SYS_TICK_H
#define __SYS_TICK_H

#include "stm32f446xx.h"
#include "core_cm4.h"

static volatile uint32_t TickCount;

/***********STEPS***************
 * 1. Program reload value
 * 2. Clear current value
 * 3. Program control and status register
 * *****************************/
void InitSysTick (void);
void IncSysTick (void);
uint32_t GetSysTick (void);
void Delay (uint32_t delay);
void SuspendSysTick (void);
void ResumeSysTick (void);

#endif
