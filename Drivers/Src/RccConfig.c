#include "RccConfig.h"

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
}

void delay (uint32_t time) {
	while (time--);
}
