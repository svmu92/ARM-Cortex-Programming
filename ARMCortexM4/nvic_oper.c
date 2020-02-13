

/* Enable and Pend the USART3 Interrupt */

#include "stm32f407xx.h"

#define USART3_IRQN	39


void USART3_IRQHandler(void)
{
	
	while(1);
}


int main(void)
{
	/*Enable the USART3 interrupt or USART3 IRQ Number */
	NVIC_Type *pNVIC;
	pNVIC = NVIC;
	
	//Enable the USART3 interrupt
	pNVIC->ISER[1] |= (1<<7);
	//NVIC_EnableIRQ(USART3_IRQn); 				CMSIS API
	
	//Pend the interrupt
	pNVIC->ISPR[1] |= (1<<7);
  //NVIC_SetPendingIRQ(USART3_IRQn); 		CMSIS API
	
	
	return 0;
	
	
}

