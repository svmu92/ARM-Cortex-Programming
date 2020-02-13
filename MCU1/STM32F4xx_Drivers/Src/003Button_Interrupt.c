/*
 * 003Button_Interrupt.c
 *
 *  Created on: 30-Dec-2019
 *      Author: Sreenath V
 */
/*
 * Button_LED.c
 *
 *  Created on: 29-Dec-2019
 *      Author: Sreenath V
 */

/*
 * 001LED_Toggle.c
 *
 *  Created on: 29-Dec-2019
 *      Author: Sreenath V
 */
#include "stm32f407xx.h"
#include "stm32f407xx_gpio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HIGH 			1
#define LOW				0
#define BTN_PRESSED 	LOW
#define BTN_NOTPRESSED	HIGH

void setup(void);
void delay1(void);

int main()
{
	setup();
	while(1)
	{
//		if(GPIO_ReadFromInputPin(GPIOD,GPIO_PIN_NO_1)==BTN_PRESSED)
//		{
//			GPIO_ToggleOutputPin(GPIOD,GPIO_PIN_NO_12);
//			delay1();
//		}
	}
	return 0;
}

void setup(void)
{
	GPIO_Handle_t GpioLed;
	GPIO_Handle_t GpioButton;

	memset(&GpioButton,0,sizeof(GpioButton));
	memset(&GpioLed,0,sizeof(GpioLed));

	GpioLed.pGPIOx = GPIOD;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOD,ENABLE);
	GPIO_Init(&GpioLed);


	GpioButton.pGPIOx = GPIOD;
	GpioButton.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_9;
	GpioButton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	GpioButton.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioButton.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;

	GPIO_PeriClockControl(GPIOD,ENABLE);
	GPIO_Init(&GpioButton);

	GPIO_IRQConfig(IRQ_NO_EXTI9_5,ENABLE);
	GPIO_IRQPriorityConfig(IRQ_NO_EXTI9_5,NVIC_IRQ_PRIO15);
}

void delay1(void)
{
	uint32_t i=0;
	for(i=0;i<50000;i++);
}

//void EXTI1_IRQHandler(void)
//{
//	GPIO_IRQHandling(GPIO_PIN_NO_5);
//	GPIO_ToggleOutputPin(GPIOD,GPIO_PIN_NO_12);
//	delay1();
//}

void EXTI9_5_IRQHandler(void)
{
	delay1();
	GPIO_IRQHandling(GPIO_PIN_NO_9);
	GPIO_ToggleOutputPin(GPIOD,GPIO_PIN_NO_12);
}
