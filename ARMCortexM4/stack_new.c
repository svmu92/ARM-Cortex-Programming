#include "Board_LED.h"
void delay()
{
	unsigned int i=0;
	for(i=0;i<90000;i++);
		
}

int main()
{
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
