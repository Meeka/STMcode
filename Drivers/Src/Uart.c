#include "Uart.h"

void UART_Init (void) {
    UART_InitTypeDef UART_Terminal = {
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

    UART_Config(&UART_Terminal);

}

void UART_Config (UART_InitTypeDef* USART_Settings) {

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

void UART_SendChar (uint8_t c, USART_TypeDef* USARTx) {
    USARTx->DR = c;     //Load data into DR register
    while (!(USARTx->SR & USART_SR_TC));    //wait for TC to set... This indicates that the data has been transmitted
}

void UART_SendString (char* string, USART_TypeDef* USARTx) {
    while (*string != '\0') {
        UART_SendChar(*string, USARTx);
        string++;
    }
}

static volatile UART_RingbufTypedef UART_read_buffer = {
    .len = RINGBUF_SIZE,
    .buffer = ring_buffer_storeage,
    .head = 0,
    .tail = 0
};

void UART_RingBufWrite (char x){
    UART_read_buffer.buffer[UART_read_buffer.tail] = x;
    if((UART_read_buffer.tail + 1) >= UART_read_buffer.len)
        UART_read_buffer.tail = 0;
    else 
        UART_read_buffer.tail++;
}

char UART_RingBufRead (void){
    if (UART_read_buffer.head == UART_read_buffer.tail)
        return 0;
    char read = UART_read_buffer.buffer[UART_read_buffer.head];
    UART_read_buffer.head = (UART_read_buffer.head < (UART_read_buffer.len - 1)) ? (UART_read_buffer.head + 1) : 0;
    return read;
}

void USART2_IRQHandler (void) {
    if (USART2->SR & USART_SR_RXNE_Msk) {
        char c = USART2->DR;
        UART_RingBufWrite(c);
        if( c == '\r')
            UART_RingBufWrite('\n');
    }
}

bool UART_IsBufferEmpty(void) {
    return (UART_read_buffer.head == UART_read_buffer.tail);
}