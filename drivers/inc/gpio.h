#ifndef __GPIO_H
#define __GPIO_H

#include "stm32f446xx.h"
#include "rccConfig.h"

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
    GPIO_MODE_INPUT = 0,
    GPIO_MODE_OUTPUT = 1,
    GPIO_MODE_ALT = 2,
    GPIO_MODE_ANALOG = 3
} GPIO_ModeTypeDef;

typedef enum  {
    GPIO_TYPE_PUSH_PULL = 0,
    GPIO_TYPE_OPEN_DRAIN = 1
} GPIO_OutputTypeDef;

typedef enum {
    GPIO_PULL_NONE = 0,
    GPIO_PULL_UP = 1,
    GPIO_PULL_DOWN = 2
} GPIO_PullTypeDef;

typedef enum {
    GPIO_SPEED_FREQ_LOW = 0,
    GPIO_SPEED_FREQ_MED = 1,
    GPIO_SPEED_FREQ_HIGH = 2,
    GPIO_SPEED_FREQ_VERY_HIGH = 3
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
    GPIO_PinTypeDef     pin;       //GPIO Pin
    GPIO_ModeTypeDef    mode;      //Operating mode
    GPIO_OutputTypeDef  oType;     //Output type
    GPIO_PullTypeDef    pull;      //Pull-up or Pull-down
    GPIO_SpeedTypeDef   speed;     //Speed for pin
    GPIO_AltFuncTypeDef alt;       //Peripheral to be connected to pin
    RCC_Periph_TypeDef  clkEn;     //Peripheral clock enable in RCC
    GPIO_TypeDef*       regOffset; //Register Offset
} GPIO_InitTypeDef;

void GPIO_Enable (GPIO_InitTypeDef* GPIO_Settings);
void GPIO_setup_output_af (GPIO_InitTypeDef* GPIO_Settings);
void GPIO_Config(GPIO_InitTypeDef* GPIO_Settings);

/**********STEPS************
 * 1. Setup User LED on PA5
 * *************************/
void GPIO_Init (void);

void GPIO_Toggle (GPIO_PinTypeDef GPIO_Pin, GPIO_TypeDef* GPIOx);

#endif