#include "main.h"

int main (void) {
    SysClockConfig();
    //TIM6Config(); -- No need, using SysTick now for delay function
    InitSysTick();
    GPIO_Init();
    UART2Config();

    while (1) {
        GPIO_Toggle(GPIO_PIN_5, GPIOA);
        UART2_SendString("On\r\n");
        Delay(1000);
        GPIO_Toggle(GPIO_PIN_5, GPIOA);
        UART2_SendString("Off\r\n");
        Delay(1000);
        //uint8_t data = UART2_GetChar();
        //UART2_SendChar(data);
    }

}
