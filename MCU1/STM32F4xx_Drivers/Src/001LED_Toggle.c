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

void setup(void);
void delay1(void);

int main()
{
	setup();
	while(1)
	{
		delay1();
		GPIO_ToggleOutputPin(GPIOD,GPIO_PIN_NO_12);
	}
	return 0;
}

void setup(void)
{
	GPIO_Handle_t GpioLed;

	GpioLed.pGPIOx = GPIOD;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOD,ENABLE);
	GPIO_Init(&GpioLed);
}

void delay1(void)
{
	uint32_t i=0;
	for(i=0;i<500000;i++);
}
