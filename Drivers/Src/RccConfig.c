#include "RccConfig.h"

static volatile uint32_t HCLK_Freq;

//Maps divider values for APB freq calculation
RCC_APBPresc_TypeDef APBPrescTableDiv[8] = {
    NO_DIV,
    NO_DIV,
    NO_DIV,
    NO_DIV,
    DIV_2,
    DIV_4,
    DIV_8,
    DIV_16
};

//Maps peripherals to their respective clock enable register
RCC_Periph_TypeDef RCCPeripheralDef[] = {
    [GPIOA_periph].Bus = &RCC->AHB1ENR,
    [GPIOA_periph].Offset = RCC_AHB1ENR_GPIOAEN,
    [GPIOB_periph].Bus = &RCC->AHB1ENR,
    [GPIOB_periph].Offset = RCC_AHB1ENR_GPIOBEN,
    [GPIOC_periph].Bus = &RCC->AHB1ENR,
    [GPIOC_periph].Offset = RCC_AHB1ENR_GPIOCEN,
    [GPIOD_periph].Bus = &RCC->AHB1ENR,
    [GPIOD_periph].Offset = RCC_AHB1ENR_GPIODEN,
    [GPIOE_periph].Bus = &RCC->AHB1ENR,
    [GPIOE_periph].Offset = RCC_AHB1ENR_GPIOEEN,
    [GPIOF_periph].Bus = &RCC->AHB1ENR,
    [GPIOF_periph].Offset = RCC_AHB1ENR_GPIOFEN,
    [GPIOG_periph].Bus = &RCC->AHB1ENR,
    [GPIOG_periph].Offset = RCC_AHB1ENR_GPIOGEN,
    [GPIOH_periph].Bus = &RCC->AHB1ENR,
    [GPIOH_periph].Offset = RCC_AHB1ENR_GPIOHEN,
    [CRC_periph].Bus = &RCC->AHB1ENR,
    [CRC_periph].Offset = RCC_AHB1ENR_CRCEN,
    [BKPSRAM_periph].Bus = &RCC->AHB1ENR,
    [BKPSRAM_periph].Offset = RCC_AHB1ENR_BKPSRAMEN,
    [DMA1_periph].Bus = &RCC->AHB1ENR,
    [DMA1_periph].Offset = RCC_AHB1ENR_DMA1EN,
    [DMA2_periph].Bus = &RCC->AHB1ENR,
    [DMA2_periph].Offset = RCC_AHB1ENR_DMA2EN,
    [OTGHS_periph].Bus = &RCC->AHB1ENR,
    [OTGHS_periph].Offset = RCC_AHB1ENR_OTGHSEN,
    [OTGHSULPI_periph].Bus = &RCC->AHB1ENR,
    [OTGHSULPI_periph].Offset = RCC_AHB1ENR_OTGHSULPIEN,
    [DCMI_periph].Bus = &RCC->AHB2ENR,
    [DCMI_periph].Offset = RCC_AHB2ENR_DCMIEN,
    [OTGFS_periph].Bus = &RCC->AHB2ENR,
    [OTGFS_periph].Offset = RCC_AHB2ENR_OTGFSEN,
    [FMC_periph].Bus = &RCC->AHB3ENR,
    [FMC_periph].Offset = RCC_AHB3ENR_FMCEN,
    [QSPI_periph].Bus = &RCC->AHB3ENR,
    [QSPI_periph].Offset = RCC_AHB3ENR_QSPIEN,
    [TIM2_periph].Bus = &RCC->APB1ENR,
    [TIM2_periph].Offset = RCC_APB1ENR_TIM2EN,
    [TIM3_periph].Bus = &RCC->APB1ENR,
    [TIM3_periph].Offset = RCC_APB1ENR_TIM3EN,
    [TIM4_periph].Bus = &RCC->APB1ENR,
    [TIM4_periph].Offset = RCC_APB1ENR_TIM4EN,
    [TIM5_periph].Bus = &RCC->APB1ENR,
    [TIM5_periph].Offset = RCC_APB1ENR_TIM5EN,
    [TIM6_periph].Bus = &RCC->APB1ENR,
    [TIM6_periph].Offset = RCC_APB1ENR_TIM6EN,
    [TIM7_periph].Bus = &RCC->APB1ENR,
    [TIM7_periph].Offset = RCC_APB1ENR_TIM7EN,
    [TIM12_periph].Bus = &RCC->APB1ENR,
    [TIM12_periph].Offset = RCC_APB1ENR_TIM12EN,
    [TIM13_periph].Bus = &RCC->APB1ENR,
    [TIM13_periph].Offset = RCC_APB1ENR_TIM13EN,
    [TIM14_periph].Bus = &RCC->APB1ENR,
    [TIM14_periph].Offset = RCC_APB1ENR_TIM14EN,
    [WWDG_periph].Bus = &RCC->APB1ENR,
    [WWDG_periph].Offset = RCC_APB1ENR_WWDGEN,
    [SPI2_periph].Bus = &RCC->APB1ENR,
    [SPI2_periph].Offset = RCC_APB1ENR_SPI2EN,
    [SPI3_periph].Bus = &RCC->APB1ENR,
    [SPI3_periph].Offset = RCC_APB1ENR_SPI3EN,
    [SPDIFRX_periph].Bus = &RCC->APB1ENR,
    [SPDIFRX_periph].Offset = RCC_APB1ENR_SPDIFRXEN,
    [USART2_periph].Bus = &RCC->APB1ENR,
    [USART2_periph].Offset = RCC_APB1ENR_USART2EN,
    [USART3_periph].Bus = &RCC->APB1ENR,
    [USART3_periph].Offset = RCC_APB1ENR_USART3EN,
    [USART4_periph].Bus = &RCC->APB1ENR,
    [USART4_periph].Offset = RCC_APB1ENR_UART4EN,
    [USART5_periph].Bus = &RCC->APB1ENR,
    [USART5_periph].Offset = RCC_APB1ENR_UART5EN,
    [I2C1_periph].Bus = &RCC->APB1ENR,
    [I2C1_periph].Offset = RCC_APB1ENR_I2C1EN,
    [I2C2_periph].Bus = &RCC->APB1ENR,
    [I2C2_periph].Offset = RCC_APB1ENR_I2C2EN,
    [I2C3_periph].Bus = &RCC->APB1ENR,
    [I2C3_periph].Offset = RCC_APB1ENR_I2C3EN,
    [FMPI2C1_periph].Bus = &RCC->APB1ENR,
    [FMPI2C1_periph].Offset = RCC_APB1ENR_FMPI2C1EN,
    [CAN1_periph].Bus = &RCC->APB1ENR,
    [CAN1_periph].Offset = RCC_APB1ENR_CAN1EN,
    [CAN2_periph].Bus = &RCC->APB1ENR,
    [CAN2_periph].Offset = RCC_APB1ENR_CAN2EN,
    [CEC_periph].Bus = &RCC->APB1ENR,
    [CEC_periph].Offset = RCC_APB1ENR_CECEN,
    [PWR_periph].Bus = &RCC->APB1ENR,
    [PWR_periph].Offset = RCC_APB1ENR_PWREN,
    [DAC_periph].Bus = &RCC->APB1ENR,
    [DAC_periph].Offset = RCC_APB1ENR_DACEN,
    [TIM1_periph].Bus = &RCC->AHB1ENR,
    [TIM1_periph].Offset = RCC_APB2ENR_TIM1EN,
    [TIM8_periph].Bus = &RCC->APB2ENR,
    [TIM8_periph].Offset = RCC_APB2ENR_TIM8EN,
    [USART1_periph].Bus = &RCC->APB2ENR,
    [USART1_periph].Offset = RCC_APB2ENR_USART1EN,
    [USART6_periph].Bus = &RCC->APB2ENR,
    [USART6_periph].Offset = RCC_APB2ENR_USART6EN,
    [ADC1_periph].Bus = &RCC->APB2ENR,
    [ADC1_periph].Offset = RCC_APB2ENR_ADC1EN,
    [ADC2_periph].Bus = &RCC->APB2ENR,
    [ADC2_periph].Offset = RCC_APB2ENR_ADC2EN,
    [ADC3_periph].Bus = &RCC->APB2ENR,
    [ADC3_periph].Offset = RCC_APB2ENR_ADC3EN,
    [SDIO_periph].Bus = &RCC->APB2ENR,
    [SDIO_periph].Offset = RCC_APB2ENR_SDIOEN,
    [SPI1_periph].Bus = &RCC->APB2ENR,
    [SPI1_periph].Offset = RCC_APB2ENR_SPI1EN,
    [SPI4_periph].Bus = &RCC->APB2ENR,
    [SPI4_periph].Offset = RCC_APB2ENR_SPI4EN,
    [SYSCFG_periph].Bus = &RCC->APB2ENR,
    [SYSCFG_periph].Offset = RCC_APB2ENR_SYSCFGEN,
    [TIM9_periph].Bus = &RCC->APB2ENR,
    [TIM9_periph].Offset = RCC_APB2ENR_TIM9EN,
    [TIM10_periph].Bus = &RCC->APB2ENR,
    [TIM10_periph].Offset = RCC_APB2ENR_TIM10EN,
    [TIM11_periph].Bus = &RCC->APB2ENR,
    [TIM11_periph].Offset = RCC_APB2ENR_TIM11EN,
    [SAI1_periph].Bus = &RCC->APB2ENR,
    [SAI1_periph].Offset = RCC_APB2ENR_SAI1EN,
    [SAI2_periph].Bus = &RCC->APB2ENR,
    [SAI2_periph].Offset = RCC_APB2ENR_SAI2EN
};

void SysClockConfig (void) {
    //1. Enable HSE and wait for the HSE to be ready
    RCC->CR |= RCC_CR_HSEON;
    while (!(RCC->CR & RCC_CR_HSERDY));
    //2. Set the POWER ENABLE CLOCK and VOLTAGE REGULATOR
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    PWR->CR |= PWR_CR_VOS;
    //3. Configure the FLASH  PREFETCH and the LATENCY related settings
    FLASH->ACR |= FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_5WS;
    //4. Configure the PRE-SCALARS HCLK, PCLK1, PCLK2
    //AHB PR
    RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
    //AHB1 PR
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;
    //AHB2 PR
    RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;
    //5. Configure the MAIN PLL
    RCC->PLLCFGR = (PLL_M << 0) | (PLL_N << 6) | (PLL_P << 16) | (RCC_PLLCFGR_PLLSRC_HSE);
    //6. Enable the PLL and wait for it to be ready
    RCC->CR |= RCC_CR_PLLON;
    while(!(RCC->CR & RCC_CR_PLLRDY));
    //7. Select the clock source and wait for it to be set
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
    //8. Set var to keep track of HCLK frequency
    HCLK_Freq = 180000000;
}

uint32_t GetHCLKFreq (void) {
    return HCLK_Freq;
}

uint32_t GetPCLK1Freq (void) {
    uint32_t temp = RCC->CFGR;
    temp &= RCC_CFGR_PPRE1_Msk;

    return HCLK_Freq >> APBPrescTableDiv[(temp >> RCC_CFGR_PPRE1_Pos)];
}

uint32_t GetPCLK2Freq (void) {
    uint32_t temp = RCC->CFGR;
    temp &= RCC_CFGR_PPRE2_Msk;

    return HCLK_Freq >> APBPrescTableDiv[(temp >> RCC_CFGR_PPRE2_Pos)];
}

void PeriphClkEnable (RCC_Periph_List_TypeDef peripheral) {
    *RCCPeripheralDef[peripheral].Bus |= RCCPeripheralDef[peripheral].Offset;
}