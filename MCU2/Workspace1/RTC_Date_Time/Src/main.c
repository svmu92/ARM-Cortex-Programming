#include "main.h"



void SystemClockConfig(void);
void Error_Handler(void);
void GPIO_Init(void);
void UART2_Init(void);
void RTC_Init(void);
void RTC_CalendarConfig(void);
void printmsg(char*,...);


UART_HandleTypeDef huart2;
RTC_HandleTypeDef hrtc;

int main(void)
{
	HAL_Init();
	//SystemClockConfig();


	//Timer6_Init();
	GPIO_Init();
	UART2_Init();

	RTC_Init();
	RTC_CalendarConfig();

	while(1){
	}

	return 0;

}

void printmsg(char *format,...)
 {

	char str[80];

	/*Extract the the argument list using VA apis */
	va_list args;
	va_start(args, format);
	vsprintf(str, format,args);
	HAL_UART_Transmit(&huart2,(uint8_t *)str, strlen(str),HAL_MAX_DELAY);
	va_end(args);

 }


void SystemClockConfig(void)
{


}

void Error_Handler(void)
{
	while(1);

}



void GPIO_Init(void)
{
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	//Disable the clocks when in sleep mode
	__HAL_RCC_GPIOD_CLK_SLEEP_DISABLE();


	GPIO_InitTypeDef ledgpio,buttongpio;
	ledgpio.Pin = GPIO_PIN_12;
	ledgpio.Mode = GPIO_MODE_OUTPUT_PP;
	ledgpio.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOD,&ledgpio);

	buttongpio.Pin = GPIO_PIN_0;
	buttongpio.Mode = GPIO_MODE_IT_FALLING;
	ledgpio.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA,&buttongpio);

	HAL_NVIC_SetPriority(EXTI0_IRQn,15,0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);


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

void RTC_Init(void)
{

	hrtc.Instance = RTC;
	hrtc.Init.HourFormat = RTC_HOURFORMAT_12;
	hrtc.Init.AsynchPrediv = 127;
	hrtc.Init.SynchPrediv = 249;
	hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
	hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_LOW;
	hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_PUSHPULL;

	if(HAL_RTC_Init(&hrtc) != HAL_OK)
	{
		Error_Handler();
	}
}


void RTC_CalendarConfig(void)
{
	RTC_TimeTypeDef RTC_TimeInit;
	RTC_DateTypeDef RTC_DateInit;
	//this function does RTC Calendar Config
	//Lets configure the calendar for Time : 12:11:10 PM Date : 12 june 2018 TUESDAY

	RTC_TimeInit.Hours = 12;
	RTC_TimeInit.Minutes = 11;
	RTC_TimeInit.Seconds = 10;
	RTC_TimeInit.TimeFormat = RTC_HOURFORMAT12_PM;
	HAL_RTC_SetTime(&hrtc, &RTC_TimeInit,RTC_FORMAT_BIN);


	RTC_DateInit.Date = 12;
	RTC_DateInit.Month = RTC_MONTH_JUNE;
	RTC_DateInit.Year = 18;
	RTC_DateInit.WeekDay = RTC_WEEKDAY_TUESDAY;

	HAL_RTC_SetDate(&hrtc,&RTC_DateInit,RTC_FORMAT_BIN);

}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	 RTC_TimeTypeDef RTC_TimeRead;
	 RTC_DateTypeDef RTC_DateRead;

	 HAL_RTC_GetTime(&hrtc,&RTC_TimeRead,RTC_FORMAT_BIN);

	 HAL_RTC_GetDate(&hrtc,&RTC_DateRead,RTC_FORMAT_BIN);

	 printmsg("Current Time is : %02d:%02d:%02d\r\n",RTC_TimeRead.Hours,\
			 RTC_TimeRead.Minutes,RTC_TimeRead.Seconds);
	 printmsg("Current Date is : %02d-%2d-%2d  <%s> \r\n",RTC_DateRead.Month,RTC_DateRead.Date,\
			 RTC_DateRead.Year,getDayofweek(RTC_DateRead.WeekDay));
}

