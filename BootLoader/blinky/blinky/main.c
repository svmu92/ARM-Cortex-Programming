
#include<stdint.h>
#include "Board_LED.h"
#include "Board_Buttons.h"


void delay(void)
{
	uint32_t i =0;
	for(i =0; i < 500000 ; i++);
}

int main(void)
{
	
	LED_Initialize();
	Buttons_Initialize();

while(1)
{
/* whenever button is pressed, toggle the LEDs */
/*	Buttons_GetState() returns 1 if USER is pressed , otherwise 0 */
	//if( Buttons_GetState() == 1 )
	{
		LED_On(0);
		delay();
		LED_Off(0);
		delay();
	}
	
}
	
	return 0;
}
