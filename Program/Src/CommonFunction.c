/*
 * CommonFunction.c
 *
 *  Created on: 21 sie 2023
 *      Author: kruszynk
 */

#include "CommonFunction.h"


static uint32_t msTicks;

void SysTick_Handler(){//interrupt from SysTick timer occurs every 1 ms
if(msTicks!=0)
	{
		msTicks--;
	}
}
void delay_ms(uint32_t ms){
msTicks=ms;
while(msTicks);
}


void FPU_enable(){
	SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2));  // FPU access
}
