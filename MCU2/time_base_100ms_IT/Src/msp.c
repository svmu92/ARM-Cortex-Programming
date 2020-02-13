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

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htimer)
{

	/* 1. Enable timer clock */
	__HAL_RCC_TIM6_CLK_ENABLE();

	/* 2. Enable Timer IRQ */
	HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);

	/* 3. Set Priority */
	HAL_NVIC_SetPriority(TIM6_DAC_IRQn,15,0);

}

