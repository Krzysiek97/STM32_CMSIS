/*
 * ADC.c
 *
 *  Created on: 22 sie 2023
 *      Author: kruszynk
 */
#include "ADC.h"

void adc_config(){
//ADC1-> DMA1 Channel 1
RCC->AHBENR|=RCC_AHBENR_ADC12EN;//Clock's for ADC1 and ADC2 enable
ADC12_COMMON->CCR|=ADC12_CCR_CKMODE_1;
ADC1->CR &=~ADC_CR_ADVREGEN;
ADC1->CR |=ADC_CR_ADVREGEN_0;//ADC voltage regulator enable
delay_ms(1);
ADC1->SQR1 = (1 << 6);//set ADC1 channel 1
ADC1->CFGR|=ADC_CFGR_OVRMOD;//Overrun Mode
ADC12_COMMON->CCR|=ADC12_CCR_DMACFG;//DMA Circular Mode selected
ADC1->CFGR|=ADC_CFGR_DMAEN;//DMA enable for ADC
/*
ADC1->CR |= ADC_CR_ADCAL; // Start ADC calibration
while (ADC1->CR & ADC_CR_ADCAL); // Wait for calibration to finish
*/
delay_ms(10);
ADC1->CR |=ADC_CR_ADEN;//ADC enable control
while (!(ADC1->ISR & ADC_ISR_ADRDY)); // Wait until ADC is prepared to conversion
}
