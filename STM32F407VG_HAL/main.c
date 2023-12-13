#include "main.h"

int main(void) 
{
	___ROM_VARIABLES_INIT();
	___ROM_CLOCK_INIT();
	___ROM_GPIO_INIT();
	
	
	while(1)
	{
		
		
	}
}

void ___ROM_VARIABLES_INIT(void)
{
	test_var = 3.1;
	gpio_var = 5.1;
}
