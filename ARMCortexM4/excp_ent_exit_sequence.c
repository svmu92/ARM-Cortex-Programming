#include "stm32f407xx.h"
#include "Board_LED.h"

void delay(void)
{
	uint32_t i;
	for(i=0;i<50000;i++);
}

void WWDG_IRQHandler(void)
{
	LED_Off(0);
	LED_Off(1);
	
	
}


int main(void)
{
	
	
	/* Change to PSP
	
	uint32_t value= __get_CONTROL();
  value |= (1<<1)
	__set_CONTROL(value);
	
	
	__set_PSP(SRAM2_BASE);
	*/
	
	
	LED_Initialize();
	while(1)
	{
	LED_On(0);
	LED_On(1);
	
	delay();

	NVIC_EnableIRQ(WWDG_IRQn);
	NVIC_SetPendingIRQ(WWDG_IRQn);
	
	delay();
	//LED_Off(0);
	//LED_Off(1);
	LED_On(0);
	LED_On(1);
	
	
	delay();
	}
	return 0;
}


	
