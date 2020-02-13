/*
 * stm32f407xx_spi.c
 *
 *  Created on: 30-Dec-2019
 *      Author: Sreenath V
 */
#include "stm32f407xx_spi.h"
#include <stddef.h>

static void spi_ovr_err_interrupt_handle(SPI_Handle_t *pSPIHandle);
static void spi_rxne_interrupt_handle(SPI_Handle_t *pSPIHandle);
static void spi_txe_interrupt_handle(SPI_Handle_t *pSPIHandle);

void SPI_PeriClockControl(SPI_RegDef_t *pSPIx,uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_EN();
		}
		else if(pSPIx == SPI2)
		{
			SPI2_PCLK_EN();
		}
		else if(pSPIx == SPI3)
		{
			SPI3_PCLK_EN();
		}
	}else
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_DI();
		}
		else if(pSPIx == SPI2)
		{
			SPI2_PCLK_DI();
		}
		else if(pSPIx == SPI3)
		{
			SPI3_PCLK_DI();
		}
	}

}


void SPI_Init(SPI_Handle_t *pSPIHandle)
{
	SPI_PeriClockControl(SPI2,ENABLE);
	uint32_t tempreg=0;

	tempreg |= (pSPIHandle->SPIConfig.SPI_DeviceMode << SPI_CR1_MSTR );

	if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD)
	{
		tempreg &= ~(1<<SPI_CR1_BIDIMODE);
	}
	else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD)
	{
		tempreg |= (1<<SPI_CR1_BIDIMODE);
	}
	else
	{
		tempreg &= ~(1<<SPI_CR1_BIDIMODE);
		tempreg |= (1<<SPI_CR1_RXONLY);
	}

	tempreg |= (pSPIHandle->SPIConfig.SPI_CPOL<<SPI_CR1_CPOL);
	tempreg |= (pSPIHandle->SPIConfig.SPI_CPHA<<SPI_CR1_CPHA);
	tempreg |= (pSPIHandle->SPIConfig.SPI_DFF<<SPI_CR1_DFF );
	tempreg |= (pSPIHandle->SPIConfig.SPI_SSM<<SPI_CR1_SSM);
	tempreg |= (pSPIHandle->SPIConfig.SPI_SclkSpeed<<SPI_CR1_BR);

	pSPIHandle->pSPIx->CR1 = tempreg;
}


void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		pSPIx->CR1 |= (1<<SPI_CR1_SSI);
	}
	else
		pSPIx->CR1 &= ~(1<<SPI_CR1_SSI);

}

void SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		pSPIx->CR2 |= (1<<SPI_CR2_SSOE);
	}
	else
		pSPIx->CR2 &= ~(1<<SPI_CR2_SSOE);
}


void SPI_DeInit(SPI_RegDef_t *pSPIx)
{
	if(pSPIx == SPI1)
	{
		SPI1_REG_RESET();
	}else if (pSPIx == SPI2)
	{
		SPI2_REG_RESET();
	}else if (pSPIx == SPI3)
	{
		SPI3_REG_RESET();
	}
}


void SPI_SendData(SPI_RegDef_t *pSPIx,uint8_t *pTxBuffer, uint32_t length)
{

	while(length>0)
	{
		while(SPI_GetStatusFlag(pSPIx,SPI_TXE_FLAG)==FLAG_RESET);

		if(pSPIx->CR1 & (1<<SPI_CR1_DFF))
		{
			//16 bit
			pSPIx->DR =   *((uint16_t*)pTxBuffer);
			length--;
			length--;
			(uint16_t*)pTxBuffer++;
		}
		else
		{
			//8 bit
			pSPIx->DR=*pTxBuffer;
			length--;
			pTxBuffer++;
		}
	}
}

void SPI_ReceiveData(SPI_RegDef_t *pSPIx,uint8_t *pRxBuffer, uint32_t length)
{
//	uint8_t buffer[length];
	while(length>0)
	{
		while(SPI_GetStatusFlag(pSPIx,SPI_RXNE_FLAG)==FLAG_RESET);

		if(pSPIx->CR1 & (1<<SPI_CR1_DFF))
		{
			//16 bit
			*((uint16_t*)pRxBuffer)=pSPIx->DR;
			length--;
			length--;
			(uint16_t*)pRxBuffer++;
		}
		else
		{
			//8 bit
			*pRxBuffer=pSPIx->DR;
			length--;
			pRxBuffer++;
		}
	}
}

uint8_t SPI_GetStatusFlag(SPI_RegDef_t *pSPIx, uint32_t Flagname)
{
	if(pSPIx->SR & Flagname)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}

void SPI_PeripheralControl(SPI_RegDef_t *pSPIx,uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		pSPIx->CR1 |= (1<<SPI_CR1_SPE);
	}
	else
		pSPIx->CR1 &= ~(1<<SPI_CR1_SPE);
}

void SPI_IRQConfig(uint8_t IRQNumber,uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(IRQNumber <32)
		{
			//ISER0 register
			*NVIC_ISER0 |= (1<<IRQNumber);

		}else if(IRQNumber >= 32 && IRQNumber < 64)
		{
			//ISER1 register
			*NVIC_ISER1 |= (1<<(IRQNumber%32));

		}
	}
	else
	{
		if(IRQNumber <32)
		{
			//ISER0 register
			*NVIC_ICER0 |= (1<<IRQNumber);

		}else if(IRQNumber >= 32 && IRQNumber < 64)
		{
			//ISER1 register
			*NVIC_ICER1 |= (1<<(IRQNumber%32));

		}
	}
}

void SPI_IRQPriorityConfig(uint8_t IRQNumber,uint32_t IRQPriority)
{
	uint8_t iprx = IRQNumber/4;
	uint8_t iprsection = IRQNumber%4;
	uint8_t shift_amount = (8*iprsection) + (8 - NO_OF_PR_IMPLEMENTED);

	*(NVIC_PR_BASE_ADDR + iprx) |= (IRQPriority << shift_amount );
}


uint8_t SPI_SendData_IT(SPI_Handle_t *pSPIHandle,uint8_t *pTxBuffer, uint32_t length)
{
	uint8_t state=pSPIHandle->TxState;

	if(state != SPI_BUSY_IN_TX)
	{
		pSPIHandle->pTxBuffer = pTxBuffer;
		pSPIHandle->TxLen = length;

		pSPIHandle->TxState = SPI_BUSY_IN_TX;

		pSPIHandle->pSPIx->CR2 |= (1<<SPI_CR2_TXEIE);
	}

	return state;
}

uint8_t SPI_ReceiveData_IT(SPI_Handle_t *pSPIHandle,uint8_t *pRxBuffer, uint32_t length)
{
	uint8_t state=pSPIHandle->RxState;

	if(state != SPI_BUSY_IN_RX)
	{
		pSPIHandle->pRxBuffer = pRxBuffer;
		pSPIHandle->RxLen = length;

		pSPIHandle->RxState = SPI_BUSY_IN_RX;

		pSPIHandle->pSPIx->CR2 |= (1<<SPI_CR2_RXNEIE);
	}

	return state;
}

void SPI_IRQHandling(SPI_Handle_t *pSPIHandle)
{
	uint8_t temp1, temp2;

	//check for TXE Flag
	temp1=pSPIHandle->pSPIx->SR & (1<<SPI_TXE_FLAG);
	temp2=pSPIHandle->pSPIx->CR2 & (1<<SPI_CR2_TXEIE);

	if(temp1 & temp2)
	{
		//Handle TXE
		spi_txe_interrupt_handle(pSPIHandle);
	}

	//check for RXNE Flag
	temp1=pSPIHandle->pSPIx->SR & (1<<SPI_RXNE_FLAG);
	temp2=pSPIHandle->pSPIx->CR2 & (1<<SPI_CR2_RXNEIE);

	if(temp1 & temp2)
	{
		//Handle TXE
		spi_rxne_interrupt_handle(pSPIHandle);
	}

	//check for OVR Flag
	temp1=pSPIHandle->pSPIx->SR & (1<<SPI_SR_OVR);
	temp2=pSPIHandle->pSPIx->CR2 & (1<<SPI_CR2_ERRIE);

	if(temp1 & temp2)
	{
		//Handle TXE
		spi_ovr_err_interrupt_handle(pSPIHandle);
	}

}

/*
 * Helper Function Implementations
 */

static void spi_ovr_err_interrupt_handle(SPI_Handle_t *pSPIHandle)
{
	uint8_t temp;
	//1. clear the ovr flag
	if(pSPIHandle->TxState != SPI_BUSY_IN_TX)
	{
		temp = pSPIHandle->pSPIx->DR;
		temp = pSPIHandle->pSPIx->SR;
	}
	(void)temp;
	//2. inform the application
	SPI_ApplicationEventCallback(pSPIHandle,SPI_EVENT_OVR_ERR);
}

static void spi_rxne_interrupt_handle(SPI_Handle_t *pSPIHandle)
{
	if(pSPIHandle->pSPIx->CR1 & (1<<SPI_CR1_DFF))
	{
		//16 bit
		*((uint16_t*)pSPIHandle->pRxBuffer)=pSPIHandle->pSPIx->DR;
		pSPIHandle->RxLen--;
		pSPIHandle->RxLen--;
		(uint16_t*)pSPIHandle->pRxBuffer++;
	}
	else
	{
		//8 bit
		*(pSPIHandle->pRxBuffer)=pSPIHandle->pSPIx->DR;
		pSPIHandle->RxLen--;
		pSPIHandle->pRxBuffer++;
	}
	if(!pSPIHandle->RxLen)
	{
		SPI_CloseReception(pSPIHandle);
		SPI_ApplicationEventCallback(pSPIHandle,SPI_EVENT_RX_CMPLT);
	}

}
static void spi_txe_interrupt_handle(SPI_Handle_t *pSPIHandle)
{
	if(pSPIHandle->pSPIx->CR1 & (1<<SPI_CR1_DFF))
	{
		//16 bit
		pSPIHandle->pSPIx->DR =   *((uint16_t*)(pSPIHandle->pTxBuffer));
		pSPIHandle->TxLen--;
		pSPIHandle->TxLen--;
		(uint16_t*)pSPIHandle->pTxBuffer++;
	}
	else
	{
		//8 bit
		pSPIHandle->pSPIx->DR=*(pSPIHandle->pTxBuffer);
		pSPIHandle->TxLen--;
		(uint16_t*)pSPIHandle->pTxBuffer++;
	}

	if(!pSPIHandle->TxLen)
	{
		SPI_CloseTransmisson(pSPIHandle);
		SPI_ApplicationEventCallback(pSPIHandle,SPI_EVENT_TX_CMPLT);
	}
}


void SPI_CloseTransmisson(SPI_Handle_t *pSPIHandle)
{
	pSPIHandle->pSPIx->CR2 &= ~( 1 << SPI_CR2_TXEIE);
	pSPIHandle->pTxBuffer = NULL;
	pSPIHandle->TxLen = 0;
	pSPIHandle->TxState = SPI_READY;

}

void SPI_CloseReception(SPI_Handle_t *pSPIHandle)
{
	pSPIHandle->pSPIx->CR2 &= ~( 1 << SPI_CR2_RXNEIE);
	pSPIHandle->pRxBuffer = NULL;
	pSPIHandle->RxLen = 0;
	pSPIHandle->RxState = SPI_READY;

}



void SPI_ClearOVRFlag(SPI_RegDef_t *pSPIx)
{
	uint8_t temp;
	temp = pSPIx->DR;
	temp = pSPIx->SR;
	(void)temp;

}



__weak void SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle,uint8_t AppEv)
{

	//This is a weak implementation . the user application may override this function.
}
