#ifndef __GPIO_H
#define __GPIO_H

#include "stm32f446xx.h"

typedef enum {
    GPIO_PIN_0,
    GPIO_PIN_1,
    GPIO_PIN_2,
    GPIO_PIN_3,
    GPIO_PIN_4,
    GPIO_PIN_5,
    GPIO_PIN_6,
    GPIO_PIN_7,
    GPIO_PIN_8,
    GPIO_PIN_9,
    GPIO_PIN_10,
    GPIO_PIN_11,
    GPIO_PIN_12,
    GPIO_PIN_13,
    GPIO_PIN_14,
    GPIO_PIN_15,
    GPIO_PIN_NUM
} GPIO_PinTypeDef;

typedef enum {
    GPIO_MODE_INPUT,
    GPIO_MODE_OUTPUT,
    GPIO_MODE_ALT
} GPIO_ModeTypeDef;

typedef enum  {
    GPIO_TYPE_PUSH_PULL,
    GPIO_TYPE_OPEN_DRAIN
} GPIO_OutputTypeDef;

typedef enum {
    GPIO_PULL_NONE,
    GPIO_PULL_DOWN,
    GPIO_PULL_UP
} GPIO_PullTypeDef;

typedef enum {
    GPIO_SPEED_FREQ_LOW,
    GPIO_SPEED_FREQ_MED,
    GPIO_SPEED_FREQ_HIGH,
    GPIO_SPEED_FREQ_VERY_HIGH
} GPIO_SpeedTypeDef;

typedef enum {
    GPIO_AF0_RTC_50Hz = 0,
    GPIO_AF0_MCO = 0,
    GPIO_AF0_SWJ = 0,
    GPIO_AF0_TAMPER = 0,
    GPIO_AF0_TRACE = 0,
    GPIO_AF1_TIM1 = 1,
    GPIO_AF1_TIM2 = 1,
    GPIO_AF2_TIM3 = 2,
    GPIO_AF2_TIM4 = 2,
    GPIO_AF2_TIM5 = 2,
    GPIO_AF3_TIM8 = 3,
    GPIO_AF3_CEC = 3,
    GPIO_AF4_I2C1 = 4,
    GPIO_AF4_I2C2 = 4,
    GPIO_AF4_I2C3 = 4,
    GPIO_AF4_CEC = 4,
    GPIO_AF5_SPI1 = 5,
    GPIO_AF5_SPI2 = 5,
    GPIO_AF5_SPI3 = 5,
    GPIO_AF5_SPI4 = 5,
    GPIO_AF6_SPI2 = 6,
    GPIO_AF6_SPI3 = 6,
    GPIO_AF6_SPI4 = 6,
    GPIO_AF6_SAI1 = 6,
    GPIO_AF7_USART1 = 7,
    GPIO_AF7_USART2 = 7,
    GPIO_AF7_USART3 = 7,
    GPIO_AF7_UART5 = 7,
    GPIO_AF7_SPI2 = 7,
    GPIO_AF7_SPI3 = 7,
    GPIO_AF7_SPDIFRX = 7,
    GPIO_AF8_UART4 = 8,
    GPIO_AF8_UART5 = 8,
    GPIO_AF8_USART6 = 8,
    GPIO_AF8_SAI2 = 8,
    GPIO_AF8_SPDIFRX = 8,
    GPIO_AF9_CAN1 = 9,
    GPIO_AF9_CAN2 = 9,
    GPIO_AF9_TIM12 = 9,
    GPIO_AF9_TIM13 = 9,
    GPIO_AF9_TIM14 = 9,
    GPIO_AF9_QSPI = 9,
    GPIO_AF10_OTG_FS = 10,
    GPIO_AF10_OTG_HSv,
    GPIO_AF10_SAI2 = 10,
    GPIO_AF10_QSPI = 10,
    GPIO_AF11_ETH = 11,
    GPIO_AF12_SDIO = 12,
    GPIO_AF12_FMC = 12,
    GPIO_AF12_OTG_HS_FS = 12,
    GPIO_AF13_DCMI = 13,
    GPIO_AF15_EVENTOUT = 15
} GPIO_AltFuncTypeDef;

typedef struct {
    GPIO_PinTypeDef     Pin;    //GPIO Pin
    GPIO_ModeTypeDef    Mode;   //Operating mode
    GPIO_OutputTypeDef  OType;  //Output type
    GPIO_PullTypeDef    Pull;   //Pull-up or Pull-down
    GPIO_SpeedTypeDef   Speed;  //Speed for pin
    GPIO_AltFuncTypeDef Alt;    //Peripheral to be connected to pin
} GPIO_InitTypeDef;


/************STEPS***********
 * 1. Enable GPIO Clock
 * 2. Set pin mode
 * 2a. Set output mode if pin is output
 * 3. Configure speed
 * 4. Configure pull-up or pull-down
 * 5. Configure alternate function
 * *************************/
void GPIO_Config (GPIO_InitTypeDef* GPIO_Settings, GPIO_TypeDef* GPIOx);

/**********STEPS************
 * 1. Setup User LED on PA5
 * *************************/
void GPIO_Init (void);


#endif