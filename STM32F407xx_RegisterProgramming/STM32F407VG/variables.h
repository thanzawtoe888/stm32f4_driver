/*******************************************************************************
 *                    ROM ROBOTICS Co,.Ltd ( Myanmar )    										 *
 *			(?) COPYLEFT 2023		| www.romrobots.com | (+95) 9-259-288-229 				 *
 *******************************************************************************/ 
#ifndef __ROM_VARIABLES_H
#define __ROM_VARIABLES_H

#include "stm32f407xx.h"

/* Declaration of variables */ /* variables.h -> main.h -> main.c -> something.c */
extern double test_var;
extern double gpio_var;

#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

#define ROM_GPIOA_ODR_Address (GPIOA_BASE + 0x14)
#define ROM_GPIOB_ODR_Address (GPIOB_BASE + 0x14)
#define ROM_GPIOC_ODR_Address (GPIOC_BASE + 0x14)
#define ROM_GPIOD_ODR_Address (GPIOD_BASE + 0x14)
#define ROM_GPIOE_ODR_Address (GPIOE_BASE + 0x14)

#define ROM_GPIOA_IDR_Address (GPIOA_BASE + 0x10)
#define ROM_GPIOB_IDR_Address (GPIOB_BASE + 0x10)
#define ROM_GPIOC_IDR_Address (GPIOC_BASE + 0x10)
#define ROM_GPIOD_IDR_Address (GPIOD_BASE + 0x10)
#define ROM_GPIOE_IDR_Address (GPIOE_BASE + 0x10)

#define PAout(n)   BIT_ADDR(ROM_GPIOA_ODR_Address,n)  
#define PAin(n)    BIT_ADDR(ROM_GPIOA_IDR_Address,n) 

#define PBout(n)   BIT_ADDR(ROM_GPIOB_ODR_Address,n)  
#define PBin(n)    BIT_ADDR(ROM_GPIOB_IDR_Address,n) 

#define PCout(n)   BIT_ADDR(ROM_GPIOC_ODR_Address,n)  
#define PCin(n)    BIT_ADDR(ROM_GPIOC_IDR_Address,n) 

#define PDout(n)   BIT_ADDR(ROM_GPIOD_ODR_Address,n)  
#define PDin(n)    BIT_ADDR(ROM_GPIOD_IDR_Address,n) 

#define PEout(n)   BIT_ADDR(ROM_GPIOE_ODR_Address,n)  
#define PEin(n)    BIT_ADDR(ROM_GPIOE_IDR_Address,n) 

#endif
