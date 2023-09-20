/*
 * SPI.h
 *
 *  Created on: 18 wrz 2023
 *      Author: kruszynk
 */

#ifndef SPI_H_
#define SPI_H_

#include "main.h"

void SPI_init();
void SPI_enable();
void SPI_SendData(uint8_t *data,uint8_t len);
void SPI_ReceiveData(uint8_t *buffer, uint8_t len);


#endif /* SPI_H_ */
