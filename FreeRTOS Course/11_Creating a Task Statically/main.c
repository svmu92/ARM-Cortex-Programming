#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core


/*
#define configSUPPORT_STATIC_ALLOCATION 			1
vApplicationGetIdleTaskMemory()
void vApplicationGetTimerTaskMemory()

*/
#define GREEN GPIO_PIN_12
#define ORANGE GPIO_PIN_13
#define RED GPIO_PIN_14
#define BLUE GPIO_PIN_15

#define bluetask_STACK_SIZE 100
StaticTask_t xBlueControllerTaskBuffer;
StackType_t xBlueControllerStack[bluetask_STACK_SIZE];
//uint32_t blueStack[100];


void GPIO_Init(void);
void vBlueLedControllerTask(void *pvParameters);
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
																	StackType_t **ppxIdleTaskStackBuffer,
																	uint32_t *pulIdleTaskStackSize );
int main()
{
		GPIO_Init();
		xTaskCreateStatic(vBlueLedControllerTask,
											"Blue LED Controller",
											bluetask_STACK_SIZE,
											NULL,
											1,
											xBlueControllerStack,
											&xBlueControllerTaskBuffer	
											);
		vTaskStartScheduler();
		while(1)
		{
		}
}


void vBlueLedControllerTask(void *pvParameters)
{
	int i;
	while(1)
	{
		HAL_GPIO_TogglePin(GPIOD,BLUE);
		for (i=0;i<70000;i++);
	}
	
}





void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
																	StackType_t **ppxIdleTaskStackBuffer,
																	uint32_t *pulIdleTaskStackSize )
{
	static StaticTask_t xIdleTaskTCB;
	static StackType_t uxIdleTaskStack [ configMINIMAL_STACK_SIZE ];
	
	*ppxIdleTaskTCBBuffer = &xIdleTaskTCB;
	*ppxIdleTaskStackBuffer = uxIdleTaskStack;
	*pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
	
}


void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer,
																	StackType_t **ppxTimerTaskStackBuffer,
																	uint32_t *pulTimerTaskStackSize )
{
	static StaticTask_t xTimerTaskTCB;
	static StackType_t uxTimerTaskStack[configTIMER_TASK_STACK_DEPTH];
	
		*ppxTimerTaskTCBBuffer = &xTimerTaskTCB;
		*ppxTimerTaskStackBuffer = uxTimerTaskStack;
	  *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
	
}


void GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pins : PD12 PD13 PD14 PD15 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);	
}

