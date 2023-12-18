#include "main.h"

int main(void) 
{
	___ROM_VARIABLES_INIT();
	___ROM_CLOCK_INIT();
	___ROM_GPIO_INIT();
	__ROS2_HZ(100);
	
	while(1)
	{
		
		
	}
}

void TIM1_BRK_TIM9_IRQHandler(void)
{
	if( TIM9->SR & TIM_SR_UIF ) {
		TIM9->SR &= ~TIM_SR_UIF;
	}
}

void ___ROM_VARIABLES_INIT(void)
{
	push_btn = 0;
	test_var = 3.1;
	gpio_var = 5.1;
}


void EXTI0_IRQHandler(void) 
{
	__gpio_clear_interrupt(push_btn);
	// ensure
	if( push_btn_bit == 1 ) { /* stop motor; */ }
}

