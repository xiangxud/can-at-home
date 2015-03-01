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

	printf("Raspberry Pi CAN-Demo Code\n\rFelix Schulze 2015\n\rmail@felixschulze.com\n\r\n\r");

	// check if program runs as root
	if(getuid() != 0)
	{
		printf("Run program as root!\n\r");
		return 1;
	}

	// Init the spi interface
	if (!bcm2835_init())
		return 1;
	
	mcp_init();
	
	
	bcm2835_spi_end();
	return 0;
}
