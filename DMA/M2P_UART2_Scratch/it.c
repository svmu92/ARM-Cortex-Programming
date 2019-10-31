/* it.c  */

#include "stm32f407xx.h"

extern void HT_Complete_Callback(void);
extern void FT_Complete_Callback(void);
extern void TE_Error_Callback(void);
extern void FE_Error_Callback(void);
extern void DE_Error_Callback(void);


#define is_it_HT() (DMA1->HISR&(1<<20))
#define is_it_FT() (DMA1->HISR&(1<<21))
#define is_it_TE() (DMA1->HISR&(1<<19))
#define is_it_FO() (DMA1->HISR&(1<<16))
#define is_it_DE() (DMA1->HISR&(1<<18))

void EXTI0_IRQHandler(void)	
{
	
		USART_TypeDef *puart2;
		puart2 = USART2;
		
		//UART sends request to DMA for transfer
		puart2->CR3 |= (1<<7);
	
		EXTI_TypeDef *pexti;
		pexti = EXTI;
	//clear_exti_pending_bit
		if (pexti->PR & 1U)
		{
			pexti->PR |= 1U;
		}
	
}



void DMA1_Stream6_IRQHandler(void)
{
	
		//Half Transfer
		if(is_it_HT())
		{
			DMA1->HIFCR |= (1<<20);
			HT_Complete_Callback();
		}
	
		//Full Transfer
		if(is_it_FT())
		{
			DMA1->HIFCR |= (1<<21);
			FT_Complete_Callback();
		}
		
		//Transfer Error
		if(is_it_TE())
		{
			DMA1->HIFCR |= (1<<19);
			TE_Error_Callback();
		}
		
		//FIFO Overrun
		if(is_it_FO())
		{
			DMA1->HIFCR |= (1<<16);
			FE_Error_Callback();
		}
		
		//DMA Error
		if(is_it_DE())
		{
			DMA1->HIFCR |= (1<<19);
			DE_Error_Callback();
		}
	
}

