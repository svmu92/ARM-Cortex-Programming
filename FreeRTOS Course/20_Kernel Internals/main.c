
//GPIO Access Steps
//1. Enable RCC->AHB1ENR clock access
//2. Set the mode 
//3. Special parameters of the pin - PUPD, SPEED etc
//4. Output Regiser (ODR)
//Four LEDS connected to PORTD pins 12,13,14,15


//#include "stdint.h"
#include "stm32f4xx.h"

#define		GREEN					(1<<12)
#define		ORANGE				(1<<13)
#define		RED						(1<<14)
#define		BLUE					(1<<15)

#define		GREEN_BIT				(1U<<24)
#define		ORANGE_BIT				(1U<<26)
#define		RED_BIT				(1U<<28)
#define		BLUE_BIT				(1U<<30)

#define  	GPIOD_CLOCK		(1<<3)


uint32_t orange_stack[40];
uint32_t blue_stack[40];
uint32_t *sp_orange = &orange_stack[40];
uint32_t *sp_blue = &blue_stack[40];

volatile uint32_t tick;
volatile uint32_t _tick;

void GPIO_Init(void);
uint32_t getTick(void);
void SysTick_Handler(void);
void DelayS(uint32_t seconds);
void blueOn(void);
void blueOff(void);
void orangeOn(void);
void orangeOff(void);


int orange_main(void)
{
		while(1)
		{
		orangeOn();
		DelayS(1);
		orangeOff();
		DelayS(1);
		}
}

int blue_main(void)
{
		while(1)
		{
		blueOn();
		DelayS(1);
		blueOff();
		DelayS(1);
		}
}

int main()
{
	uint32_t volatile start=0U;
	GPIO_Init();
//Step 3
//ON/OFF the GPIO
	
//	if(start)
//	{
//	blue_main();
//	}
//	else
//	{
//	orange_main();
//	}

	//populating the stack frame orange
	*(--sp_orange)= (1U<<24); //xPSR
	*(--sp_orange)= (uint32_t)&orange_main; //PC
	*(--sp_orange)= 0x0000000DU; //LR//
	*(--sp_orange)= 0x0000000EU; //R12//	
	*(--sp_orange)= 0x0000000AU; //R3//
	*(--sp_orange)= 0x0000000EU; //R2//
	*(--sp_orange)= 0x0000000AU; //R1//
	*(--sp_orange)= 0x0000000DU; //R1//


	//populating the stack frame blue
	*(--sp_blue)= (1U<<24); //xPSR
	*(--sp_blue)= (uint32_t)&blue_main; //PC
	*(--sp_blue)= 0x0000000BU; //LR//
	*(--sp_blue)= 0x0000000EU; //R12//	
	*(--sp_blue)= 0x0000000EU; //R3//
	*(--sp_blue)= 0x0000000EU; //R2//
	*(--sp_blue)= 0x0000000EU; //R1//
	*(--sp_blue)= 0x0000000FU; //R1//
	
	
	while(1)
	{
		//GPIOD->ODR ^= (GREEN | ORANGE | RED | BLUE);
		
		/*blueOn();
		DelayS(1);
		blueOff();
		DelayS(1);*/
	}
//return 0;	
	
}


void GPIO_Init(void)
{
//Step 1
//AHB1ENR Enable
RCC->AHB1ENR |= GPIOD_CLOCK;

//Step 2
//Set GPIO Output mode
GPIOD->MODER |= (GREEN_BIT | ORANGE_BIT | RED_BIT | BLUE_BIT);	
	
	
	SystemCoreClockUpdate(); //Current System Clock
	SysTick_Config(SystemCoreClock/1000);
	__enable_irq();
		
}


void SysTick_Handler(void)
{
	++tick;
	
}


uint32_t getTick(void)
{
	__disable_irq();
	_tick=tick;		//no interrupt should happen while executing this instruction (load,process,store). So disable interrupts 
	__enable_irq();
	
	return _tick;
}

void DelayS(uint32_t seconds)
{
	seconds= seconds*1000;
	uint32_t temp = getTick();//current tick value
	
	while((getTick()-temp)<seconds);//while tick value - stored tick value is less than required delay, wait
}


void blueOn(void)
{
	GPIOD->ODR |= BLUE;
	
}

void blueOff(void)
{
	//GPIOD->ODR &= ~BLUE;
	GPIOD->ODR &= 0U;
}
	

void orangeOn(void)
{
	GPIOD->ODR |= ORANGE;
}

void orangeOff(void)
{
	//GPIOD->ODR &= ~ORANGE;
	GPIOD->ODR &= 0U;
}
	
