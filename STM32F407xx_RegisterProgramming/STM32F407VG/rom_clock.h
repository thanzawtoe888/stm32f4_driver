/*******************************************************************************
 *                    ROM ROBOTICS Co,.Ltd ( Myanmar )    										 *
 *			(?) COPYLEFT 2023		| www.romrobots.com | (+95) 9-259-288-229 				 *
 *******************************************************************************/ 
#ifndef __ROM_CLOCK_H
#define __ROM_CLOCK_H

#include "variables.h"

/* pc9 တွင် clock output လိုချင်ပါက အောက်ပါ MACRO ကို  comment ဖြုတ်ပါ။ */
//#define USE_PC9_AS_CLOCK_OUTPUT 1

void ___ROM_CLOCK_INIT(void);
void ___ROM_CLOCK_MEASURE_FROM_PC9_MCO2(void);
void ___ROM_CLOCK_MEASURE_FROM_PC9_GPIO(void);
void ___ROM_USE_PLL_CLOCK(void);

void ___ROM_CLOCK_MEASURE_FROM_PA8_MCO1(void);
void ___ROM_USE_HSE_CLOCK(void);


#endif
