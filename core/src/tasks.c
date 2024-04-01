#include "tasks.h"

void led_blink(uint8_t* taskState, uint32_t* taskDelay) {
    GPIO_Toggle(GPIO_PIN_5, GPIOA);
    sleep_task(taskDelay, taskState, 100); //flash every 1s
}

void timer_5s(uint8_t* taskState, uint32_t* taskDelay) {
    sleep_task(taskDelay, taskState, 500); //flash "5s" every 5s
    printf("5s\r\n");
}

void write_uart(uint8_t* taskState, uint32_t* taskDelay) {
    UNUSED(taskState);
    UNUSED(taskDelay);

    while (!UART_IsBufferEmpty()) {
        UART_SendChar(UART_RingBufRead(), USART2);
    }
}

void start_task(uint8_t* taskState) {
    *taskState = STATE_READY;
}

void halt_task(uint8_t* taskState) {
    *taskState = STATE_INACTIVE;
}

void sleep_task(uint32_t* taskDelay, uint8_t* taskState, uint32_t delay) {
    *taskDelay = delay;
    *taskState = STATE_WAITING;
}