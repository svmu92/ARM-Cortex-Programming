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
		if(GPIO_ReadFromInputPin(GPIOB,GPIO_PIN_NO_1)==BTN_PRESSED)
		{
			GPIO_ToggleOutputPin(GPIOD,GPIO_PIN_NO_11);
			delay1();
		}
	}
	return 0;
}

void setup(void)
{
	GPIO_Handle_t GpioLed;
	GPIO_Handle_t GpioButton;

	GpioLed.pGPIOx = GPIOD;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_11;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOD,ENABLE);
	GPIO_Init(&GpioLed);


	GpioButton.pGPIOx = GPIOB;
	GpioButton.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_1;
	GpioButton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GpioButton.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioButton.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOB,ENABLE);
	GPIO_Init(&GpioButton);
}

void delay1(void)
{
	uint32_t i=0;
	for(i=0;i<50000;i++);
}

