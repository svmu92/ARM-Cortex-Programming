#include "STM32F4_RTOS_BSP.h"

void TIM2_Init()
{
	TIM_ClockConfigTypeDef sClockSourceConfig;
	TIM_MasterConfigTypeDef sMasterConfig;
	
	htim2.Instance = TIM2;
	htim2.Init.Prescaler = 16000; //Scale down to milliseconds
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = 1; //ms
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	
	HAL_TIM_Base_Init(&htim2);
	
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	HAL_TIM_ConfigClockSource(&htim2,&sClockSourceConfig);
	
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	
	HAL_TIMEx_MasterConfigSynchronization(&htim2,&sMasterConfig);
	
	
}


void TIM3_Init()
{
	TIM_ClockConfigTypeDef sClockSourceConfig;
	TIM_MasterConfigTypeDef sMasterConfig;
	
	htim3.Instance = TIM3;
	htim3.Init.Prescaler = 16000; //Scale down to milliseconds
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim3.Init.Period = 1; //ms
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	
	HAL_TIM_Base_Init(&htim3);
	
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	HAL_TIM_ConfigClockSource(&htim3,&sClockSourceConfig);
	
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	
	HAL_TIMEx_MasterConfigSynchronization(&htim3,&sMasterConfig);
	
}

void TIM4_Init()
{
	TIM_ClockConfigTypeDef sClockSourceConfig;
	TIM_MasterConfigTypeDef sMasterConfig;
	
	htim4.Instance = TIM2;
	htim4.Init.Prescaler = 16000; //Scale down to milliseconds
	htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim4.Init.Period = 1; //ms
	htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	
	HAL_TIM_Base_Init(&htim4);
	
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	HAL_TIM_ConfigClockSource(&htim4,&sClockSourceConfig);
	
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	
	HAL_TIMEx_MasterConfigSynchronization(&htim4,&sMasterConfig);
		
}

void TIM5_Init()
{
	TIM_ClockConfigTypeDef sClockSourceConfig;
	TIM_MasterConfigTypeDef sMasterConfig;
	
	htim5.Instance = TIM2;
	htim5.Init.Prescaler = 16000; //Scale down to milliseconds
	htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim5.Init.Period = 1; //ms
	htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	
	HAL_TIM_Base_Init(&htim5);
	
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	HAL_TIM_ConfigClockSource(&htim5,&sClockSourceConfig);
	
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	
	HAL_TIMEx_MasterConfigSynchronization(&htim5,&sMasterConfig);
}

