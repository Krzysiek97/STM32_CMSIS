/*
 * GPIO.h
 *
 *  Created on: 22 sie 2023
 *      Author: kruszynk
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "main.h"

void gpio_config();
void Config_GpioForSPI();
void CS_ForSPI_Set();
void CS_ForSPI_Reset();

#endif /* GPIO_H_ */
