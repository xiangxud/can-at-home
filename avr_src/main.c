/*
 * Author: Felix Schulze
 * Date:    28/02/2015
 *
 * Desc:   AVR Atmega8 Can-Demo Code
 * Ver.:      0.02
 *
 */

#define BAUD  9600
#define F_CPU 7372800

#define LED0 PC2
#define LED1 PC3
#define PORT_LED0 PORTC
#define PORT_LED1 PORTC
#define DDR_LED0 DDRC
#define DDR_LED1 DDRC

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "uart.h"
#include "mcp2515.h"


int main(void)
{

	Canmsg msg;
	Canmsg newmsg;


	DDR_LED0 |= (1<<LED0);
	DDR_LED1 |= (1<<LED1);

	msg.id = 0x0123;
	msg.rtr = 0;
	msg.length = 2;
	msg.data[0] = 0x04;
	msg.data[1] = 0xf3;


	uart_init(BAUD_SELECT(BAUD, F_CPU));
	
	uart_puts("AVR-CAN-Demo Code\n\rFelix Schulze 2015\n\rmail@felixschulze.com\n\r\n\r");
	mcp_init();
	uart_puts(":: Init mcp2515\n\r");


	PORT_LED0 |= (1<<LED0);

	
	
	can_send_msg(&msg);
	
	uart_puts(":: send test message\n\r");



	while(1)
	{

		
	
		if(can_get_msg(&newmsg) == 0)
		{
			uart_can_msg(&newmsg);
		}
	}

  
	return 0;
}
