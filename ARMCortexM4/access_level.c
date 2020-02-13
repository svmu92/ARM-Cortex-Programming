
#include "stm32f407xx.h"

void call_application_Task(void);
//Watchdog Interrupt Handler
void WWDG_IRQHandler(void)
{
		uint32_t value=__get_CONTROL();
	value=value&~(1<<0);
	__set_CONTROL(value);
	for(int i=0;i<50;i++);
}


void generate_interrupt(void)
{
	//Watchdog interrupt
	NVIC_EnableIRQ(WWDG_IRQn);
	NVIC_SetPendingIRQ(WWDG_IRQn);
	
}


void RTOS_Init(void)
{
	uint32_t value=__get_CONTROL();
	value=value|(1<<0);
	__set_CONTROL(value);
	/*change privilege level to unprivileged level*/
	call_application_Task();
}

void call_application_Task()
{
	uint32_t value=__get_CONTROL();
	value=value&~(1<<0);
	__set_CONTROL(value);//This cannot be done as access level is unprivileged
	
	generate_interrupt();
}

int main(void)
{
	RTOS_Init();	
	while(1);
	return 0;
}
