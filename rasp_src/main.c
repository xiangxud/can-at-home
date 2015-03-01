/*
 * Author: Felix Schulze
 * Date:    28/02/2015
 *
 * Desc:   RaspberryPi Can-Demo Code
 * Ver.:      0.01
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include "mcp2515.h"
#include "bcm2835.h"

int main(int argc, char ** argv)
{
	uint8_t i = 0;

	printf("Raspberry Pi CAN-Demo Code\n\rFelix Schulze 2015\n\rmail@felixschulze.com\n\r\n\r");

	// check if program runs as root
	if(getuid() != 0)
	{
		printf("Run program as root!\n\r");
		return 1;
	}

	if (!bcm2835_init())
		return 1;

	bcm2835_spi_begin();
	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_32);
	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
	bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
	bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
	bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW); 
	bcm2835_spi_transfer(0xaa);
	bcm2835_spi_transfer(1);
	bcm2835_spi_end();

	return 0;
}
