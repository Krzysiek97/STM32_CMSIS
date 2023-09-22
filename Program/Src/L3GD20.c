/*
 * L3GD20.c
 *
 *  Created on: 19 wrz 2023
 *      Author: kruszynk
 */


#include "L3GD20.h"

void L3GD20_Read(uint8_t ReadAddress,uint8_t * buffer,uint32_t len){
	if(len>0) ReadAddress=ReadAddress|MS_BIT;
	ReadAddress=ReadAddress|ToRead_Bit;

	CS_ForSPI_Reset();/* Set chip select Low at the start of the transmission */

	CS_ForSPI_Set();/* Set chip select High at the end of the transmission */
}
void L3GD20_Send(uint8_t Data){
	/* Check if TX buffer is empty */
	if(SPI1->SR&SPI_SR_TXE){

	}
}
