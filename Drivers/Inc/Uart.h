#ifndef __UART_H
#define __UART_H

#include "stm32f446xx.h"
#include "Gpio.h"
#include "RccConfig.h"

typedef struct {
    GPIO_InitTypeDef USART_Gpio[2];
    RCC_Periph_TypeDef ClkEn;
    USART_TypeDef* RegOffset;
} UART_InitTypeDef;


/*********STEPS***********
 * 1. Enable the UART CLOCK
 * 2. Enable the USART by writing the UE bit in USART_CR1 register to 1.
 * 3. Program the M bit in USART_CR1 to define the word length.
 * 4. Select the desired baud rate using the USART_BRR register.
 * 5. Enable the Transmitter/Receiver by setting the TE and RE bits in USART_CR1 register.
 * ***********************/
void UART_Config (UART_InitTypeDef* USART_Settings);

/**************STEPS**************
 * 1. Write the data to send in the USART_DR register (this clears the TXE bit). Repeat this
 *    for each data to be transmitted in case of single buffer.
 * 2. After writing the last data into the USART_DR reigster, wait until TC=1. This indicates
 *    That the transmission of t he last frame is complete. This is required for instance when 
 *    the USART is disabled or enters the Halt mode to avoid corrupting the last transmission.
 * *******************************/
void UART2_SendChar (uint8_t c);
void UART2_SendString (char* string);

/***************STEPS**************
 * 1. Wait for the RXNE bit to set. It indicates that the data has been received and can be read.
 * 2. Read the data from USART_DR register. This also clears the RXNE bit
 * ********************************/
uint8_t UART2_GetChar (void);

/************STEPS************
 * 1. Setup terminal on USART2
 * ***************************/
void UART_Init(void);

#endif