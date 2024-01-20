#include "Gpio.h"

void GPIO_Enable (GPIO_InitTypeDef* GPIO_Settings) {
    //Enable clock
    PeriphClkEnable(GPIO_Settings->clkEn);
    //Set mode
    GPIO_Settings->regOffset->MODER &=  ~(GPIO_MODER_MODER0_Msk << (GPIO_Settings->pin * 2));
    GPIO_Settings->regOffset->MODER |= GPIO_Settings->mode << (GPIO_Settings->pin * 2);
    //Configure pu/pd/floating
    GPIO_Settings->regOffset->PUPDR &= ~(GPIO_PUPDR_PUPD10_Msk << (GPIO_Settings->pin * 2));
    
    if(GPIO_Settings->mode != GPIO_MODE_ANALOG) {
        GPIO_Settings->regOffset->PUPDR |= GPIO_Settings->pull << (GPIO_Settings->pin * 2);
    }
}

void GPIO_setup_output_af (GPIO_InitTypeDef* GPIO_Settings) {
    //Set output mode
    GPIO_Settings->regOffset->OTYPER &= ~(GPIO_OTYPER_OT0_Msk << GPIO_Settings->pin); 
    GPIO_Settings->regOffset->OTYPER |= GPIO_Settings->oType << GPIO_Settings->pin;
    //Set speed
    GPIO_Settings->regOffset->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED0_Msk << (GPIO_Settings->pin * 2));
    GPIO_Settings->regOffset->OSPEEDR |= GPIO_Settings->speed << (GPIO_Settings->pin * 2);

    if(GPIO_Settings->mode == GPIO_MODE_ALT) {
        if(GPIO_Settings->pin > 7)
            //Use GPIO Alternate Function High register (For pins 15:8)
            GPIO_Settings->regOffset->AFR[1] |= GPIO_Settings->alt << ((GPIO_Settings->pin >> 7) * 4);
        else
            //Use GPIO Alternate Function Low register (For pins 7:0)
            GPIO_Settings->regOffset->AFR[0] |= GPIO_Settings->alt << (GPIO_Settings->pin * 4);
    }
}

void GPIO_Config(GPIO_InitTypeDef* GPIO_Settings) {
    GPIO_Enable(GPIO_Settings);
    if(GPIO_Settings->mode == GPIO_MODE_OUTPUT || GPIO_Settings->mode == GPIO_MODE_ALT)
        GPIO_setup_output_af(GPIO_Settings);
}

void GPIO_Init (void) {

    //1. Setup User LED on PA5
    GPIO_InitTypeDef LED_Gpio = {
        .pin = GPIO_PIN_5,
        .mode = GPIO_MODE_OUTPUT,
        .speed = GPIO_SPEED_FREQ_HIGH,
        .pull = GPIO_PULL_NONE,
        .clkEn.Bus = &RCC->AHB1ENR,
        .clkEn.Offset = RCC_AHB1ENR_GPIOAEN,
        .regOffset = GPIOA
    };

    GPIO_Config(&LED_Gpio);

}

void GPIO_Toggle (GPIO_PinTypeDef GPIO_Pin, GPIO_TypeDef* GPIOx) {
    GPIOx->ODR ^= (1 << GPIO_Pin);
}
