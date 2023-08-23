/*
 * Timer1.c
 *
 *  Created on: 22 sie 2023
 *      Author: kruszynk
 */

#include "Timer1.h"

extern uint16_t arr;
extern int duty;

void timer1_config(void){
RCC->APB2ENR|=RCC_APB2ENR_TIM1EN;//enable clock for timer1
TIM1->CR1|=TIM_CR1_CMS_0;//Center-aligned mode 1;Counter counts up and down
TIM1->CCMR2|=TIM_CCMR2_OC4PE;//Preload register on TIM1_CCR4 is enabled. It means its can be changed fill factor.
TIM1->CCMR2|=TIM_CCMR2_OC4M_2|TIM_CCMR2_OC4M_1;//PWM Mode 1
TIM1->CR1|=TIM_CR1_ARPE;//TIM1_ARR is buffered
TIM1->EGR=TIM_EGR_UG;//Reinitialize the counter and generates an update of the registers
TIM1->CCER|=TIM_CCER_CC4E;//Capture/Compare 4 output enable
TIM1->BDTR|=TIM_BDTR_MOE;
TIM1->ARR=arr-1;//auto-reload register
TIM1->CCR4=duty;
TIM1->CR1|=TIM_CR1_CEN;//Counter enable
}

