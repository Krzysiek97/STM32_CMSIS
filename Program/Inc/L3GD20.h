/*
 * L3GD20.h
 *
 *  Created on: 19 wrz 2023
 *      Author: kruszynk
 */

#ifndef L3GD20_H_
#define L3GD20_H_

#include "main.h"

#define L3GD20_WHO_AM_I_ADDR          0x0F  //device identification register
#define ToRead_Bit ((uint8_t)0x80) //Read bit (SPI Read)
#define MS_BIT    ((uint8_t)0x40)//When 0 do not increment address; when 1 increment address in multiple reading.

void L3GD20_Read(uint8_t ReadAddress,uint8_t * buffer,uint32_t len);
void L3GD20_Send(uint8_t Data);

#endif /* L3GD20_H_ */
