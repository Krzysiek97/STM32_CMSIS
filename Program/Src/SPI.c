/*
 * SPI.c
 *
 *  Created on: 18 wrz 2023
 *      Author: kruszynk
 */


#include "SPI.h"
#include "GPIO.h"

void SPI_init(){
	RCC->APB2ENR|=RCC_APB2ENR_SPI1EN;//SPI1 clock enabled
//Full-duplex (Transmit and receive) reset state
	SPI1->CR1|=SPI_CR1_BR_2|SPI_CR1_BR_0;//72MHz/64=1.125 MBits/s
//Clock polarity->  CK to 0 when idle (reset state)

/*
 * Clock phase-> The first clock transition is the first data capture edge (reset state)
 * Sampling data is on first clock's edge, changing data on second
 */
//LSBFIRST:0 Frame format 0: data is transmitted / received with the MSB first (reset state)
//SSM=0 (Software slave management) -> In Master, NSS is steered by peripheral SPI
	SPI1->CR1|=SPI_CR1_MSTR;//Master configuration
//Data Size -> 8 bit (reset state)
}
void SPI_enable(){
/*
 * It's recommended to enable SPI slave before the master sends the clock.
 * The data register of the slave must already contain data to be sent before starting communication with master.
 * (Either on the first edge of the communication clock or before the end of ongoing com. if the clock is cont.)
 * The SCK sig. must be settled at an idle state level corresponding to the selected polarity before the SPI slave is enabled.
 * The master at full-duplex starts to com. when the SPI is enabled and TXFIFO isn't empty or with the next write to TXFIFO.
 */
	CS_ForSPI_Set();//For L3GD20 sensor
	SPI1->CR1|=SPI_CR1_SPE;// SPI enable
}
void SPI_SendData(uint8_t *data,uint8_t len){
	for(uint32_t i=0;i<len;++i)
	{
		while (!(SPI1->SR & SPI_SR_TXE)); // Wait until buffer will be empty
		SPI1->DR = data[i]; // send data
	}
}
void SPI_ReceiveData(uint8_t *buffer, uint8_t len){
	for (uint32_t i = 0; i < len; ++i)
	    {
	        while (!(SPI1->SR & SPI_SR_RXNE)); // Wait until data will be available
	        buffer[i]=SPI1->DR; // receive data
	    }
}
