#ifndef __UART_H
#define __UART_H

#include "stm32f446xx.h"
#include "gpio.h"
#include "rccConfig.h"
#include "core_cm4.h"
#include <stdbool.h>

#define RINGBUF_SIZE (128)
#define UNUSED(x) (void)(x); //Macro for unused parameter in overridden _write function.

typedef struct {
    int len;
    volatile char* buffer;
    volatile int head;
    volatile int tail;
} UART_Ringbuf_t;

static volatile UART_Ringbuf_t uartRingBuff;

enum UART_Pinout{
    UART_RX = 0,
    UART_TX = 1,
    UART_PINOUT
};

typedef enum {
    DATA_BITS_8 = 0,
    DATA_BITS_9 = 1
} UART_DataBits_t;

typedef enum {
    STOP_BIT_1 = 0,
    STOP_BIT_0_5 = 1,
    STOP_BIT_2 = 2,
    STOP_BIT_1_5 = 3
} UART_StopBits_t;

typedef enum {
    PARITY_DIS = 0,
    PARITY_EN = 1
} UART_Parity_t;

typedef struct {
    GPIO_InitTypeDef USART_Gpio[UART_PINOUT];
    RCC_Periph_TypeDef ClkEn;
    USART_TypeDef* RegOffset;
    UART_DataBits_t DataBits;
    UART_StopBits_t StopBits;
    UART_Parity_t Parity;
    IRQn_Type Interrupt;
} UART_Init_t;

//Enables UART
void uart_init(void);
void uart_config (UART_Init_t* USART_Settings);

//Send data to UART HW
void uart_send_char (uint8_t c, USART_TypeDef* USARTx);
void uart_send_string (char* string, USART_TypeDef* USARTx, int size);

//Used by USART2_IRQHandler to store keystrokes
bool uart_is_buffer_empty(void);
void uart_ring_buf_write (char x);
char uart_ring_buf_read (void);

//implements printf() over UART
int _write (int handle, char* data, int size);

#endif