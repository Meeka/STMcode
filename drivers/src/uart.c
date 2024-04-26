#include "uart.h"

void uart_init (void) {
    UART_Init_t UART_Terminal = {
        .RegOffset = USART2,
        .ClkEn.Bus = &RCC->APB1ENR,
        .ClkEn.Offset = RCC_APB1ENR_USART2EN,
        .USART_Gpio[UART_RX] = {
            .pin = GPIO_PIN_2,
            .mode = GPIO_MODE_ALT,
            .speed = GPIO_SPEED_FREQ_VERY_HIGH,
            .alt = GPIO_AF7_USART2,
            .clkEn.Bus = &RCC->AHB1ENR,
            .clkEn.Offset = RCC_AHB1ENR_GPIOAEN,
            .regOffset = GPIOA
        },
        .USART_Gpio[UART_TX] = {
            .pin = GPIO_PIN_3,
            .mode = GPIO_MODE_ALT,
            .speed = GPIO_SPEED_FREQ_VERY_HIGH,
            .alt = GPIO_AF7_USART2,
            .clkEn.Bus = &RCC->AHB1ENR,
            .clkEn.Offset = RCC_AHB1ENR_GPIOAEN,
            .regOffset = GPIOA
        },
        .DataBits = DATA_BITS_8,
        .StopBits = STOP_BIT_1,
        .Parity = PARITY_DIS,
        .Interrupt = USART2_IRQn
        
    };

    uart_config(&UART_Terminal);

    //create ring buffer to capture keystrokes from ISR
    static volatile char ringBuffer[RINGBUF_SIZE + 1];
    uartRingBuff.len = RINGBUF_SIZE;
    uartRingBuff.buffer = ringBuffer;
    uartRingBuff.head = 0;
    uartRingBuff.tail = 0;
}

void uart_config (UART_Init_t* USART_Settings) {

    //GPIO programming
    GPIO_Config(&USART_Settings->USART_Gpio[UART_RX]);
    GPIO_Config(&USART_Settings->USART_Gpio[UART_TX]);

    //UART Clock
    PeriphClkEnable(USART_Settings->ClkEn);

    //Enable interrupt
    NVIC_SetPriorityGrouping(0);
    uint32_t uart_priority_encoding = NVIC_EncodePriority(0, 1, 0);
    NVIC_SetPriority (USART_Settings->Interrupt, uart_priority_encoding);
    NVIC_EnableIRQ (USART_Settings->Interrupt);

    //Additional USART settings
    USART_Settings->RegOffset->CR1 &= ~(USART_CR1_M_Msk);
    USART_Settings->RegOffset->CR2 &= ~(USART_CR2_STOP_Msk & USART_CR2_CPOL_Msk);
    USART_Settings->RegOffset->CR1 |= USART_Settings->DataBits;
    USART_Settings->RegOffset->CR2 |= USART_Settings->StopBits;
    USART_Settings->RegOffset->CR2 |= USART_Settings->Parity;
    USART_Settings->RegOffset->BRR = (7<<0) | (24<<4);

    //Enable USART
    USART_Settings->RegOffset->CR1 |= (USART_CR1_RE | USART_CR1_TE | USART_CR1_RXNEIE | USART_CR1_UE);    //RE=1 Enable RX

}

void uart_send_char (uint8_t c, USART_TypeDef* USARTx) {
    USARTx->DR = c;     //Load data into DR register
    while (!(USARTx->SR & USART_SR_TC));    //wait for TC to set... This indicates that the data has been transmitted
}

void uart_send_string (char* string, USART_TypeDef* USARTx, int size) {
    for (int i = 0; i < size; i++) {
        uart_send_char(*string, USARTx);
        string++;
    }
}

void uart_ring_buf_write (char x){
    uartRingBuff.buffer[uartRingBuff.tail] = x;
    if((uartRingBuff.tail + 1) >= uartRingBuff.len)
        uartRingBuff.tail = 0;
    else 
        uartRingBuff.tail++;
}

char uart_ring_buf_read (void){
    if (uartRingBuff.head == uartRingBuff.tail)
        return 0;
    char read = uartRingBuff.buffer[uartRingBuff.head];
    uartRingBuff.head = (uartRingBuff.head < (uartRingBuff.len - 1)) ? (uartRingBuff.head + 1) : 0;
    return read;
}

void USART2_IRQHandler (void) {
    if (USART2->SR & USART_SR_RXNE_Msk) {
        char c = USART2->DR;
        if (c == '\r')
            c = '\n';
        uart_ring_buf_write(c);
        if (c == '\b') {
            uart_ring_buf_write(' ');
            uart_ring_buf_write('\b');
        }
    }
}

bool uart_is_buffer_empty(void) {
    return (uartRingBuff.head == uartRingBuff.tail);
}

//Implements printf()
int _write (int handle, char* data, int size) {
    UNUSED(handle);

    uart_send_string(data, USART2, size);
    return size;
}