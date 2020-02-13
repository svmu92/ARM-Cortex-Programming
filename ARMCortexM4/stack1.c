#include "Board_LED.h"

void delay()
{
	unsigned int i=0;
	for(i=0;i<90000;i++);
		
}

int main()
{
	
	/*Program to move stack to another position in SRAM1*/
	/*Stack Base = 0x2001_BFFF + 1*/
	
	__set_MSP(0x2001BFFF + 1);
	LED_Initialize();
	while(1)
	{
		LED_On (1);
		delay();
		LED_Off(1);
		delay();
	}
	return 0;
}
