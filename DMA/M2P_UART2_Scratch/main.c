#include <stdint.h>
#include "stm32f407xx.h"
#include "string.h"

#define GPIOA_BASE_ADDR			GPIOA





void button_init(void);
void uart_init(void);
void send_data(void);
void dma1_init(void);
void dma1_interrupt_config(void);
void enable_dma_stream6(void);

void HT_Complete_Callback(void);
void FT_Complete_Callback(void);
void TE_Error_Callback(void);
void FE_Error_Callback(void);
void DE_Error_Callback(void);


char data1[]="Hello World\r\n";

int main(void)
{
	
	button_init();
	uart_init();
	//send_data();
	dma1_init();
	dma1_interrupt_config();
	enable_dma_stream6();
	
}

void button_init(void)
{
	//Button is connected to PA0
	GPIO_TypeDef *pgpio;	
	pgpio = GPIOA_BASE_ADDR;
	
	RCC_TypeDef *prcc;
	prcc = RCC;
	
	EXTI_TypeDef *pexti;
	pexti = EXTI;
	
	SYSCFG_TypeDef *psyscfg;
	psyscfg = SYSCFG;
	
	//1. Enable the clock for the GPIOA peripheral
	prcc->AHB1ENR |= 1U;
	
	//2. Keep the GPIO in input mode
	pgpio->MODER &= ~(3<<0);
	
	//3. Enable the Interrupt over the GPIO pin
		pexti->IMR |= 1U;
		
	//4. Enabling the clock to SYSCFG controller
	prcc->APB2ENR |= (1U<<14);
	
	//5. Configuring the SYSCFG EXTI1 register
	psyscfg->EXTICR[1] &= ~(0xF<<0);
	
	//6. Configure the edge detection on the gpio pin
	pexti->FTSR |= 1U;
	
	//7. Enable the IRQ related to the GPIO pin in NVIC of the processor
	NVIC_EnableIRQ(EXTI0_IRQn);
}

void uart_init(void)
{
		RCC_TypeDef *prcc;
		prcc = RCC;
	
		GPIO_TypeDef *pgpio;	
		pgpio = GPIOA_BASE_ADDR;
	
		USART_TypeDef *puart2;
		puart2 = USART2;
	
	//1. Enable the peripheral clock for UART3 peripheral
		prcc->APB1ENR |= (1<<17);
	
	//2. Configure the pins to act as UART3 Tx and Rx
		//PA2--->Tx    PA3--->Rx
		
		//2.1 Enable the clock for GPIOA peripheral
		prcc->AHB1ENR |= 1U;
		
		//2.2 Change the mode of PA2 to Alternate function
		pgpio->MODER &= ~(0x3 << 4);
		pgpio->MODER |= (0x2 << 4);
	
		pgpio->AFR[0] &= ~(0xF<<8);
		pgpio->AFR[0] |= (0x7 <<8);
	
		//2.3 Enable/Disable the pullup resistors if required
		pgpio->PUPDR |= (0x1 << 4);		
		
		//2.4 Change the mode of PA3 to Alternate function
		pgpio->MODER &= ~(0x3 << 6);
		pgpio->MODER |= (0x2 << 6);
	
		pgpio->AFR[0] &= ~(0xF<<12);
		pgpio->AFR[0] |= (0x7 <<12);
	
		//2.5 Enable/Disable the pullup resistors if required
		pgpio->PUPDR |= (0x1 << 6);		
	
	//3. Configure the baud rate
		puart2->BRR = 0x8B;
		
	//4. Configure the data width, parity, no of data bits etc
		//no config required as default is 8-bit word + 1 stop bit
	
	//5. Enable the Tx engine of the UART3 peripheral
		puart2->CR1 |= (1<<3);
	
	//6. Enable the UART peripheral
		puart2->CR1 |= (1<<13);
}




void dma1_init(void)
{
			RCC_TypeDef *prcc;
			prcc = RCC;
		
			DMA_TypeDef *pdma1;
			pdma1 = DMA1;
	
			DMA_Stream_TypeDef *pstream6;
			pstream6 = DMA1_Stream6;
	
			USART_TypeDef *puart2;
			puart2 = USART2;
	
		//1. Enable the peripheral clock for the dma1
			prcc->AHB1ENR |= (1<<21);
	
		//2. Identify the stream which is suitable for your peripheral
			//channel 4 stream 6
	
		//3. Identify the channel number on which UART2_Tx sends peripheral request
			//channel 4
			pstream6->CR &= ~(7<<25);
			pstream6->CR |= (4<<25);
		
		//4. Program the source address
			pstream6->M0AR = (uint32_t)data1;
	
		//5. Program the destination address
			pstream6->PAR = (uint32_t)&(puart2->DR);
	
		//6. Program the number of bytes to send
			uint32_t len = sizeof(data1);
			pstream6->NDTR = len;
		
		//7. Direction of data transfer - M2P, P2M or M2M
			pstream6->CR &= ~(1<<6);
			pstream6->CR |= (1<<6); //Memory to peripheral
			
		//8. Program the source and destination data width
			pstream6->CR &= ~(3<<13);
			pstream6->CR &= ~(1<<11);
			
			//8a. Program memory auto increment
			pstream6->CR |= (1<<10);
		
		//9. Direct mode or FIFO mode
			pstream6->FCR |= (1<<2);  //FIFO mode
		
		//10. Select the FIFO Threshold
			pstream6->FCR |= 0x3;  //full FIFO
		
		//11. Enable the circular mode if required
			
		
		//12. Single transfer or burst transfer
			
		
		//13. Configure the stream priority
		

		
}	
void dma1_interrupt_config(void)
{
			DMA_Stream_TypeDef *pstream6;
			pstream6 = DMA1_Stream6;
			
			//1. Half transfer Interrupt enable
			pstream6->CR |= (1<<3);	
				
			//2. Transfer complete Interrupt enable
			pstream6->CR |= (1<<4);
	
			//3. Transfer error Interrupt
			pstream6->CR |= (1<<2);
	
			//4. FIFO overrun/underrun Interrupt
			pstream6->FCR |= (1<<7);
			
			//5. Direct mode error
			pstream6->CR |= (1<<1);
	
			//6. Enable IRQ in NVIC
			NVIC_EnableIRQ(DMA1_Stream6_IRQn);
		
}


void enable_dma_stream6(void)
{
			DMA_Stream_TypeDef *pstream6;
			pstream6 = DMA1_Stream6;
	
			//14. Enable the stream
			pstream6->CR |= 1U;
	
}


void HT_Complete_Callback(void)
{
		
	
	
}


void FT_Complete_Callback(void)
{
	
	//code to retransmit the code
		USART_TypeDef *puart2;
		puart2 = USART2;
	
		DMA_Stream_TypeDef *pstream6;
		pstream6 = DMA1_Stream6;
		
		puart2->CR3 &= ~(1<<7);
	
		uint32_t len = sizeof(data1);
		pstream6->NDTR = len;
	
		enable_dma_stream6();
	
}
void TE_Error_Callback(void)
{
		while(1);
}

void FE_Error_Callback(void)
{
		while(1);
	
}

void DE_Error_Callback(void)
{
	
	while(1);
}



void send_data(void)
{

	
		USART_TypeDef *puart2;
		puart2 = USART2;
	
		
	//send byte by byte
		for(int i=0;i<strlen(data1);i++)
		{
				//Make sure the Data Register is empty
				while(!(puart2->SR & (1<<7))	);		
			
				//Put data into Data Register
				puart2->DR = data1[i];
		}
	
}

