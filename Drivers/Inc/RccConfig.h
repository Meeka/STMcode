#ifndef __RCC_CONFIG_H
#define __RCC_CONFIG_H

/**
	*System clock configuration:
	*			System Clock source							= PLL (HSE)
	*			SYSCLK(Hz)											= 180000000
	*			HCLK(Hz)												= 180000000
	*			AHB Prescaler										= 1
	*			APB1 Prescaler									= 4
	*			APB2 Prescaler									= 2
	*			HSE Frequency(Hz)								= 8000000
	*			PLL_M														= 4
	*			PLL_N														= 180
	*			PLL_P														= 2
	*			VDD(V)													= 3.3
	*			Main regulator output voltage		= Scale1 mode
	*			Flash Latency(WS)								= 5
	*/




#include "stm32f446xx.h"

#define PLL_M 	4
#define PLL_N 	180
#define PLL_P 	0	//PLLP = 2

void SysClockConfig (void);
void delay (uint32_t time);

#endif
