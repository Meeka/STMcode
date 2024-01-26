#ifndef __UART_H
#define __UART_H

#include "stm32f446xx.h"
#include "Gpio.h"
#include "RccConfig.h"
#include "core_cm4.h"

#define RINGBUF_SIZE (128)

//static volatile char ring_buffer_storeage[ RINGBUF_SIZE + 1];
//static volatile int newline = 0;
extern volatile char uart_rx_char; //remove once ring buffer implemented.

/*typedef struct {
    int len;
    volatile char* buffer;
    volatile int head;
    volatile int tail;
} UART_RingbufTypedef;*/

//ToDo: Find a better place for this...
/*UART_RingbufTypedef buffer = {
    .len = RINGBUF_SIZE,
    .buffer = ring_buffer_storeage,
    .head = 0,
    .tail = 0
};*/

enum UART_Pinout{
    UART_RX = 0,
    UART_TX = 1,
    UART_PINOUT
};

typedef enum {
    DATA_BITS_8 = 0,
    DATA_BITS_9 = 1
} UART_DataBitsTypedef;

typedef enum {
    STOP_BIT_1 = 0,
    STOP_BIT_0_5 = 1,
    STOP_BIT_2 = 2,
    STOP_BIT_1_5 = 3
} UART_StopBitsTypedef;

typedef enum {
    PARITY_DIS = 0,
    PARITY_EN = 1
} UART_ParityTypedef;

typedef struct {
    GPIO_InitTypeDef USART_Gpio[UART_PINOUT];
    RCC_Periph_TypeDef ClkEn;
    USART_TypeDef* RegOffset;
    UART_DataBitsTypedef DataBits;
    UART_StopBitsTypedef StopBits;
    UART_ParityTypedef Parity;
    IRQn_Type Interrupt;
} UART_InitTypeDef;

//void UART_RingBufWrite (UART_RingbufTypedef* ring_buffer, char* x);
//static inline char UART_RingBufRead (UART_RingbufTypedef* buffer);
void UART_Config (UART_InitTypeDef* USART_Settings);
void UART_SendChar (uint8_t c, USART_TypeDef* USARTx);
void UART_SendString (char* string, USART_TypeDef* USARTx);
uint8_t UART_GetChar (USART_TypeDef* USARTx);

void UART_Init(void);

#endif