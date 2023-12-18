#include "rom_timer.h"

// todo 1 pandabot Hz?

void __ROS2_HZ(uint16_t ros2_frequency)
{
	RCC->AHB1ENR = RCC_APB2ENR_TIM9EN; // recheck =  or |=?
	/* FORMULA
	// Assume => MCU က 72MHz ရှိတယ် ကျတော် တို့က တခါတက်တိုင်း 1 micro second တက်ချင်တယ်။
	period = 1/72e6 = 72e-6 seconds = 0.13888 * e-6 = 13.8 ns
	PSC = 1us / 13.9 ns = 1/13.9 e3 = 71.9
	So RCC->PSC  = 71;
	
	// Assume => 168MHz, we want 1us step
	1us / [(1e-6/168)) = ( e-6 * 168 ) / e-6 = 168
	So RCC->PSC = 168;  // 168 or 168-1
	*/
	TIM9->PSC  = 16;
	// FOR 10000us => 10000 us/1us = 10000
	//TIM9->ARR  = 10000;	// 10us	
	
	
	// 1/100Hz = 10000 us = 10ms
	// 1/90Hz  = 11111 us = 11ms
	// 1/80Hz  = 12500 us = 12ms
	// 1/70Hz  = 14285 us = 14ms
	// 1/60Hz  = 16666 us = 16ms
	// 1/50Hz  = 20000 us = 20ms
	// 1/40Hz  = 25000 us = 25ms
	// 1/30Hz  = 33333 us = 33ms
	// 1/20Hz  = 50000 us = 50ms
	// 1/10Hz  = 100000 us // not available because 65536
	
	switch(ros2_frequency)
	{
		case 100: TIM9->ARR  = 10000; break;
		case 90: TIM9->ARR  = 11111; break;
		case 80: TIM9->ARR  = 12500; break;
		case 70: TIM9->ARR  = 14285; break;
		case 60: TIM9->ARR  = 16666; break;
		case 50: TIM9->ARR  = 20000; break;
		case 40: TIM9->ARR  = 25000; break;
		case 30: TIM9->ARR  = 33333; break;
		case 20: TIM9->ARR  = 50000; break;
		
		default: TIM9->ARR  = 20000; break;
	}
	
	// clear counter
	TIM9->CNT  = 0;
	TIM9->CR1 |= 1; 	// counter enable
	TIM9->DIER|= 1; 	// interrupt enable
	NVIC_EnableIRQ(TIM1_BRK_TIM9_IRQn);
}
