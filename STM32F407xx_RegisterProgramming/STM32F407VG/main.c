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

// interrupt use about 3us


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

