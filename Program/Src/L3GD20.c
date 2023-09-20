/*
 * L3GD20.c
 *
 *  Created on: 19 wrz 2023
 *      Author: kruszynk
 */


#include "L3GD20.h"

void L3GD20_Read(uint8_t ReadAddress,uint8_t * buffer,uint32_t len){
	if(len>0) ReadAddress|MS_BIT;
}
