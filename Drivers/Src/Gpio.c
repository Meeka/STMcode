#include "Gpio.h"

void GPIO_Config (GPIO_InitTypeDef* GPIO_Settings, GPIO_TypeDef* GPIOx) {

    //1. Enable GPIO Clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN << ((uint32_t)GPIOx ^ AHB1PERIPH_BASE) % 400;

    //2. Set pin mode
    switch(GPIO_Settings->Mode) {
        case GPIO_MODE_INPUT:
            GPIOx->MODER &=  ~(GPIO_MODER_MODER0 << (GPIO_Settings->Pin * 2));
            break;
        case GPIO_MODE_OUTPUT:
            GPIOx->MODER |= GPIO_MODER_MODER0_0 << (GPIO_Settings->Pin * 2);     //Output (0b01)
            break;
        case GPIO_MODE_ALT:
            GPIOx->MODER |= GPIO_MODER_MODER0_1 << (GPIO_Settings->Pin * 2);    //AF (0b10)
            break;
    }

    //2a. Set output mode if pin is output
    if(GPIO_Settings->Mode == GPIO_MODE_OUTPUT) {
        switch(GPIO_Settings->OType) {
            case GPIO_TYPE_PUSH_PULL:
                GPIOx->OTYPER &= ~(GPIO_OTYPER_OT0 << GPIO_Settings->Pin);    //Push-pull (0b0)
                break;
            case GPIO_TYPE_OPEN_DRAIN:
                GPIOx->OTYPER |= GPIO_OTYPER_OT0 << GPIO_Settings->Pin;       //Open-drain (0b1)
                break;
        }
    }

    //3. Configure speed
    switch(GPIO_Settings->Speed) {
        case GPIO_SPEED_FREQ_LOW:
            GPIOx->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED0 << (GPIO_Settings->Pin * 2));  //Low-speed (0b00)
            break;
        case GPIO_SPEED_FREQ_MED:
            GPIOx->OSPEEDR |= GPIO_OSPEEDR_OSPEED0_0 << (GPIO_Settings->Pin * 2);   //Med-speed (0b01)
            break;
        case GPIO_SPEED_FREQ_HIGH:
            GPIOx->OSPEEDR |= GPIO_OSPEEDR_OSPEED0_1 << (GPIO_Settings->Pin * 2);   //High-speed (0b10)
            break;
        case GPIO_SPEED_FREQ_VERY_HIGH:
            GPIOx->OSPEEDR |= GPIO_OSPEEDR_OSPEED0 << (GPIO_Settings->Pin * 2);     //Very high-speed (0b11)
            break;
    }

    //4. Configure pull-up or pull-down
    switch(GPIO_Settings->Pull) {
        case GPIO_PULL_NONE:
            GPIOx->PUPDR &= ~(GPIO_PUPDR_PUPD0 << (GPIO_Settings->Pin * 2));    //No pull (0b00)
            break;
        case  GPIO_PULL_UP:
            GPIOx->PUPDR |= GPIO_PUPDR_PUPD0_0 << (GPIO_Settings->Pin * 2);     //Pull up (0b01)
            break;
        case GPIO_PULL_DOWN:
            GPIOx->PUPDR |= GPIO_PUPDR_PUPD0_1 << (GPIO_Settings->Pin * 2);     //Pull up (0b10)
            break;
    }

    //5. Configure alternate function
    if(GPIO_Settings->Mode == GPIO_MODE_ALT) {
        if(GPIO_Settings->Pin > 7) {
            //Use GPIO Alternate Function High register (For pins 15:8)
            GPIOx->AFR[1] |= GPIO_Settings->Alt << ((GPIO_Settings->Pin >> 7) * 4);
        }
        else {
            //Use GPIO Alternate Function Low register (For pins 7:0)
            GPIOx->AFR[0] |= GPIO_Settings->Alt << (GPIO_Settings->Pin * 4);
        }
    }
}

void GPIO_Init (void) {

    GPIO_InitTypeDef LED_Gpio = {0};

    //1. Setup User LED on PA5
    LED_Gpio.Pin = GPIO_PIN_5;
    LED_Gpio.Mode = GPIO_MODE_OUTPUT;
    LED_Gpio.Speed = GPIO_SPEED_FREQ_HIGH;
    LED_Gpio.Pull = GPIO_PULL_NONE;
    GPIO_Config(&LED_Gpio, GPIOA);

}

void GPIO_Toggle (GPIO_PinTypeDef GPIO_Pin, GPIO_TypeDef* GPIOx) {
    GPIOx->ODR ^= (1 << GPIO_Pin);
}
