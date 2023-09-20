/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include "main.h"

uint16_t arr=4095;//variable to auto reload registers
uint32_t NbOfConv=1;//number of conversion per one ADC's measurement
uint32_t ADC_Data=0;
uint8_t duty=0;

extern uint32_t msTicks;

int main(){

SysTick_Config(8000000 / 1000);
gpio_config();
timer1_config();
adc_config();
DMA_config();
Config_GpioForSPI();

while(1){

ADC1->CR|=ADC_CR_ADSTART;//: ADC start of regular conversion
while (!(DMA1->ISR & DMA_ISR_TCIF1));  //Wait for flag's -> transfer complete (TC) event occurred on channel 1
TIM1->CCR4=ADC_Data;
DMA1->IFCR|=DMA_IFCR_CTCIF1;
}
return 0;
}





