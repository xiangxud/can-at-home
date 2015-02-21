/*
 * Author: Felix Schulze
 * Date:   21/02/2015
 *
 *
 */


#include <avr/io.h>
#include "spi.h"

void spi_init(void)
{

	DDR_SPI |= (1<<P_SCK) | (1<<P_MOSI);
	PORT_SPI &= ~((1<<P_SCK) | (1<<P_MOSI) | (1<<P_MISO));

	DDR_CS |= (1<<P_CS);
	PORT_CS |= (1<<P_CS);

	SPCR = (1<<SPE) |  (1<<MSTR);
	SPSR = (1<<SPI2X);
}

uint8_t spi_trans(uint8_t data)
{
	SPDR = data;

	while(!(SPSR & (1<<SPIF)));

	return SPDR;
}