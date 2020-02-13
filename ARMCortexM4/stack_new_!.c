#include <stdint.h>
#include "stm32f407xx.h"
#include "Board_LED.h"
void delay()
{
	unsigned int i=0;
	for(i=0;i<90000;i++);
		
}

int main()
{
	
	/*Program to change Stack Top to 0x2001_BFFF + 1 */
		__set_MSP(0x2001BFFF+1);
	
	/*Change current SP to PSP */
		uint32_t value = __get_CONTROL();
		value|=(1<<1);
		__set_CONTROL(value);
	
	/*Initialize PSP*/
		__set_PSP(0x2001BFFF+1);
	
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
