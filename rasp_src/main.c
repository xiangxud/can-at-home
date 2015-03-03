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

 void print_can_msg(Canmsg *s_msg)
{
    printf("\n\rID: 0x%x\n\rLength: 0x%x\n\rRTR: %x", s_msg -> id,s_msg->length, s_msg->rtr);

    for(int i = 0; i < s_msg->length; i++)
        printf("\n\rData[%i]: 0x%x", i, s_msg->data[i]);
  
    printf("\n\r");

    return;
}

int main(int argc, char ** argv)
{

	Canmsg msg;
	Canmsg newmsg;

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
	printf(":: Init mcp2515\n\r");

	can_send_msg(&msg);
	printf(":: send test message\n\r");

	while(1)
	{	
		if(can_get_msg(&newmsg) == 0)
			print_can_msg(&newmsg);
	}

	
	
	bcm2835_spi_end();
	return 0;
}
