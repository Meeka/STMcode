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

void SysClockConfig (void) {
    //1. Enable HSE and wait for the HSE to be ready
    RCC->CR |= RCC_CR_HSEON;
    while (!(RCC->CR & RCC_CR_HSERDY));
    //2. Set the POWER ENABLE CLOCK and VOLTAGE REGULATOR
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    PWR->CR |= PWR_CR_VOS;
    //3. Configure the FLASH PREFETCH and the LATENCY related settings
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

void PeriphClkEnable (RCC_Periph_TypeDef ClkEn) {
    *ClkEn.Bus |= ClkEn.Offset;
}