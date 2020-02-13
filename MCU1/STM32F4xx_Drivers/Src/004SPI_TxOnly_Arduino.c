/*
 * 004SPI_TxOnly_Arduino.c
 *
 *  Created on: 30-Dec-2019
 *      Author: Sreenath V
 */



#include "stm32f407xx.h"
#include "stm32f407xx_spi.h"
#include "stm32f407xx_gpio.h"
#include <string.h>
#include <stdlib.h>

#define BTN_PRESSED 0

void SPI2_GPIOInits(void);
void SPI_Inits(void);

void delay1(void);

int main(void)
{
	char user_data[]="Hello World";

	SPI2_GPIOInits();

	SPI_Inits();

	//SPI_SSIConfig(SPI2,DISABLE);

	SPI_SSOEConfig(SPI2,ENABLE);



	while(1)
	{
		while(!GPIO_ReadFromInputPin(GPIOA,GPIO_PIN_NO_0));

		delay1();

		uint8_t datalen=strlen(user_data);

		SPI_PeripheralControl(SPI2,ENABLE);

		SPI_SendData(SPI2,&datalen,1);

		SPI_SendData(SPI2,(uint8_t*)user_data,strlen(user_data));

		while( SPI_GetStatusFlag(SPI2,SPI_BUSY_FLAG) );

			//Disable the SPI2 peripheral
		SPI_PeripheralControl(SPI2,DISABLE);
	}
//	while(1);
	return 0;
}

void SPI2_GPIOInits(void)
{
	GPIO_Handle_t GpioSPI;
	GPIO_Handle_t GpioButton;
	GPIO_PeriClockControl(GPIOB,ENABLE);

	GpioSPI.pGPIOx = GPIOB;
	GpioSPI.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	GpioSPI.GPIO_PinConfig.GPIO_PinAltFuncMode = 5;
	GpioSPI.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioSPI.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioSPI.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;



	GpioSPI.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GPIO_Init(&GpioSPI);
	GpioSPI.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIO_Init(&GpioSPI);
//	GpioSPI.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
//	GPIO_Init(&GpioSPI);
	GpioSPI.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	GPIO_Init(&GpioSPI);

	GPIO_PeriClockControl(GPIOA,ENABLE);
	GpioButton.pGPIOx = GPIOA;
	GpioButton.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	GpioButton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GpioButton.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioButton.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;


	GPIO_Init(&GpioButton);
}

void SPI_Inits(void)
{
	SPI_Handle_t SPI2Handle;
	SPI2Handle.pSPIx = SPI2;
	SPI2Handle.SPIConfig.SPI_BusConfig =SPI_BUS_CONFIG_FD;
	SPI2Handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2Handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV8;
	SPI2Handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
	SPI2Handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2Handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI2Handle.SPIConfig.SPI_SSM = SPI_SSM_DI;

	SPI_Init(&SPI2Handle);

}


void delay1(void)
{
	uint32_t i=0;
	for(i=0;i<500000;i++);
}

