#include "main.h"

int main (void) {
    SysClockConfig();
    InitSysTick();
    GPIO_Init();
    UART_Init();
    scheduler_init();

    uint32_t loop_time = 0;

    while (1) {
        
        if(GetSysTick() - loop_time > 999) { //1s loop
            loop_time = GetSysTick();
            scheduler();
        }
    }

}
