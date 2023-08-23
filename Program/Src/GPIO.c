/*
 * GPIO.c
 *
 *  Created on: 22 sie 2023
 *      Author: kruszynk
 */

#include "GPIO.h"

void gpio_config(){
RCC->AHBENR|=RCC_AHBENR_GPIOEEN|RCC_AHBENR_GPIOAEN;//enable clock for port E and port A
GPIOE->AFR[1]|=(2<<((14-8)*4));//Its set AF2 for PE14
GPIOE->MODER|=GPIO_MODER_MODER14_1;//alternate
GPIOE->PUPDR|=GPIO_PUPDR_PUPDR14_1;//Pull down
GPIOA->MODER|=GPIO_MODER_MODER0_0 | GPIO_MODER_MODER0_1;//analog state

GPIOE->MODER|=GPIO_MODER_MODER15_0;//tryb output
}
