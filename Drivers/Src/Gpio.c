#include "Gpio.h"


void GPIO_Config (void) {
    //1. Enable GPIO Clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    //2. Set the pin as OUTPUT
    GPIOA->MODER |= GPIO_MODER_MODE5_0; //pin PA5(bits 11:10) as output (01)

    //3. Configure OUTPUT MODE
    GPIOA->OTYPER &= ~(GPIO_OTYPER_OT5);   //bit 5 = 0 -->output push pull
    GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED5;  //Pin PA5 (bits 11:10) as fast speed (1:0)
    GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD5);   //Pin PA5 (bits 11:10) are 0:0 --> no pull up or pulldown
}
