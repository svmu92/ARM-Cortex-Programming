#include "stm32f4xx_hal.h"

extern TIM_HandleTypeDef htimer6;

void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}


void TIM6_DAC_IRQHandler(void)
{

	//__HAL_RCC_USART2_CLK_ENABLE();
	HAL_TIM_IRQHandler(&htimer6);
	//__HAL_RCC_USART2_CLK_DISABLE();

}

