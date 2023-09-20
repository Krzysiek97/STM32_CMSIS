/*
 * DMA.c
 *
 *  Created on: 22 sie 2023
 *      Author: kruszynk
 */

#include "DMA.h"

extern uint32_t ADC_Data;
extern uint8_t NbOfConv;

void DMA_config(){
RCC->AHBENR|=RCC_AHBENR_DMA1EN;//Clock's for DMA1
DMA1_Channel1->CCR|=DMA_CCR_PSIZE_0;//Peripheral size: 16 bits
DMA1_Channel1->CCR|=DMA_CCR_MSIZE_0;//Peripheral size: 16 bits
DMA1_Channel1->CPAR=(uint32_t) &ADC1->DR;//peripheral register address
DMA1_Channel1->CMAR=(uint32_t) &ADC_Data;//memory register address
DMA1_Channel1->CNDTR=NbOfConv;
DMA1_Channel1->CCR |= DMA_CCR_CIRC;//Circular mode
DMA1_Channel1->CCR|=DMA_CCR_EN;//Channel enable
}
