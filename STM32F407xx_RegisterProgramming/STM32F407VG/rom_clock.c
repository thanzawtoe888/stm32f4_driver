#include "rom_clock.h"

void ___ROM_CLOCK_MEASURE_FROM_PA8_MCO1(void)
{
	// သူက  MCU ရဲ့  clock output ဖြစ် ပါတယ်။ ဒီဖန်ရှင်ကို clock setup မလုပ်ခင် run ရပါမယ်။

	// သူသည် MCO1 clock output 1 ဖြစ်ပါတယ်။
	// clock source သည်  
	// HSI ဆိုရင် 0<<21 ,  
	// LSE ဆိုရင် 1<<21 , 
	// HSE ဆိုရင် 2<<21 , 
	// PLL ဆိုရင် 3<<21 ဖြစ်ပြီး PLL ရွေး ထားသည်။
	RCC->CFGR |= 3<<21;

	// သူသည် prescaler ဖြစ်ပြီး 
	// 0 ဆို no division, 
	// 100 ဆို divide by 2, 
	// 101 ဆို divide by 3, 
	// 110 ဆို divide by 4, 
	// 111 ဆို divide by 5 ဖြစ်ပြီး divide by 4 ရွေးထားသည်။ 168/4 = 42MHz 
	// MCO1 PRE
	RCC->CFGR |= 6<<24;
}



void ___ROM_CLOCK_MEASURE_FROM_PC9_MCO2(void)
{
	// သူက  MCU ရဲ့  clock output ဖြစ် ပါတယ်။ ဒီဖန်ရှင်ကို clock setup မလုပ်ခင် run ရပါမယ်။

	// MCO2 --> သူသည် MCO2 clocu output 2 ဖြစ်ပါတယ်။ clock source သည် 
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
	// HSEON bit
	RCC->CR |= ( 1 << 16);

	// HSERDY bit ( clock ကို stable ဖြစ်စေရန် clock cycle အနည်းငယ်စောင့်ပြီး ready bit ကို စောင့်သည်။ )
	while( ! ( RCC->CR & (1<<17) ) );

	// SW0, SW1 bit များ ကို ကိုင်ပြီး system clock ကို hse အသုံးပြုခိုင်းသည်။
	RCC->CFGR &= ~(0x3U); // bit 0 နဲ့ bit 1 ကို 0 ဖြစ်စေ သည်။
	RCC->CFGR |= 0X01;     // 01 က HSE  

	// ခုကစပြီး MCU သည်  SYSCLK အဖြစ် HSE ကို အသုံးပြုပါသည်။
}



void ___ROM_USE_PLL_CLOCK(void)
{
	/* HSE ကို  PLL ရဲ့ source အဖြစ် သုံးပါမည်။ */
	// HSEON bit
	RCC->CR |= ( 1 << 16);
	// HSERDY bit ( clock ကို stable ဖြစ်စေရန် clock cycle အနည်းငယ်စောင့်ပြီး ready bit ကို စောင့်သည်။ )
	while( ! ( RCC->CR & ( 1 << 17 ) ) );
	// PLL ကို ပိတ်ထားမည်။
	RCC->CR &= ~( 1U << 24 );
	// HSE ကို PLL ရဲ့  clock source အဖြစ် သုံးမည်။
	RCC->PLLCFGR |= ( 1 << 22 );
	
	/* PLL 168MHz */
	// reference manual အရ VCO သည် 1 to 2MHz အတွင်း ရှိရမှာမို့  PLLM ကို divide by 8 ထားပြီး  1MHz ရအောင်လုပ်မည်။
	RCC->PLLCFGR &= ~( 0x1FU );
	RCC->PLLCFGR |= ( 0x08 );           // PLLM = 8
	// VCO input သည် 1MHz ရှိပြီး reference manual အရ PLLN သည် 192 to 432 ရှိရမှာဖြစ်သည်။
	// PLLN ကို 336 ထားပြီး formula အရ  VCO output 336MHz ရသည်။
	RCC->PLLCFGR &= ~( 0x1FFU << 6 );
	RCC->PLLCFGR |= ( 336 << 6 );     // PLLN = 336
	// နောက်တဆင့်အနေနဲ့  PLLP ကို divide by 2 ထားပြီး 168MHz ရပါသည်။
	RCC->PLLCFGR &= ~( 0x03U << 16 );
	RCC->PLLCFGR |= ( 0x02 << 16 );
	
	// PLLON bit ( clock ကို stable ဖြစ်စေရန် clock cycle အနည်းငယ်စောင့်ပြီး ready bit ကို စောင့်သည်။ )
	RCC->CR |= ( 1 << 24);

	// PLLRDY bit
	while( ! ( RCC->CR & (1<<25) ) );

	// SW0, SW1 bit များ ကို ကိုင်ပြီး system clock ကို PLL အသုံးပြုခိုင်းသည်။
	RCC->CFGR &= ~(0x3U);  // bit 0 နဲ့ bit 1 ကို 0 ဖြစ်စေ သည်။
	RCC->CFGR |= 0x02;     // 10 က PLL
	
	/* HCLK ကို  prescaler 1 ထားပြီး 168MHz ရစေသည်။ */
	RCC->CFGR &= ~( 0xFU << 4 );

	/* APB1 prescaler 4 , (168/4) = 42MHz */
	RCC->CFGR &= ~( 0x7U << 10 );
	RCC->CFGR |= ( 0x5U << 10 );

	/* APB2 prescaler 2 , (168/2) = 84MHz */
	RCC->CFGR &= ~( 0x7U << 13 );
	RCC->CFGR |= ( 0x4 << 13 );
	
	// ခုကစပြီး MCU သည်  SYSCLK အဖြစ် PLL ကို အသုံးပြုပြီး full speed 168MHz ဖြစ်သည်။
}


void ___ROM_CLOCK_INIT(void) 
{
	___ROM_USE_PLL_CLOCK();
	//___ROM_CLOCK_MEASURE_FROM_PC9_MCO2();
	//test_var *= 2.0;
}
