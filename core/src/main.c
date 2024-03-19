#include "main.h"

int main (void) {
    SysClockConfig();
    InitSysTick();
    GPIO_Init();
    UART_Init();

    Node_t* taskHead = NULL;
    
    scheduler_init(&taskHead);

    uint32_t loopTime = 0;

    while (1) {
        
        if(GetSysTick() - loopTime > 9) { //10ms loop
            loopTime = GetSysTick();
            scheduler(&taskHead);
            while (!UART_IsBufferEmpty()) {
                UART_SendChar(UART_RingBufRead(), USART2);
            }
        }
    }

}
