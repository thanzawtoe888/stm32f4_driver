#include "rom_gpio.h"


void ___ROM_GPIO_INIT(void) 
{
	gpio_var *= 2.0;
	
	// GPIOD CLOCK ENABLE
	RCC->AHB1ENR = RCC_AHB1ENR_GPIODEN;
	
	// input or output
	GPIOD->MODER &= ~(3u<<24 & 3u<<26 & 3u<<28 & 3u<<30);
	GPIOD->MODER  |= 1 << 24 		// PD12 output
								| 1 << 26			// PD13
								| 1 << 28			// PD14
								| 1 << 30;		// PD15
	
	// what speed
	GPIOD->OSPEEDR &= ~(3u<<24 & 3u<<26 & 3u<<28 & 3u<<30);
	GPIOD->OSPEEDR |= 1 << 24 	// PD12 medium speed
								 | 1 << 26		// PD13
								 | 1 << 28		// PD14
								 | 1 << 30;		// PD15
	
	green_led = 1;
} 
