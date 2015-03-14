/*
 * Author: Felix Schulze
 * Date:   21/02/2015
 *
 *
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <mail@felixschulze.com> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Felix Schulze
 * ----------------------------------------------------------------------------
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