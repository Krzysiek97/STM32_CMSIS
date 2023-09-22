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
void Config_GpioForSPI(){
RCC->AHBENR|=RCC_AHBENR_GPIOEEN|RCC_AHBENR_GPIOAEN;//enable clock for port A

//PE3 CS wystawic logiczne 0 na poczatek transmisji oraz 1, gdy komunikacja się zakonczy

//PA5 SCK -> AF
GPIOA->AFR[0]|=(5<<(5*4));//Its set AF5 for PA5
GPIOA->MODER|=GPIO_MODER_MODER5_1;//alternate
GPIOE->PUPDR|=GPIO_PUPDR_PUPDR5_1;//Pull down
//PA6 MISO -> INPUT (reset state)
//PA7 MOSI
GPIOA->AFR[0]|=(5<<(7*4));//Its set AF5 for PA6
GPIOA->MODER|=GPIO_MODER_MODER7_1;//alternate
GPIOE->PUPDR|=GPIO_PUPDR_PUPDR7_1;//Pull down
//PE3 CS -> Output
GPIOE->MODER|=GPIO_MODER_MODER3_0;//Output

CS_ForSPI_Set();//default value is high state
}
void CS_ForSPI_Set(){
GPIOE->ODR|=GPIO_ODR_3;
}
void CS_ForSPI_Reset(){
GPIOE->ODR&=~GPIO_ODR_3;
}
