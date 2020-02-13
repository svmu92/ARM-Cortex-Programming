/*
 * main.c
 *
 *  Created on: 13-Apr-2019
 *      Author: Sreenath V
 */


#include "stm32f4xx_hal.h"
#include "string.h"

#define TRUE 1
#define FALSE 0


void SystemClockConfig(void);
void UART2_Init(void);

void Error_Handler();
uint8_t convert_to_capital(uint8_t);

UART_HandleTypeDef huart2;

uint8_t data_buffer[100];
uint8_t recv_data;
uint32_t count=0;
uint8_t reception_complete;
char *user_data = "Hello\r\n";


int main(void)
{
	HAL_Init();
//HAL_Init()

	SystemClockConfig();


	UART2_Init();

	uint32_t len_of_data = strlen(user_data);
	if(HAL_UART_Transmit(&huart2,(uint8_t *)user_data,len_of_data,HAL_MAX_DELAY) != HAL_OK)
		{

		//Data transmission failure
		Error_Handler();
		}


	while(reception_complete != TRUE)
		HAL_UART_Receive_IT(&huart2,&recv_data,1);

	while(1);
	return 0;
}


void SystemClockConfig(void)
{


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
	if(HAL_UART_Init(&huart2) != HAL_OK )
		{
			Error_Handler();
		}

}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(recv_data == '\r')
	{
		reception_complete = TRUE;
		data_buffer [count++] = '\r';
		HAL_UART_Transmit(&huart2,data_buffer,count,HAL_MAX_DELAY);
	}
	else
		data_buffer[count++] = recv_data;

}

uint8_t convert_to_capital(uint8_t x)
{
	if(x >= 'a' && x <= 'z')
		x=x-('a'-'A');
	return x;
}


void Error_Handler()
{

	//blink RED LED
}

