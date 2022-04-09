#include "Uart.h"

void UART2Config (void) {

    //1. Enable the UART CLOCK
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    
    //2. Enable the USART by writing the UE bit in USART_CR1 register to 1.
    USART2->CR1 = 0x0;               //reset all
    USART2->CR1 |= USART_CR1_UE;     //UE = 1, enable USART

    //3. Program the M bit in USART_CR1 to define the word length.
    USART2->CR1 &= ~(USART_CR1_M);  //M=0; 8 bit word length

    //4. Select the desired baud rate using the USART_BRR register.
    USART2->BRR = (7<<0) | (24<<4); //Baud rate of 115200, PCLK1 at 45Mhz

    //5. Enable the Transmitter/Receiver by setting the TE and RE bits in USART_CR1 register.
    USART2->CR1 |= USART_CR1_RE;    //RE=1 Enable RX
    USART2->CR1 |= USART_CR1_TE;    //TE=1 Enable TX
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

uint8_t UART2_GetChar (void) {
    uint8_t temp;
    while (!(USART2->SR & USART_SR_RXNE)); //wait for RXNE bit to set
    temp = USART2->DR;                      // Read the data. This clears the RXNE bit.
    return temp;
}