#include "main.h"

int main (void) {
    SysClockConfig();
    InitSysTick();
    GPIO_Init();
    UART_Init();

    while (1) {
        GPIO_Toggle(GPIO_PIN_5, GPIOA);
        UART_SendString("On\r\n", USART2);
        Delay(1000);
        GPIO_Toggle(GPIO_PIN_5, GPIOA);
        UART_SendString("Off\r\n", USART2);
        Delay(1000);
        //uint8_t data = UART_GetChar(USART2);
        //UART_SendChar(data, USART2);
    }

}
