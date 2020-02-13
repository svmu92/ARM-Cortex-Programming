#include <stdint.h>
#include "stm32f407xx.h"
#include "led_header.h"
#include "my_board.h"


void button_init()
{

	/*1. Enable GPIOA clock */
	/* because BUTTON is connected to GPIOA PIN0 */
	//RCC_AHB1ENR
	RCC->AHB1ENR |= 0X01; //Enables the clock
	

	/* 2. set the mode of GPIOA pin0 to "INPUT" */
	GPIOA->MODER &= ~0X03;


	
	/*3. set the interrupt triggering level */
	//(EXTI_FTSR
	EXTI->FTSR |= 0X01;	

	/*4. enable the interrupt over EXTI0 */
	EXTI->IMR |= 0X01;


	/*5. the interrupt on NVIC for IRQ6 */
  NVIC->ISER[0] |= ( 1 << EXTI0_IRQn);
	
}


int main()
{
	
	led_init();
	
	button_init();
	
	
	while(1)
	{
		
		
		
		
	}
	
}


void EXTI0_IRQHandler(void)
{
	/*clear the pending bit for exti0 */
		if( (EXTI->PR & 0x01) )
	{
		EXTI->PR = 0x01;//Writing 1 , clears the pending bit for exti0
	
	}
	led_toggle(LED_4);
	
	
	/*Triggering PendSV Exception */
	
	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
	
}


void PendSV_Handler (void)
{
	/*Bottom half work done here */
	
	led_toggle(LED_3);
	
	
}

	