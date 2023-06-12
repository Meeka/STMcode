#include "SysTick.h"

static volatile uint32_t TickCount;

void InitSysTick (void) {
    
    //1. Program reload value
    SysTick->LOAD = 0x2BF20 - 0x1;    //180Mhz / 1000 = ms timer
    NVIC_SetPriority(SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL);
    //2. Clear current value
    SysTick->VAL = 0;
    //3. Program control and status register
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |
                    SysTick_CTRL_TICKINT_Msk |
                    SysTick_CTRL_ENABLE_Msk;
    TickCount = 0;
}

void IncSysTick (void) {
    TickCount++;
}

uint32_t GetSysTick (void) {
    return TickCount;
}

//ToDo: change so it doesn't spin cpu
void Delay (uint32_t delay) {
    uint32_t tickstart = GetSysTick();
    
    while((GetSysTick() - tickstart) < delay);
}

void SuspendSysTick (void) {
    SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
}

void ResumeSysTick (void) {
    SysTick->CTRL |= ~SysTick_CTRL_TICKINT_Msk;
}