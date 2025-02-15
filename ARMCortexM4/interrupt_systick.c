#include <stdint.h>
#include "stm32f407xx.h"
#include "led_header.h"
#include "my_board.h"

/* highest */
#define HIGH_PRIORITY_VAL_1   0X00 
/*lowest*/
#define LOW_PRIORITY_VAL_1    0XF0 

#define HIGH_PRIORITY_VAL_2   0X10 
#define LOW_PRIORITY_VAL_2    0XE0  

void button_init(void)
{
	/* Enable GPIOA clock */
	/* because BUTTON is connected to GPIOA */
	RCC->AHB1ENR |= 0x01;

	//set the mode 
	GPIOA->MODER &= ~0x3;
	GPIOA->PUPDR  &= ~0x3;

	//enable clock for RCC
	RCC->APB2ENR |= 0x00004000;

	//configure the interrupt 
	EXTI->IMR |= 0x01;
	//	EXTI->RTSR |= 0X01;
	EXTI->FTSR |= 0X01;
	
	
	//nvic configuration 
	/* button is irq number 6. which is connected over EXTI0 line in stm32f4xx */
	NVIC->IP[EXTI0_IRQn] = 0X00;// (low priority )
	NVIC_EnableIRQ(EXTI0_IRQn);

}



int main(void)
{
	uint32_t val;
	led_init();
	
	//No of ticks after which SysTick will issue an exception
	SysTick_Config(2000);

	/*configure Systick priority and enable it */
	SCB->SHP[0x0B] = 0XF0;// ( high priority)
	NVIC_EnableIRQ(SysTick_IRQn);
	


	/* Configure EXTI Line0 (connected to PA0 pin) in interrupt mode */
	button_init();
	
	
	/* Infinite loop */
	while (1)
	{
		
	}
	
}


void SysTick_Handler(void)
{
		//PD13
	 led_on(LED_3);
	 //for(int i=0;i<50000;i++); 
	 led_off(LED_3);
	
}



void EXTI0_IRQHandler(void)
{
	
int i=0;
/* clear the interrupt pending bit of exti0*/
if( (EXTI->PR & 0x01) )
{
	EXTI->PR &= 0x01;

}
  //PD12
	led_on(LED_4);
	for(i=0;i<50000;i++); //do some work
	led_off(LED_4);
}
