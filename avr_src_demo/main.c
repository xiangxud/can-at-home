/*
 * Author: Felix Schulze
 * Date:    28/02/2015
 *
 * Desc:   AVR Atmega8 Can-Demo Code
 * Ver.:      0.02
 *
 *
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <mail@felixschulze.com> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Felix Schulze
 * ----------------------------------------------------------------------------
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
#include "i2cmaster.h"
#include "uart.h"
#include "mcp2515.h"

#define LM75 0x90


int main(void)
{


	Canmsg msg;
	Canmsg newmsg;


	DDR_LED0 |= (1<<LED0);
	DDR_LED1 |= (1<<LED1);

	msg.id = 504;
	msg.rtr = 0;
	msg.length = 2;
	msg.data[0] = 0x01;
	msg.data[1] = 0x02;

	uint16_t temperature = 0;
	uint8_t dp = 0;
	uart_init(BAUD_SELECT(BAUD, F_CPU));

	i2c_init();

	
	uart_puts("AVR-CAN-Demo Code\n\rFelix Schulze 2015\n\rmail@felixschulze.com\n\r\n\r");
	mcp_init();

	can_send_msg(&msg);



	i2c_start(LM75+I2C_WRITE);
	i2c_write(0x00);
    i2c_rep_start(LM75+I2C_READ);
	
	temperature = i2c_readAck();
	dp = i2c_readNak();
	i2c_stop();

	temperature += 273;
	temperature *= 10;
	if(dp & 0x80)
		temperature += 5;
	

	
	PORT_LED0 |= (1<<LED0);
	
	
	
	uart_puts(":: send test message\n\r");


	while(1)
	{	
		if(can_get_msg(&newmsg) == 0)
		{
			uart_can_msg(&newmsg);
		}

		i2c_start(LM75+I2C_READ);
		temperature = i2c_readAck();
		dp = i2c_readNak();
		i2c_stop();

		temperature += 273;
		temperature *= 10;
		if(dp & 0x80)
			temperature += 5;

		msg.data[0] = temperature >> 8;
		msg.data[1] = temperature & 0xff;

		can_send_msg(&msg);

		for(int i = 0; i < 30; i++)
			_delay_ms(100);
	}

  
	return 0;
}
