#include "Uart.h"
#include "Gpio.h"
#include "RccConfig.h"

void UART2Config (void) {

    //1. Set up GPIO for USART2 on PA2 and PA3
    GPIO_InitTypeDef USART_Gpio[2] = {0};

    USART_Gpio[0].Pin = GPIO_PIN_2;
    USART_Gpio[0].Mode = GPIO_MODE_ALT;
    USART_Gpio[0].Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    USART_Gpio[0].Alt = GPIO_AF7_USART2;
    GPIO_Config(&USART_Gpio[0], GPIOA);

    USART_Gpio[1].Pin = GPIO_PIN_3;
    USART_Gpio[1].Mode = GPIO_MODE_ALT;
    USART_Gpio[1].Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    USART_Gpio[1].Alt = GPIO_AF7_USART2;
    GPIO_Config(&USART_Gpio[1], GPIOA);

    //2. Enable the UART CLOCK
    PeriphClkEnable(USART2_periph);
    
    //3. Enable the USART by writing the UE bit in USART_CR1 register to 1.
    USART2->CR1 = 0x0;               //reset all
    USART2->CR1 |= USART_CR1_UE;     //UE = 1, enable USART

    //4. Program the M bit in USART_CR1 to define the word length.
    USART2->CR1 &= ~(USART_CR1_M);  //M=0; 8 bit word length

    //5. Select the desired baud rate using the USART_BRR register.
    USART2->BRR = (7<<0) | (24<<4); //Baud rate of 115200, PCLK1 at 45Mhz

    //6. Enable the Transmitter/Receiver by setting the TE and RE bits in USART_CR1 register.
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