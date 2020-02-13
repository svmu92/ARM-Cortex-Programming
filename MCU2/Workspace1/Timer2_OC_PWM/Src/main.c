/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <string.h>
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */



TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

volatile uint32_t pulse1_value = 25000;
volatile uint32_t pulse2_value = 12500;
volatile uint32_t pulse3_value = 6250;
volatile uint32_t pulse4_value = 3125;
volatile uint32_t ccr_value;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
//void SystemClock_ConfigHSE(uint8_t clock_freq);
void GPIO_Init(void);
void Timer2_Init(void);
void UART2_Init(void);
void Error_Handler(void);
void SystemClockConfig(uint8_t clockFreq);



/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{


  HAL_Init();


  SystemClockConfig(SYS_CLOCK_FREQ_50_MHz);

//  UART2_Init();
  GPIO_Init();
  Timer2_Init();

  if(HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1) != HAL_OK)
  {
	  Error_Handler();
  }

  if(HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2) != HAL_OK)
  {
	  Error_Handler();
  }

  if(HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3) != HAL_OK)
  {
	  Error_Handler();
  }

  if(HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_4) != HAL_OK)
  {
	  Error_Handler();
  }

  while (1);
  return 0;
}




void SystemClockConfig(uint8_t clockFreq)
{
	RCC_OscInitTypeDef osc_init;
	RCC_ClkInitTypeDef clk_init;

	uint32_t FlashLatency = 0;

	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	osc_init.HSIState = RCC_HSI_ON;
	osc_init.HSICalibrationValue = 16;
	osc_init.PLL.PLLState = RCC_PLL_ON;
	osc_init.PLL.PLLSource = RCC_PLLSOURCE_HSI;


	switch(clockFreq)
	{
	case SYS_CLOCK_FREQ_50_MHz	:	osc_init.PLL.PLLM 		= 16;
									osc_init.PLL.PLLN 		= 100;
									osc_init.PLL.PLLP 		= 2;
									clk_init.ClockType 		= RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
									clk_init.SYSCLKSource 	= RCC_SYSCLKSOURCE_PLLCLK;
									clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
									clk_init.APB2CLKDivider = RCC_HCLK_DIV2;
									clk_init.AHBCLKDivider 	= RCC_SYSCLK_DIV1;
									FlashLatency			= FLASH_ACR_LATENCY_1WS;
									break;
	case SYS_CLOCK_FREQ_84_MHz	:	osc_init.PLL.PLLM = 16;
									osc_init.PLL.PLLN = 168;
									osc_init.PLL.PLLP = 2;
									clk_init.ClockType 		= RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
									clk_init.SYSCLKSource 	= RCC_SYSCLKSOURCE_PLLCLK;
									clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
									clk_init.APB2CLKDivider = RCC_HCLK_DIV2;
									clk_init.AHBCLKDivider 	= RCC_SYSCLK_DIV1;
									FlashLatency			= FLASH_ACR_LATENCY_2WS;
									break;
	case SYS_CLOCK_FREQ_120_MHz	:	osc_init.PLL.PLLM = 16;
									osc_init.PLL.PLLN = 240;
									osc_init.PLL.PLLP = 2;
									clk_init.ClockType 		= RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
									clk_init.SYSCLKSource 	= RCC_SYSCLKSOURCE_PLLCLK;
									clk_init.APB1CLKDivider = RCC_HCLK_DIV4;
									clk_init.APB2CLKDivider = RCC_HCLK_DIV2;
									clk_init.AHBCLKDivider 	= RCC_SYSCLK_DIV1;
									FlashLatency			= FLASH_ACR_LATENCY_3WS;
									break;
	case SYS_CLOCK_FREQ_180_MHz	:	osc_init.PLL.PLLM = 16;
									osc_init.PLL.PLLN = 360;
									osc_init.PLL.PLLP = 2;
									clk_init.ClockType 		= RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
									clk_init.SYSCLKSource 	= RCC_SYSCLKSOURCE_PLLCLK;
									clk_init.APB1CLKDivider = RCC_HCLK_DIV4;
									clk_init.APB2CLKDivider = RCC_HCLK_DIV2;
									clk_init.AHBCLKDivider 	= RCC_SYSCLK_DIV1;
									FlashLatency			= FLASH_ACR_LATENCY_5WS;
									break;
	default						:	return;
	}

	osc_init.PLL.PLLQ = 2;
	//osc_init.PLL.P = 2;

	if(HAL_RCC_OscConfig(&osc_init) != HAL_OK)
	{
		Error_Handler();
	}
	if(HAL_RCC_ClockConfig(&clk_init,FlashLatency)!= HAL_OK)
	{
		Error_Handler();
	}

	//SysTick Configuration
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

}

/**
  * @brief System Clock Configuration
  * @retval None*/


 /*USER CODE BEGIN 4 */

void GPIO_Init(void)
{
	__HAL_RCC_GPIOD_CLK_ENABLE();
	GPIO_InitTypeDef ledgpio;
	ledgpio.Pin = GPIO_PIN_12;
	ledgpio.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(GPIOD,&ledgpio);

}


void Timer2_Init(void)
{
	TIM_OC_InitTypeDef tim2OC;

	htim2.Instance = TIM2;
	htim2.Init.Period = 10000-1;
	htim2.Init.Prescaler = 4;
	if(HAL_TIM_PWM_Init(&htim2)!=HAL_OK)
	{
		Error_Handler();
	}

	memset(&tim2OC,0,sizeof(tim2OC));
	tim2OC.OCMode = TIM_OCMODE_PWM1;

	// OCREF---->OC Output (Inverted or Non-Inverted from OCREF)
	tim2OC.OCPolarity = TIM_OCPOLARITY_HIGH; 	//Non-Inverted

	/* Channel 1 ------- 25% */
	tim2OC.Pulse = (htim2.Init.Period/25)*100;
	if(HAL_TIM_PWM_ConfigChannel(&htim2,&tim2OC, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}

	/* Channel 2 ------- 45% */
	tim2OC.Pulse = (htim2.Init.Period/45)*100;
	if(HAL_TIM_PWM_ConfigChannel(&htim2,&tim2OC, TIM_CHANNEL_2) != HAL_OK)
	{
		Error_Handler();
	}

	/* Channel 3 ------- 75% */
	tim2OC.Pulse = (htim2.Init.Period/75)*100;
	if(HAL_TIM_PWM_ConfigChannel(&htim2,&tim2OC, TIM_CHANNEL_3) != HAL_OK)
	{
		Error_Handler();
	}

	/* Channel 4 ------- 90% */
	tim2OC.Pulse = (htim2.Init.Period/90)*100;
	if(HAL_TIM_PWM_ConfigChannel(&htim2,&tim2OC, TIM_CHANNEL_4) != HAL_OK)
	{
		Error_Handler();
	}


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




/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
	while(1);
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
