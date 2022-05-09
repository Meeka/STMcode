#ifndef __RCC_CONFIG_H
#define __RCC_CONFIG_H

/*****************STEPS*****************************
    *System clock configuration:
    *           System Clock source	            = PLL (HSE)
    *           SYSCLK(Hz)                      = 180000000
    *           HCLK(Hz)                        = 180000000
    *           AHB Prescaler                   = 1
    *           APB1 Prescaler                  = 4
    *           APB2 Prescaler                  = 2
    *           HSE Frequency(Hz)               = 8000000
    *           PLL_M                           = 4
    *           PLL_N                           = 180
    *           PLL_P                           = 2
    *           VDD(V)                          = 3.3
    *           Main regulator output voltage   = Scale1 mode
    *           Flash Latency(WS)               = 5
***************************************************/




#include "stm32f446xx.h"
#include "system_stm32f4xx.h"

#define PLL_M   4
#define PLL_N   180
#define PLL_P   0   //PLLP = 2

typedef enum {
    NO_DIV,
    DIV_2,
    DIV_4,
    DIV_8,
    DIV_16
} RCC_APBPresc_TypeDef;

typedef enum {
    GPIOA_periph,
    GPIOB_periph,
    GPIOC_periph,
    GPIOD_periph,
    GPIOE_periph,
    GPIOF_periph,
    GPIOG_periph,
    GPIOH_periph,
    CRC_periph,
    BKPSRAM_periph,
    DMA1_periph,
    DMA2_periph,
    OTGHS_periph,
    OTGHSULPI_periph,
    DCMI_periph,
    OTGFS_periph,
    FMC_periph,
    QSPI_periph,
    TIM2_periph,
    TIM3_periph,
    TIM4_periph,
    TIM5_periph,
    TIM6_periph,
    TIM7_periph,
    TIM12_periph,
    TIM13_periph,
    TIM14_periph,
    WWDG_periph,
    SPI2_periph,
    SPI3_periph,
    SPDIFRX_periph,
    USART2_periph,
    USART3_periph,
    USART4_periph,
    USART5_periph,
    I2C1_periph,
    I2C2_periph,
    I2C3_periph,
    FMPI2C1_periph,
    CAN1_periph,
    CAN2_periph,
    CEC_periph,
    PWR_periph,
    DAC_periph,
    TIM1_periph,
    TIM8_periph,
    USART1_periph,
    USART6_periph,
    ADC1_periph,
    ADC2_periph,
    ADC3_periph,
    SDIO_periph,
    SPI1_periph,
    SPI4_periph,
    SYSCFG_periph,
    TIM9_periph,
    TIM10_periph,
    TIM11_periph,
    SAI1_periph,
    SAI2_periph,
    COUNT_periph
} RCC_Periph_List_TypeDef;

typedef struct {
    volatile uint32_t * Bus;
    uint32_t Offset;
} RCC_Periph_TypeDef;

void SysClockConfig (void);
uint32_t GetHCLKFreq (void);
uint32_t GetPCLK1Freq (void);
uint32_t GetPCLK2Freq (void);
void PeriphClkEnable (RCC_Periph_List_TypeDef peripheral);

#endif
