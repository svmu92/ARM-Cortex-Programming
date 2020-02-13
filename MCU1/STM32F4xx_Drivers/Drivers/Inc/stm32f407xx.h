/*
 * stm32f407xx.h
 *
 *  Created on: 28-Dec-2019
 *      Author: Sreenath V
 */

#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

#include <stdint.h>

#define __vo volatile
#define __weak __attribute__((weak))
/*
 * Processor Specific Details
 */

#define NVIC_ISER0		((__vo uint32_t*)0xE000E100)
#define NVIC_ISER1		((__vo uint32_t*)0xE000E104)
#define NVIC_ISER2		((__vo uint32_t*)0xE000E108)
#define NVIC_ISER3		((__vo uint32_t*)0xE000E10C)


#define NVIC_ICER0		((__vo uint32_t*)0xE000E180)
#define NVIC_ICER1		((__vo uint32_t*)0xE000E184)
#define NVIC_ICER2		((__vo uint32_t*)0xE000E188)
#define NVIC_ICER3		((__vo uint32_t*)0xE000E18C)

#define NVIC_PR_BASE_ADDR	((__vo uint32_t*)0xE000E400)

#define NO_OF_PR_IMPLEMENTED	4

/*
 * Peripheral Register Definition Structures
 */

typedef struct{
	__vo uint32_t CR;
	__vo uint32_t PLLCFGR;
	__vo uint32_t CFGR;
	__vo uint32_t CIR;
	__vo uint32_t AHB1RSTR;
	__vo uint32_t AHB2RSTR;
	__vo uint32_t AHB3RSTR;
	uint32_t Reserved0;
	__vo uint32_t APB1RSTR;
	__vo uint32_t APB2RSTR;
	uint32_t Reserved1;
	uint32_t Reserved2;
	__vo uint32_t AHB1ENR;
	__vo uint32_t AHB2ENR;
	__vo uint32_t AHB3ENR;
	uint32_t Reserved3;
	__vo uint32_t APB1ENR;
	__vo uint32_t APB2ENR;
	uint32_t Reserved4;
	uint32_t Reserved5;
	__vo uint32_t AHB1LPENR;
	__vo uint32_t AHB2LPENR;
	__vo uint32_t AHB3LPENR;
	uint32_t Reserved6;
	__vo uint32_t APB1LPENR;
	__vo uint32_t APB2LPENR;
	uint32_t Reserved7;
	uint32_t Reserved8;
	__vo uint32_t BDCR;
	__vo uint32_t CSR;
	uint32_t Reserved9;
	uint32_t Reserved10;
	__vo uint32_t SSCGR;
	__vo uint32_t PLLI2SCFGR;
}RCC_RegDef_t;

typedef struct{
	__vo uint32_t MODER;
	__vo uint32_t OTYPER;
	__vo uint32_t OSPEEDR;
	__vo uint32_t PUPDR;
	__vo uint32_t IDR;
	__vo uint32_t ODR;
	__vo uint32_t BSRR;
	__vo uint32_t LCKR;
	__vo uint32_t AFR[2];
}GPIO_RegDef_t;

/*
 * Peripheral Structrure for EXTI
 */
typedef struct{
	__vo uint32_t IMR;    /*! Address offset: 0x00 */
	__vo uint32_t EMR;    /*!Address offset: 0x04 */
	__vo uint32_t RTSR;   /*!Address offset: 0x08 */
	__vo uint32_t FTSR;   /*!Address offset: 0x0C */
	__vo uint32_t SWIER;  /*! Address offset: 0x10 */
	__vo uint32_t PR;     /*!Address offset: 0x14 */
}EXTI_RegDef_t;

typedef struct{
	__vo uint32_t MEMRMP;
	__vo uint32_t PMC;
	__vo uint32_t EXTICR[4];
	uint32_t Reserved[2];
	__vo uint32_t CMPCR;
}SYSCFG_RegDef_t;


typedef struct{
	__vo uint32_t CR1;
	__vo uint32_t CR2;
	__vo uint32_t SR;
	__vo uint32_t DR;
	__vo uint32_t CRCPR;
	__vo uint32_t RXCRCR;
	__vo uint32_t TXCRCR;
}SPI_RegDef_t;

/*
 * peripheral register definition structure for I2C
 */
typedef struct
{
  __vo uint32_t CR1;        /*!< TODO,     										Address offset: 0x00 */
  __vo uint32_t CR2;        /*!< TODO,     										Address offset: 0x04 */
  __vo uint32_t OAR1;       /*!< TODO,     										Address offset: 0x08 */
  __vo uint32_t OAR2;       /*!< TODO,     										Address offset: 0x0C */
  __vo uint32_t DR;         /*!< TODO,     										Address offset: 0x10 */
  __vo uint32_t SR1;        /*!< TODO,     										Address offset: 0x14 */
  __vo uint32_t SR2;        /*!< TODO,     										Address offset: 0x18 */
  __vo uint32_t CCR;        /*!< TODO,     										Address offset: 0x1C */
  __vo uint32_t TRISE;      /*!< TODO,     										Address offset: 0x20 */
  __vo uint32_t FLTR;       /*!< TODO,     										Address offset: 0x24 */
}I2C_RegDef_t;

/*
 * base addresses of memory areas */

#define FLASH_BASEADDRESS	0x08000000
#define SRAM1_BASEADDRESS	0x20000000
#define SRAM2_BASEADDRESS	0x2001C000
#define ROM_BASEADDRESS		0x1FFF0000
#define SRAM				SRAM1_BASEADDRESS

/*
 * base address of bus domains
 */

#define PERIPH_BASEADDR			0x40000000
#define APB1PERIPH_BASEADDR		(PERIPH_BASEADDR+0x00000000)
#define APB2PERIPH_BASEADDR		(PERIPH_BASEADDR+0x00010000)
#define AHB1PERIPH_BASEADDR		(PERIPH_BASEADDR+0x00020000)
#define AHB2PERIPH_BASEADDR		(PERIPH_BASEADDR+0x10000000)

/*
 * base address of GPIO Ports
 */
#define GPIOA_BASEADDR		(AHB1PERIPH_BASEADDR+0x0000)
#define GPIOB_BASEADDR		(AHB1PERIPH_BASEADDR+0x0400)
#define GPIOC_BASEADDR		(AHB1PERIPH_BASEADDR+0x0800)
#define GPIOD_BASEADDR		(AHB1PERIPH_BASEADDR+0x0C00)
#define GPIOE_BASEADDR		(AHB1PERIPH_BASEADDR+0x1000)
#define GPIOF_BASEADDR		(AHB1PERIPH_BASEADDR+0x1400)
#define GPIOG_BASEADDR		(AHB1PERIPH_BASEADDR+0x1800)
#define GPIOH_BASEADDR		(AHB1PERIPH_BASEADDR+0x1C00)
#define GPIOI_BASEADDR		(AHB1PERIPH_BASEADDR+0x2000)
#define RCC_BASEADDR		(AHB1PERIPH_BASEADDR+0x3800)
/*
 * base address of peripherals on APB1 Bus
 */

#define I2C1_BASEADDR		(APB1PERIPH_BASEADDR+0x5400)
#define I2C2_BASEADDR		(APB1PERIPH_BASEADDR+0x5800)
#define I2C3_BASEADDR		(APB1PERIPH_BASEADDR+0x5C00)

#define SPI2_BASEADDR		(APB1PERIPH_BASEADDR+0x3800)
#define SPI3_BASEADDR		(APB1PERIPH_BASEADDR+0x3C00)

#define USART2_BASEADDR		(APB1PERIPH_BASEADDR+0x4400)
#define USART3_BASEADDR		(APB1PERIPH_BASEADDR+0x4800)
#define UART4_BASEADDR		(APB1PERIPH_BASEADDR+0x4C00)
#define UART5_BASEADDR		(APB1PERIPH_BASEADDR+0x5000)
#define UART7_BASEADDR		(APB1PERIPH_BASEADDR+0x7800)
#define UART8_BASEADDR		(APB1PERIPH_BASEADDR+0x7C00)

/*
 * base address of peripherals on APB2 Bus
 */
#define SPI1_BASEADDR		(APB2PERIPH_BASEADDR+0x3000)
#define SPI4_BASEADDR		(APB2PERIPH_BASEADDR+0x3400)
#define SPI5_BASEADDR		(APB2PERIPH_BASEADDR+0x5000)
#define SPI6_BASEADDR		(APB2PERIPH_BASEADDR+0x5400)

#define USART1_BASEADDR		(APB2PERIPH_BASEADDR+0x1000)
#define USART6_BASEADDR		(APB2PERIPH_BASEADDR+0x1400)

#define EXTI_BASEADDR		(APB2PERIPH_BASEADDR+0x3C00)
#define SYSCFG_BASEADDR		(APB2PERIPH_BASEADDR+0x3800)

/*
 * Peripheral Definitions
 */

#define GPIOA  	((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB  	((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC  	((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD  	((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE  	((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF  	((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG  	((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH  	((GPIO_RegDef_t*)GPIOH_BASEADDR)
#define GPIOI  	((GPIO_RegDef_t*)GPIOI_BASEADDR)

#define RCC		((RCC_RegDef_t*)RCC_BASEADDR)
#define EXTI	((EXTI_RegDef_t*)EXTI_BASEADDR)
#define SYSCFG	((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)

#define SPI1	((SPI_RegDef_t*)SPI1_BASEADDR)
#define SPI2	((SPI_RegDef_t*)SPI2_BASEADDR)
#define SPI3	((SPI_RegDef_t*)SPI3_BASEADDR)


#define I2C1	((I2C_RegDef_t*)I2C1_BASEADDR)
#define I2C2	((I2C_RegDef_t*)I2C2_BASEADDR)
#define SPI3	((I2C_RegDef_t*)I2C3_BASEADDR)

/*
 * Clock Enable Macros
 */
#define GPIOA_PCLK_EN()		(RCC->AHB1ENR|=(1<<0))
#define GPIOB_PCLK_EN()		(RCC->AHB1ENR|=(1<<1))
#define GPIOC_PCLK_EN()		(RCC->AHB1ENR|=(1<<2))
#define GPIOD_PCLK_EN()		(RCC->AHB1ENR|=(1<<3))
#define GPIOE_PCLK_EN()		(RCC->AHB1ENR|=(1<<4))
#define GPIOF_PCLK_EN()		(RCC->AHB1ENR|=(1<<5))
#define GPIOG_PCLK_EN()		(RCC->AHB1ENR|=(1<<6))
#define GPIOH_PCLK_EN()		(RCC->AHB1ENR|=(1<<7))
#define GPIOI_PCLK_EN()		(RCC->AHB1ENR|=(1<<8))

#define I2C1_PCLK_EN()		(RCC->APB1ENR|=(1<<21))
#define I2C2_PCLK_EN()		(RCC->APB1ENR|=(1<<22))
#define I2C3_PCLK_EN()		(RCC->APB1ENR|=(1<<23))

#define SPI2_PCLK_EN()		(RCC->APB1ENR|=(1<<14))
#define SPI3_PCLK_EN()		(RCC->APB1ENR|=(1<<15))

#define USART2_PCLK_EN()	(RCC->APB1ENR|=(1<<17))
#define USART3_PCLK_EN()	(RCC->APB1ENR|=(1<<18))
#define UART4_PCLK_EN()		(RCC->APB1ENR|=(1<<19))
#define UART5_PCLK_EN()		(RCC->APB1ENR|=(1<<20))

#define SPI1_PCLK_EN()		(RCC->APB2ENR|=(1<<12))

#define USART1_PCLK_EN()	(RCC->APB2ENR|=(1<<4))
#define USART6_PCLK_EN()	(RCC->APB2ENR|=(1<<5))

#define SYSCFG_PCLK_EN() 	(RCC->APB2ENR|=(1<<14))


/*
 * Clock Disable Macros
 */
#define GPIOA_PCLK_DI()		(RCC->AHB1ENR&=~(1<<0))
#define GPIOB_PCLK_DI()		(RCC->AHB1ENR&=~(1<<1))
#define GPIOC_PCLK_DI()		(RCC->AHB1ENR&=~(1<<2))
#define GPIOD_PCLK_DI()		(RCC->AHB1ENR&=~(1<<3))
#define GPIOE_PCLK_DI()		(RCC->AHB1ENR&=~(1<<4))
#define GPIOF_PCLK_DI()		(RCC->AHB1ENR&=~(1<<5))
#define GPIOG_PCLK_DI()		(RCC->AHB1ENR&=~(1<<6))
#define GPIOH_PCLK_DI()		(RCC->AHB1ENR&=~(1<<7))
#define GPIOI_PCLK_DI()		(RCC->AHB1ENR&=~(1<<8))


#define I2C1_PCLK_DI()		(RCC->APB1ENR&=~(1<<21))
#define I2C2_PCLK_DI()		(RCC->APB1ENR&=~(1<<22))
#define I2C3_PCLK_DI()		(RCC->APB1ENR&=~(1<<23))

#define SPI2_PCLK_DI()		(RCC->APB1ENR&=~(1<<14))
#define SPI3_PCLK_DI()		(RCC->APB1ENR&=~(1<<15))

#define USART2_PCLK_DI()	(RCC->APB1ENR&=~(1<<17))
#define USART3_PCLK_DI()	(RCC->APB1ENR&=~(1<<18))
#define UART4_PCLK_DI()		(RCC->APB1ENR&=~(1<<19))
#define UART5_PCLK_DI()		(RCC->APB1ENR&=~(1<<20))

#define SPI1_PCLK_DI()		(RCC->APB2ENR&=~(1<<12))

#define USART1_PCLK_DI()	(RCC->APB2ENR&=~(1<<4))
#define USART6_PCLK_DI()	(RCC->APB2ENR&=~(1<<5))

#define SYSCFG_PCLK_DI() 	(RCC->APB2ENR&=~(1<<14))

/*
 * Reset Peripheral Macors
 *
 */
#define GPIOA_REG_RESET()	do{(RCC->AHB1RSTR |= (1<<0)); (RCC->AHB1RSTR &= ~(1<<0));}while(0)
#define GPIOB_REG_RESET()	do{(RCC->AHB1RSTR |= (1<<1)); (RCC->AHB1RSTR &= ~(1<<1));}while(0)
#define GPIOC_REG_RESET()	do{(RCC->AHB1RSTR |= (1<<2)); (RCC->AHB1RSTR &= ~(1<<2));}while(0)
#define GPIOD_REG_RESET()	do{(RCC->AHB1RSTR |= (1<<3)); (RCC->AHB1RSTR &= ~(1<<3));}while(0)
#define GPIOE_REG_RESET()	do{(RCC->AHB1RSTR |= (1<<4)); (RCC->AHB1RSTR &= ~(1<<4));}while(0)
#define GPIOF_REG_RESET()	do{(RCC->AHB1RSTR |= (1<<5)); (RCC->AHB1RSTR &= ~(1<<5));}while(0)
#define GPIOG_REG_RESET()	do{(RCC->AHB1RSTR |= (1<<6)); (RCC->AHB1RSTR &= ~(1<<6));}while(0)
#define GPIOH_REG_RESET()	do{(RCC->AHB1RSTR |= (1<<7)); (RCC->AHB1RSTR &= ~(1<<7));}while(0)
#define GPIOI_REG_RESET()	do{(RCC->AHB1RSTR |= (1<<8)); (RCC->AHB1RSTR &= ~(1<<8));}while(0)

#define GPIO_BASE_ADDRESS_TO_CODE(x)   ((x==GPIOA) ? 0:\
										(x==GPIOB) ? 1:\
										(x==GPIOC) ? 2:\
										(x==GPIOD) ? 3:\
										(x==GPIOE) ? 4:\
										(x==GPIOF) ? 5:\
										(x==GPIOG) ? 6:\
										(x==GPIOH) ? 7:8)

#define SPI1_REG_RESET()	do{(RCC->APB2RSTR |= (1<<12)); (RCC->APB2RSTR &= ~(1<<12));}while(0)
#define SPI2_REG_RESET()	do{(RCC->APB1RSTR |= (1<<14)); (RCC->APB1RSTR &= ~(1<<14));}while(0)
#define SPI3_REG_RESET()	do{(RCC->APB1RSTR |= (1<<15)); (RCC->APB1RSTR &= ~(1<<15));}while(0)

#define I2C1_REG_RESET()    do{


/*
 * IRQ Numbers
 */
#define IRQ_NO_EXTI0 		6
#define IRQ_NO_EXTI1 		7
#define IRQ_NO_EXTI2 		8
#define IRQ_NO_EXTI3 		9
#define IRQ_NO_EXTI4 		10
#define IRQ_NO_EXTI9_5 		23

#define IRQ_NO_SPI1			35
#define IRQ_NO_SPI2			36
#define IRQ_NO_SPI3			51

#define IRQ_NO_I2C1_EV     31
#define IRQ_NO_I2C1_ER     32

#define NVIC_IRQ_PRIO15		15

#define ENABLE 			1
#define DISABLE 		0

#define SET				ENABLE
#define RESET			DISABLE

#define GPIO_PIN_SET	SET
#define GPIO_PIN_RESET	RESET

#define TRUE			SET
#define FALSE			RESET

#define FLAG_RESET         RESET
#define FLAG_SET 			SET


/*
 * Bit position definitions SPI_CR1
 *
 */

#define SPI_CR1_CPHA					 0
#define SPI_CR1_CPOL      				 1
#define SPI_CR1_MSTR     				 2
#define SPI_CR1_BR   					 3
#define SPI_CR1_SPE     				 6
#define SPI_CR1_LSBFIRST   			 	 7
#define SPI_CR1_SSI     				 8
#define SPI_CR1_SSM      				 9
#define SPI_CR1_RXONLY      		 	10
#define SPI_CR1_DFF     			 	11
#define SPI_CR1_CRCNEXT   			 	12
#define SPI_CR1_CRCEN   			 	13
#define SPI_CR1_BIDIOE     			 	14
#define SPI_CR1_BIDIMODE      			15

/*
 * Bit position definitions SPI_CR2
 */
#define SPI_CR2_RXDMAEN		 			0
#define SPI_CR2_TXDMAEN				 	1
#define SPI_CR2_SSOE				 	2
#define SPI_CR2_FRF						4
#define SPI_CR2_ERRIE					5
#define SPI_CR2_RXNEIE				 	6
#define SPI_CR2_TXEIE					7

/*
 * Bit position definitions SPI_SR
 */
#define SPI_SR_RXNE						0
#define SPI_SR_TXE				 		1
#define SPI_SR_CHSIDE				 	2
#define SPI_SR_UDR					 	3
#define SPI_SR_CRCERR				 	4
#define SPI_SR_MODF					 	5
#define SPI_SR_OVR					 	6
#define SPI_SR_BSY					 	7
#define SPI_SR_FRE					 	8

/******************************************************************************************
 *Bit position definitions of I2C peripheral
 ******************************************************************************************/
/*
 * Bit position definitions I2C_CR1
 */
#define I2C_CR1_PE						0
#define I2C_CR1_NOSTRETCH  				7
#define I2C_CR1_START 					8
#define I2C_CR1_STOP  				 	9
#define I2C_CR1_ACK 				 	10
#define I2C_CR1_SWRST  				 	15

/*
 * Bit position definitions I2C_CR2
 */
#define I2C_CR2_FREQ				 	0
#define I2C_CR2_ITERREN				 	8
#define I2C_CR2_ITEVTEN				 	9
#define I2C_CR2_ITBUFEN 			    10

/*
 * Bit position definitions I2C_OAR1
 */
#define I2C_OAR1_ADD0    				 0
#define I2C_OAR1_ADD71 				 	 1
#define I2C_OAR1_ADD98  			 	 8
#define I2C_OAR1_ADDMODE   			 	15

/*
 * Bit position definitions I2C_SR1
 */

#define I2C_SR1_SB 					 	0
#define I2C_SR1_ADDR 				 	1
#define I2C_SR1_BTF 					2
#define I2C_SR1_ADD10 					3
#define I2C_SR1_STOPF 					4
#define I2C_SR1_RXNE 					6
#define I2C_SR1_TXE 					7
#define I2C_SR1_BERR 					8
#define I2C_SR1_ARLO 					9
#define I2C_SR1_AF 					 	10
#define I2C_SR1_OVR 					11
#define I2C_SR1_TIMEOUT 				14

/*
 * Bit position definitions I2C_SR2
 */
#define I2C_SR2_MSL						0
#define I2C_SR2_BUSY 					1
#define I2C_SR2_TRA 					2
#define I2C_SR2_GENCALL 				4
#define I2C_SR2_DUALF 					7

/*
 * Bit position definitions I2C_CCR
 */
#define I2C_CCR_CCR 					 0
#define I2C_CCR_DUTY 					14
#define I2C_CCR_FS  				 	15



#endif /* INC_STM32F407XX_H_ */
