#include "Uart.h"

void UART_Init (void) {
    UART_InitTypeDef UART_Terminal = {0};

    UART_Terminal.RegOffset = USART2;
    UART_Terminal.ClkEn.Bus = &RCC->APB1ENR;
    UART_Terminal.ClkEn.Offset = RCC_APB1ENR_USART2EN;
    UART_Terminal.USART_Gpio[0].Pin = GPIO_PIN_2;
    UART_Terminal.USART_Gpio[0].Mode = GPIO_MODE_ALT;
    UART_Terminal.USART_Gpio[0].Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    UART_Terminal.USART_Gpio[0].Alt = GPIO_AF7_USART2;
    UART_Terminal.USART_Gpio[0].ClkEn.Bus = &RCC->AHB1ENR;
    UART_Terminal.USART_Gpio[0].ClkEn.Offset = RCC_AHB1ENR_GPIOAEN;
    UART_Terminal.USART_Gpio[0].RegOffset = GPIOA;
    UART_Terminal.USART_Gpio[1].Pin = GPIO_PIN_3;
    UART_Terminal.USART_Gpio[1].Mode = GPIO_MODE_ALT;
    UART_Terminal.USART_Gpio[1].Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    UART_Terminal.USART_Gpio[1].Alt = GPIO_AF7_USART2;
    UART_Terminal.USART_Gpio[1].ClkEn.Bus = &RCC->AHB1ENR;
    UART_Terminal.USART_Gpio[1].ClkEn.Offset = RCC_AHB1ENR_GPIOAEN;
    UART_Terminal.USART_Gpio[1].RegOffset = GPIOA;

    UART_Config(&UART_Terminal);

}

void UART_Config (UART_InitTypeDef* USART_Settings) {

    //1. Set up GPIO for USART2 on PA2 and PA3
    GPIO_Config(&USART_Settings->USART_Gpio[0]);
    GPIO_Config(&USART_Settings->USART_Gpio[1]);

    //2. Enable the UART CLOCK
    PeriphClkEnable(USART_Settings->ClkEn);
    
    //3. Enable the USART by writing the UE bit in USART_CR1 register to 1.
    USART_Settings->RegOffset->CR1 = 0x0;               //reset all
    USART_Settings->RegOffset->CR1 |= USART_CR1_UE;     //UE = 1, enable USART

    //4. Program the M bit in USART_CR1 to define the word length.
    USART_Settings->RegOffset->CR1 &= ~(USART_CR1_M);  //M=0; 8 bit word length

    //5. Select the desired baud rate using the USART_BRR register.
    USART_Settings->RegOffset->BRR = (7<<0) | (24<<4); //Baud rate of 115200, PCLK1 at 45Mhz

    //6. Enable the Transmitter/Receiver by setting the TE and RE bits in USART_CR1 register.
    USART_Settings->RegOffset->CR1 |= USART_CR1_RE;    //RE=1 Enable RX
    USART_Settings->RegOffset->CR1 |= USART_CR1_TE;    //TE=1 Enable TX
}

void UART2_SendChar (uint8_t c) {
    USART2->DR = c;     //Load data into DR register
    while (!(USART2->SR & USART_SR_TC));    //wait for TC to set... This indicates that the data has been transmitted
}

void UART2_SendString (char* string) {
    while (*string != '\0') {
        UART2_SendChar(*string);
        string++;
    }
}

//ToDo: Improve to remove polling
uint8_t UART2_GetChar (void) {
    uint8_t temp;
    while (!(USART2->SR & USART_SR_RXNE)); //wait for RXNE bit to set
    temp = USART2->DR;                      // Read the data. This clears the RXNE bit.
    return temp;
}