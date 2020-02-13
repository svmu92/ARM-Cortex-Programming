#include "stm32f407xx.h"
#include <stdint.h>

#define BLUE 		(1<<30)
#define BLUEON	(1<<15)
#define BLUEOFF	(~(1<<15))
int main()
{
	int i;
	RCC->AHB1ENR |= (1<<3);
	GPIOD->MODER |= BLUE;
	while(1)
	{
		GPIOD->ODR 	 |= BLUEON;
		for(i=0;i<7000000;i++);
		GPIOD->ODR	&= BLUEOFF;
		for(i=0;i<7000000;i++);
	}
	
}
