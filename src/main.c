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
#include "uart.h"
#include "mcp2515.h"


int main(void)
{
	DDR_LED0 |= (1<<LED0);
	DDR_LED1 |= (1<<LED1);


	uart_init(UART_BAUD_SELECT(BAUD, F_CPU));
	sei();

	
	PORT_LED1 |= (1<<LED1);
	uart_puts("CAN-Demo Code\n\r");
	PORT_LED0 |= (1<<LED0);


	while(1);

  
	return 0;
}
