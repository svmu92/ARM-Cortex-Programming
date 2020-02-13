/*
 * it.c
 *
 *  Created on: 13-Apr-2019
 *      Author: Sreenath V
 */

#include "main.h"


//void HAL_IncTick(uwTick);
void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}


