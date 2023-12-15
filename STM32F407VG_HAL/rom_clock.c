#include "rom_clock.h"


void ___ROM_CLOCK_INIT(void) 
{
	___ROM_USE_PLL_CLOCK();
	//___ROM_CLOCK_MEASURE_FROM_PC9_MCO2();
	//test_var *= 2.0;
}

/* to fix */
// Error_handler();
// RCC_CLOCK_PCLK2

void ___ROM_USE_PLL_CLOCK(void)
{
	RCC_OscInitTypeDef osc_init;
	RCC_ClkInitTypeDef clock_init;

	// random value တွေ မဖြစ်အောင် 0 နဲ့ ဖြည့်လိုက်တာပါ။
	memset(&osc_init, 0, sizeof(osc_init) );
	
	// clock speed အမြင့် ဆုံးဆိုရင် power for clock ကို လည်း တင်ဖို့ လိုကောင်း လိုပါမယ်။
	// Enable the clock for the power controller
	// __HAL_RCC_CLK_ENABLE();
	// set regulator voltage scale as 1
	// __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
	// Turn on the over drive mode of the voltage regulator
	// __HAL_PWR_OVERDRIVE_ENABLE();

	uint32_t Flatency = 0u;

	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	// ဒီခါတော့ HSE သုံးပြီး PLL လုပ်မယ်။
	osc_init.HSEState = RCC_HSE_ON;

	//
	osc_init.PLL.PLLState = RCC_PLL_ON;
	osc_init.PLL.PLLSource = RCC_PLLSOURCE_HSE;

	osc_init.PLL.PLLM = 4;
	osc_init.PLL.PLLN = 168;
	osc_init.PLL.PLLP = 2;
	osc_init.PLL.PLLQ = 2;
	//osc_init.PLL.PLLR = 2;

	clock_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	clock_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	clock_init.AHBCLKDivider = RCC_SYSCLK_DIV1; 
	clock_init.APB1CLKDivider = RCC_SYSCLK_DIV4; 
	clock_init.APB2CLKDivider = RCC_SYSCLK_DIV2; 

	Flatency = FLASH_ACR_LATENCY_5WS; // to edit

	if( HAL_RCC_OscConfig(&osc_init) != HAL_OK ) { /*Error_handler();*/ }

___ROM_CLOCK_MEASURE_FROM_PC9_MCO2();
	// ဒီမှာ ဒုတိယ argument ဖြစ်တဲ့ flash latency က အရေးကြီးပါတယ်။ reference maunal ရဲ့ embedded flash memory ကို ကြည့်ပါ။
	//  flash memory ကို သေချာ read data လုပ်နိုင်ဖို့  wait state ဖြစ်တဲ့ latency ကို သေချာ configure လုပ်ဖို့လိုပါတယ်။
	//  HCLK frequency နဲ့  supply voltage အရ FLASH_ACR ( flash access control register ) မှာ 
	//  latency သတ်မှတ်ဖို့လိုတယ်။
	//  HCLK frequency များရင် flash data read တာ fail နိုင်တယ်၊ table ကို ကြည့်ပြီး latency ရဲ့  cpu cycle ကို ဆုံးဖြတ်ပါ။
	//  ဆုံးဖြတ်တာမှားရင် application အလုပ်မလုပ်တာ ဘာမှန်းမသိ အဖြေရှာမရတာမျိုးတွေဖြစ်နိုင်တယ်။
	if( HAL_RCC_ClockConfig(&clock_init, Flatency) != HAL_OK ) { /*Error_handler();*/ }

	// ခုဆိုရင် HSI ကို ပိတ်ထားလို့လည်းရပါပြီ။
	__HAL_RCC_HSI_DISABLE();

	
	// SYSTICK --> HAL 
	// HSI ကို disable လုပ်ပြီး HSE သုံးတာမို့လို့ SYSTICK ကို reconfigure လုပ်ပေးဖို့လိုမယ်။ HCLK Speed ကွာသွားလို့ဖြစ်တယ်။ 
	// SYSTICK --> HAL မှာသုံးတဲ့ 1ms delay ရအောင် systick သုံးဖို့လိုတယ်။ systick သည် arm ရဲ့  peripheral မို့လို့ cortex.c ကို သုံးဖို့လိုမယ်။
	// Init, Interrupt, Start
	//  SYSTICK သည် HCLK ပေါ်မူတည် တာမို့ တွက်ဖို့လိုမယ်။
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

   // ခုဆိုရင် peripherals တွေကို initialize လုပ်လို့ရပါပြီ။ 
// pll အတွက် hse ကို သုံးသင့်တယ်၊ hsi သည် temperature အရ accuracy နဲလာနိုင်လို့ဖြစ်ပါတယ်။ 
	
}


void ___ROM_CLOCK_MEASURE_FROM_PA8_MCO1(void)
{}



void ___ROM_CLOCK_MEASURE_FROM_PC9_MCO2(void)
{
		// သူက  MCU ရဲ့  clock output ဖြစ် ပါတယ်။ ဒီဖန်ရှင်ကို clock setup မလုပ်ခင် run ရပါမယ်။

	// MCO2 --> သူသည် MCO2 clock output 2 ဖြစ်ပါတယ်။ clock source သည် 
	// SYSCLK ဆိုရင် 00 ,  
	// PLLI2S ဆိုရင် 01 , 
	// HSE ဆိုရင် 10 , 
	// PLL ဆိုရင် 11 ဖြစ်ပြီး SYSCLK ရွေး ထားသည်။
	RCC->CFGR &= ~(1u << 30);
	RCC->CFGR &= ~(1u << 31);

	// MCO2PRE --> သူသည် prescaler ဖြစ်ပြီး 0 ဆို no division, 
	// 100 ဆို divide by 2, 
	// 101 ဆို divide by 3, 
	// 110 ဆို divide by 4, ( 42MHz )
	// 111 ဆို divide by 5  ( 33.6MHz) 
	// ယခု 111 ရွေးထားသည်။ 168/5 = 33.6 MHz 
	RCC->CFGR |= 7<<27;
}



// Default အားဖြင့် STM32 MCU တွေသည် HSI ကို အသုံးပြုမှာ ဖြစ်ပြီး HSE သို့မဟုတ် PLL သုံးရန် အောက်ပါ function တစ်ခုခုကို ရွေးပါ။
void ___ROM_USE_HSE_CLOCK(void)
{
	
	RCC_OscInitTypeDef osc_init;
	RCC_ClkInitTypeDef clock_init;

	// random value တွေ မဖြစ်အောင် 0 နဲ့ ဖြည့်လိုက်တာပါ။
	memset(&osc_init, 0, sizeof(osc_init) );

	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	// RCC_HSE_BYPASS ဆိုတာက တခြား mcu က လာတဲ့ clock ကို ဆိုလိုတာပါ။
	//  nucleo board မှာဆိုရင် stlink mcu က clock ကို main mcu ကို ပေးထားပြီး main mcu တွင် hse_bpyass သုံးရပါမယ်။
	osc_init.HSEState = RCC_HSE_ON;

	if( HAL_RCC_OscConfig(&osc_init) != HAL_OK ) { /*Error_handler();*/ }

	clock_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	clock_init.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
	clock_init.AHBCLKDivider = RCC_SYSCLK_DIV2;
	clock_init.APB1CLKDivider = RCC_SYSCLK_DIV2;
	clock_init.APB2CLKDivider = RCC_SYSCLK_DIV2;

	// ဒီမှာ ဒုတိယ argument ဖြစ်တဲ့ flash latency က အရေးကြီးပါတယ်။ reference maunal ရဲ့ embedded flash memory ကို ကြည့်ပါ။
	// flash memory ကို သေချာ read data လုပ်နိုင်ဖို့  wait state ဖြစ်တဲ့ latency ကို သေချာ configure လုပ်ဖို့လိုပါတယ်။
	//  HCLK frequency နဲ့  supply voltage အရ FLASH_ACR ( flash access control register ) မှာ  latency သတ်မှတ်ဖို့လိုတယ်။
	//  HCLK frequency များရင် flash data read တာ fail နိုင်တယ်၊ table ကို ကြည့်ပြီး latency ရဲ့  cpu cycle ကို ဆုံးဖြတ်ပါ။
	//  ဆုံးဖြတ်တာမှားရင် application အလုပ်မလုပ်တာ ဘာမှန်းမသိ အဖြေရှာမရတာမျိုးတွေဖြစ်နိုင်တယ်။
	if( HAL_RCC_ClockConfig(&clock_init, FLASH_ACR_LATENCY_0WS) != HAL_OK ) { /*Error_handler();*/ }

	// ခုဆိုရင် HSI ကို ပိတ်ထားလို့လည်းရပါပြီ။
	__HAL_RCC_HSI_DISABLE();

	// USART ကို သုံးပြီး print() နဲ့ debug လုပ်ပါ။


	// SYSTICK --> HAL 
	// HSI ကို disable လုပ်ပြီး HSE သုံးတာမို့လို့ SYSTICK ကို reconfigure လုပ်ပေးဖို့လိုမယ်။ HCLK Speed ကွာသွားလို့ဖြစ်တယ်။ 
	// SYSTICK --> HAL မှာသုံးတဲ့ 1ms delay ရအောင် systick သုံးဖို့လိုတယ်။ systick သည် arm ရဲ့  peripheral မို့လို့ cortex.c ကို သုံးဖို့လိုမယ်။
	// Init, Interrupt, Start
	//  SYSTICK သည် HCLK ပေါ်မူတည် တာမို့ တွက်ဖို့လိုမယ်။
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

// Uart သုံးထားရင် Init ပြန်လုပ်ဖို့လိုတယ်။
}





