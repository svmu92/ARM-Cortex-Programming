/*
 * msp.c
 *
 *  Created on: 13-Apr-2019
 *      Author: Sreenath V
 */
#include "main.h"

void HAL_MspInit(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_MspInit could be implemented in the user file
   */

	//Here we will do low level processor specific inits
	//1. Setup the priority grouping
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	//2. Enable the required system exceptions
	SCB->SHCSR |= (0x7 << 16); //usage fault, memory fault and bus fault exceptions enabled.

	//3. Configure the priority for system exceptions
	HAL_NVIC_SetPriority(MemoryManagement_IRQn,0,0);
	HAL_NVIC_SetPriority(BusFault_IRQn,0,0);
	HAL_NVIC_SetPriority(UsageFault_IRQn,0,0);

}


void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	//here we have to do the low-level initialization of the USART peripheral
	GPIO_InitTypeDef gpio_uart;
	//1.Enable the clock
	__HAL_RCC_USART2_CLK_ENABLE();

	__HAL_RCC_GPIOA_CLK_ENABLE();

	//2. Do the Pin MUXing
	gpio_uart.Pin 	= GPIO_PIN_2;
	gpio_uart.Mode 	= GPIO_MODE_AF_PP;
	gpio_uart.Pull 	= GPIO_PULLUP;
	gpio_uart.Speed = GPIO_SPEED_FREQ_LOW;
	gpio_uart.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA,&gpio_uart);

	gpio_uart.Pin 	= GPIO_PIN_3;
//	gpio_uart.Mode 	= GPIO_MODE_AF_PP;
//	gpio_uart.Pull 	= GPIO_PULLUP;
//	gpio_uart.Speed = GPIO_SPEED_FREQ_LOW;
//	gpio_uart.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA,&gpio_uart);


	//3. Enable the IRQ and set up the priority (NVIC Settings)
	HAL_NVIC_EnableIRQ(USART2_IRQn);
	HAL_NVIC_SetPriority(USART2_IRQn,15,0);
}
