#include "Timer.h"


void TIM6Config (void) {
    RCC_Periph_TypeDef  ClkEn;
    ClkEn.Bus = &RCC->APB1ENR;
    ClkEn.Offset = RCC_APB1ENR_TIM6EN;
    PeriphClkEnable(ClkEn);

    TIM6->PSC |= 90 - 1;    // 90Mhz/90 = 1Mhz ~~ 1uS delay
    TIM6->ARR = 0xFFFF;     //MAX ARR  value

    TIM6->CR1 |= (1<<0);            //Enable the counter
    while (!(TIM6->SR & (1<<0)));   //UIF: Update interrupt flag. This bit is set by hardware when the registers update
}

//ToDo: change so it doesn't spin CPU
void delay_us (uint16_t us) {
    TIM6->CNT = 0;
    while (TIM6->CNT < us);
}

//ToDo: change so it doesn't spin CPU
void delay_ms (uint16_t ms) {
    TIM6->CNT = 0;
    for (uint16_t i = 0; i < ms; i++) {
        delay_us (1000); //delay 1ms
    }
}
