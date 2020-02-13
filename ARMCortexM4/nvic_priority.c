#include "stm32f407xx.h"


void WWDG_IRQHandler(void)
{
	NVIC_SetPendingIRQ(USART3_IRQn);
	while(1);	
}


void USART3_IRQHandler(void)
{
	
	while(1);
}

int main()
{
	/*Enable the Interrutps*/
	NVIC_EnableIRQ(WWDG_IRQn);
	NVIC_EnableIRQ(USART3_IRQn);
	
	/*Set Priority*/
	NVIC_SetPriority(WWDG_IRQn,5);
	NVIC_SetPriority(USART3_IRQn,0);
	
	
	/*Pend Watchdog Interrupts*/
	NVIC_SetPendingIRQ(WWDG_IRQn);
	
	while(1);
	return 0;
	
}