#include "stm32f4xx_hal.h"



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


void HAL_TIM_OC_MspInit(TIM_HandleTypeDef *htim)
{
	GPIO_InitTypeDef tim2ch1_gpio;
	// 1. Enable the clock for Timer2
	__HAL_RCC_TIM2_CLK_ENABLE();

	// 2. Select Alternate Function for GPIO as Timer Channel
	/* PA0 ----- TIM2_CH1
	 * PA1 ----- TIM2_CH2
	 * PB10----- TIM2_CH3
	 * PB11----- TIM2_CH4
	 * */

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();


	tim2ch1_gpio.Pin = GPIO_PIN_5 | GPIO_PIN_1;
	tim2ch1_gpio.Mode = GPIO_MODE_AF_PP;
	tim2ch1_gpio.Alternate = GPIO_AF1_TIM2;
	HAL_GPIO_Init(GPIOA, &tim2ch1_gpio);


	tim2ch1_gpio.Pin = GPIO_PIN_10 | GPIO_PIN_11;
	tim2ch1_gpio.Mode = GPIO_MODE_AF_PP;
	tim2ch1_gpio.Alternate = GPIO_AF1_TIM2;
	HAL_GPIO_Init(GPIOB, &tim2ch1_gpio);


	// 3. NVIC Settings
	HAL_NVIC_SetPriority(TIM2_IRQn,15,0);
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
}
