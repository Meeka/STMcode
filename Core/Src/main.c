#include "main.h"

int main (void) {
    SysClockConfig();
    //TIM6Config(); -- No need, using SysTick now for delay function
    InitSysTick();
    GPIO_Config();

    while (1) {
        GPIOA->BSRR |= (1<<5);  //Set pin PA5
        Delay(1000);
        GPIOA->BSRR |= ((1<<5) <<16);   //Reset pin PA5
        Delay(1000);
    }

}
