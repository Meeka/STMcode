#include "main.h"

int main (void) {
    SysClockConfig();
    InitSysTick();
    GPIO_Init();
    UART_Init();
    scheduler_init();

    uint32_t loop_time = 0;

    while (1) {
        
        if(GetSysTick() - loop_time > 9) { //10ms loop
            loop_time = GetSysTick();
            scheduler();
            while (!UART_IsBufferEmpty()) {
                UART_SendChar(UART_RingBufRead(), USART2);
            }
        }
    }

}
