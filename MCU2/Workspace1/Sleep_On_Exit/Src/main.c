#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "main.h"
#include <string.h>


void SystemClockConfig(void);
void Error_Handler(void);
void Timer6_Init(void);
void GPIO_Init(void);
void UART2_Init(void);


TIM_HandleTypeDef htimer6;
UART_HandleTypeDef huart2;
extern char msg[30];

int main(void)
{
	HAL_Init();
	SystemClockConfig();


	Timer6_Init();
	GPIO_Init();
	UART2_Init();

	SCB->SCR |= (1<<1);
	//HAL_PWR_EnableSleepOnExit();

	TIM6->SR = 0;
	HAL_TIM_Base_Start_IT(&htimer6);


	while(1);

	return 0;

}




void SystemClockConfig(void)
{


}

void Error_Handler(void)
{
	while(1);

}

void Timer6_Init(void)
{
	htimer6.Instance=TIM6;
	/*100 ms delay required*/
	htimer6.Init.Prescaler = 4999;
	htimer6.Init.Period = 31;
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

void UART2_Init(void)
{
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	if ( HAL_UART_Init(&huart2) != HAL_OK )
	{
		//There is a problem
		Error_Handler();
	}

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

	HAL_UART_Transmit(&huart2,(uint8_t*)msg,(uint16_t)strlen(msg),HAL_MAX_DELAY);
	HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_12);

}

