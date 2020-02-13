#include "stm32f407xx.h"

#define	RCC_BASE_ADDR							0x40023800
#define RCC_AHB1ENR_OFFSET_ADDR		0x30

#define RCC_AHB1ENR_ADDR					*((volatile unsigned long *)(RCC_BASE_ADDR + RCC_AHB1ENR_OFFSET_ADDR))
					
#define GPIOD_BASE_ADDR						0x40020C00
#define	GPIOD_MODER_REG					*((volatile unsigned long*)(GPIOD_BASE_ADDR+0))

#define GPIOD_ODR_OFFSET					0x14
#define GPIOD_ODR									*((volatile unsigned long*)(GPIOD_BASE_ADDR + GPIOD_ODR_OFFSET))

#define GPIOD_IDR_OFFSET					0x10
#define GPIOD_IDR									*((volatile unsigned long*)(GPIOD_BASE_ADDR + GPIOD_ODR_OFFSET))

#define Method2

int main(void)
{
	/*Enable the clock to the GPIOD port*/
	RCC_AHB1ENR_ADDR |= (1<<3); 					//Bit3 enables the clock for PORTD
	
	/*Make the GPIO pins as output pins*/
	GPIOD_MODER_REG |= ((1<<24) | (1<<26) | (1<<28) | (1<<30));
	
	/*Use the Data Register to write to GPIOD12 pin to turn LED On*/
	GPIOD_ODR |= (1<<12);
	
	while(1)
	{
		#ifdef Method1
			GPIOD_ODR ^= (1<<12);
			for(int i=0;i<90000;i++);
		#endif
		
		#ifdef Method2
			if(GPIOD_IDR & (1<<12))
			{
				GPIOD_ODR &= ~(1<<12);
				for(int i=0;i<90000;i++);
			}
			else
			{
				GPIOD_ODR |= (1<<12);
				for(int i=0;i<90000;i++);
			}
		#endif
	}
	
	return 0;
}
