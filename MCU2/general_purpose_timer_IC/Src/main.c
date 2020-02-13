#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "main.h"
#include <string.h>



void SystemClockConfig(uint8_t);
void Error_Handler(void);
void GPIO_Init(void);
void Timer2_Init(void);
void LSE_Configuration(void);

uint32_t input_capture[2];
uint32_t capture_difference;
uint8_t count = 1;
uint8_t is_capture_done = FALSE;
char user_msg[100];
double timer2_cnt_freq;
double timer2_cnt_res;
double user_signal_timer_period;
double user_signal_freq;

TIM_HandleTypeDef htimer2;
//UART_HandleTypeDef huart2;

int main(void)
{
	HAL_Init();
	SystemClockConfig(SYS_CLOCK_FREQ_50_MHz);


	GPIO_Init();

	Timer2_Init();

	LSE_Configuration();
	timer2_cnt_freq = (HAL_RCC_GetPCLK1Freq()*2)/htimer2.Init.Prescaler;
	timer2_cnt_res = 1/timer2_cnt_freq;

	while(1)
	{
		if(is_capture_done == TRUE)
		{
			if (input_capture[1] > input_capture[0])
				capture_difference = input_capture[1] - input_capture[0];
			else
				capture_difference = input_capture[0] - input_capture[1];
		}

		timer2_cnt_freq = (HAL_RCC_GetPCLK1Freq()*2)/(htimer2.Init.Prescaler+1);
		timer2_cnt_res = 1/timer2_cnt_freq;
		user_signal_timer_period = capture_difference * timer2_cnt_res;\
		user_signal_freq = 1/user_signal_timer_period;

		sprintf(user_msg,"Frequency of the signal applied = %lf\r\n",user_signal_timer_period);
		is_capture_done = TRUE;
	}

	return 0;

}


void SystemClockConfig(uint8_t clockFreq)
{
	RCC_OscInitTypeDef osc_init;
	RCC_ClkInitTypeDef clk_init;

	uint32_t FlashLatency = 0;

	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSE;
	osc_init.HSIState = RCC_HSI_ON;
	osc_init.LSEState = RCC_LSE_ON;
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


void LSE_Configuration(void)
{
/*	RCC_OscInitTypeDef osc_init;

	osc_init.OscillatorType = RCC_OSCILLATORTYPE_LSE;
	osc_init.LSEState = RCC_LSE_ON;

	if(HAL_RCC_OscConfig(&osc_init) != HAL_OK)
	{
		Error_Handler();
	}*/

	// Use the MCO pins to output the LSE clock
	HAL_RCC_MCOConfig(RCC_MCO1,RCC_MCO1SOURCE_LSE,RCC_MCODIV_1);


}


void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(! is_capture_done)
	{

	if(count==1)
	{
		input_capture[0] = __HAL_TIM_GET_COMPARE(htim, TIM_CHANNEL_1);
		count++;
	}
	else if(count==2)
	{
		input_capture[1] = __HAL_TIM_GET_COMPARE(htim, TIM_CHANNEL_1);
		is_capture_done = TRUE;
		count=1;
	}
	}

}

void Error_Handler(void)
{

	while(1);
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


void Timer2_Init(void)
{
	TIM_IC_InitTypeDef timer2IC_Config;

	htimer2.Instance = TIM2;
	htimer2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htimer2.Init.Period = 0xFFFFFFFF;
	htimer2.Init.Prescaler = 0x01;
	if(HAL_TIM_IC_Init(&htimer2) != HAL_OK)
	{
		Error_Handler();
	}

	timer2IC_Config.ICFilter = 0;
	timer2IC_Config.ICPrescaler = TIM_ICPSC_DIV1;
	timer2IC_Config.ICPolarity = TIM_ICPOLARITY_RISING;
	timer2IC_Config.ICSelection = TIM_ICSELECTION_DIRECTTI;

	if(HAL_TIM_IC_ConfigChannel(&htimer2,&timer2IC_Config,TIM_CHANNEL_1) != HAL_OK)
		{
			Error_Handler();
		}
}
