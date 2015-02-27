/*
 * Author: Felix Schulze
 * Date:   21/02/2015
 *
 *
 */

#ifndef SPI_H
#define SPI_H

 #include <avr/io.h>

#define DDR_SPI DDRB
#define PORT_SPI PORTB
#define P_SCK	 5
#define P_MOSI 3
#define P_MISO 4

#define DDR_CS DDRB
#define PORT_CS PORTB
#define P_CS 2

// Init the spi interface
void spi_init(void);

// send data to devive or receive data from device
uint8_t spi_trans(uint8_t data);


#endif