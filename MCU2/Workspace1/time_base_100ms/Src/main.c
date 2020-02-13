#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "main.h"



void SystemClockConfig(void);
void Error_Handler(void);
void Timer6_Init(void);
void GPIO_Init(void);

TIM_HandleTypeDef htimer6;

int main(void)
{
	HAL_Init();
	SystemClockConfig();

	Timer6_Init();
	GPIO_Init();

	HAL_TIM_Base_Start(&htimer6);

	while(1)
	{
		while(!TIM6->SR & TIM_SR_UIF); 			//wait here till update event occurs
		HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_12); 	//Toggle the LED
		TIM6->SR = 0;							//Clear the Status Register
	}
	while(1);

	return 0;

}




void SystemClockConfig(void)
{


}

void Error_Handler(void)
{


}

void Timer6_Init(void)
{
	htimer6.Instance=TIM6;
	/*100 ms delay required*/
	htimer6.Init.Prescaler = 0x18;
	htimer6.Init.Period = 64000-1;
	if(HAL_TIM_Base_Init(&htimer6) != HAL_OK)
	{
		Error_Handler();

	}

}

void GPIO_Init(void)
{
	__HAL_RCC_GPIOD_CLK_ENABLE();
	GPIO_InitTypeDef ledgpio;
	ledgpio.Pin = GPIO_PIN_12;
	ledgpio.Mode = GPIO_MODE_OUTPUT_PP;
	ledgpio.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOD,&ledgpio);

}
