#include "main.h"

int main (void) {
    SysClockConfig();
    //TIM6Config(); -- No need, using SysTick now for delay function
    InitSysTick();
    GPIO_Config();
    UART2Config();

    while (1) {
        /*GPIOA->BSRR |= (1<<5);  //Set pin PA5
        UART2_SendString("On\r\n");
        Delay(1000);
        GPIOA->BSRR |= ((1<<5) <<16);   //Reset pin PA5
        UART2_SendString("Off\r\n");
        Delay(1000);*/
        uint8_t data = UART2_GetChar();
        UART2_SendChar(data);
    }

}
