#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

#ifndef __STM32F4_RTOS_BSP_H
#define __STM32F4_RTOS_BSP_H

//Timers
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;

/**
	*@brief 	Initialize General Purpose Timer 2
	*@input		None
	*@retval 	None
	**/
void TIM2_Init (void);

/**
	*@brief 	Initialize General Purpose Timer 3
	*@input		None
	*@retval 	None
	**/
void TIM3_Init (void);

/**
	*@brief 	Initialize General Purpose Timer 4
	*@input		None
	*@retval 	None
	**/
void TIM4_Init (void);

/**
	*@brief 	Initialize General Purpose Timer 5
	*@input		None
	*@retval 	None
	**/
void TIM5_Init (void);

/**
	*@brief 	Initialize General Purpose Timer 2 and Configure Interrupt
	*@input		None
	*@retval 	None
	**/
void TIM2_Init_Start (void);
/**
	*@brief 	Initialize General Purpose Timer 3 and Configure Interrupt
	*@input		None
	*@retval 	None
	**/
void TIM3_Init_Start (void);
/**
	*@brief 	Initialize General Purpose Timer 4 and Configure Interrupt
	*@input		None
	*@retval 	None
	**/
void TIM4_Init_Start (void);
/**
	*@brief 	Initialize General Purpose Timer 5 and Configure Interrupt
	*@input		None
	*@retval 	None
	**/
void TIM5_Init_Start (void);


#endif