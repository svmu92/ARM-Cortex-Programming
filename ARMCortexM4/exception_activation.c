#include "stm32f407xx.h"


void MemManage_Handler (void)
{
	
	
}

void BusFault_Handler (void)
{
	
	
}

void UsageFault_Handler (void)
{
	
	
}


void SVC_Handler (void)
{


	
}

void PendSV_Handler (void)
{
	
	
}


int divide_numbers(int x, int y)
{
	
	return x/y;
}

int main(void)
{
		
	void (*go_addr)(void);
	SCB_Type *pSCB;
	pSCB=SCB;
	
		go_addr = 0x00000000;
	/* To mask HardFault, set FaultMask */
	/* __set_FAULTMASK(1); */
	go_addr();	//This will result in HARDFAULT
	
	
	
	/*1.Enable system exceptions : MemManage, BusFault, UsageFault */
	pSCB->SHCSR |= ((1<<16) | (1<<17) | (1<<18)) ; 			//Enabling MemManage, BusFault and UsageFault exceptions*/
	
	//Enabling trap when divide by zero // 
	pSCB->CCR |= (1<<4); 																
	
	/* Enable Unaligned access trap */
	pSCB->CCR |= (1<<3);
	
	//lets divide by zero//
	divide_numbers(1,0);
	
	//unaligned data access//
	uint32_t volatile *p = (uint32_t*)(0x20000001); //Not word aligned address
	uint32_t volatile var = *p;
	var++;
	//divide_numbers(1,var);
	
	while(1);	
	return 0;
}

