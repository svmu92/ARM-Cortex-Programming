
#include "stm32f407xx.h"

//Watchdog Interrupt Handler
void WWDG_IRQHandler(void)
{
	for(int i=0;i<50;i++);
}


void generate_interrupt(void)
{
	//Watchdog interrupt
	NVIC_EnableIRQ(WWDG_IRQn);
	NVIC_SetPendingIRQ(WWDG_IRQn);
	
}




int main(void)
{
	/*change PRIMASK register 0th bit to 1*/
	__set_PRIMASK(1);
	generate_interrupt();
	while(1);
	return 0;
}
