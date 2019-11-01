//1. Enable the clock's access to the PORT of the PIN
//2. Set the pin's mode
//3. Set output

//AHB1_EN
//GREEN - PD12
//ORANGE - PD13
//RED - PD14
//BLUE - PD15

//GPIOxMODER - SET BITS 30,28,26,24
//GPIOxODR - SET BITS 15,14,13,12

#include "stm32f4xx.h"

#define RED			(1U<<14)
#define GREEN 	(1U<<12)
#define ORANGE 	(1U<<13)
#define BLUE		(1U<<15)

#define	REDBIT	(1U<<28)
#define	GREENBIT	(1U<<24)
#define	ORANGEBIT	(1U<<26)
#define	BLUEBIT	(1U<<30)

#define	GPIOD_CLK	(1U<<3)

int main()
{
	RCC->AHB1ENR 	|= GPIOD_CLK;
	
	GPIOD->MODER	|=	REDBIT | GREENBIT | ORANGEBIT | BLUEBIT;
	
	while(1)
	{
	GPIOD->ODR |= RED | GREEN | ORANGE | BLUE;
	}
	
}
