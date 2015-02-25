/*
 * Author: Felix Schulze
 * Date:   21/02/2015
 *
 * Desc:   Can-Demo Code
 * Ver.:   0.01
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

	stdCanmsg msg;
	uint8_t i = 0;
	char buffer[9];
	DDR_LED0 |= (1<<LED0);
	DDR_LED1 |= (1<<LED1);

	msg.id = 0x0123;
	msg.rtr = 0;
	msg.length = 2;
	msg.data[0] = 0x04;
	msg.data[1] = 0xf3;


	uart_init(BAUD_SELECT(BAUD, F_CPU));
	
	PORT_LED1 |= (1<<LED1);
	uart_puts("CAN-Demo Code\n\rFelix Schulze 2015\n\rmail@felixschulze.com\n\r\n\r");
	PORT_LED0 |= (1<<LED0);

	mcp_init();
	PORT_LED1 |= (1<<LED1);
	uart_puts(":: Init mcp2515\n\r");
	PORT_LED0 |= (1<<LED0);

	i = mcp_read_reg(CANSTAT);
	itoa(i, buffer, 2);
	uart_puts(buffer);

	
	can_send_message(&msg);
	uart_puts(":: send test message\n\r");


	while(1);

  
	return 0;
}
