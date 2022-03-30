

#include "main.h"



void GPIO_Config (void) {
	//1. Enable GPIO Clock
	RCC->AHB1ENR |= (1<<0);
	
	//2. Set the pin as OUTPUT
	GPIOA->MODER |= (1<<10); //pin PA5(bits 11:10) as output (01)
	
	//3. Configure OUTPUT MODE
	GPIOA->OTYPER = 0;
	GPIOA->OSPEEDR = 0;
}



int main (void) {
	SysClockConfig();
	GPIO_Config();
	
	while (1) {
		GPIOA->BSRR |= (1<<5);	//Set pin PA5
		delay (10000000);
		GPIOA->BSRR |= ((1<<5) <<16);	//Reset pin PA5
		delay (10000000);
	}
	
}
