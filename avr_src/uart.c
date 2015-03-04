/*
 * Author: Felix Schulze
 * Date:   22/02/2015
 *
 *
 */

#include <avr/io.h>
#include <stdlib.h>
#include "uart.h"
#include "mcp2515.h"


static char buffer[9];

void uart_init(unsigned int baudrate)
{
    
    UBRRL = (unsigned char) baudrate;
    UBRRH = (unsigned char)(baudrate>>8);


    UCSRB = (1<<TXEN) | (1<<RXEN);
    UCSRC = (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0);

    return;
   
}

void uart_putc(unsigned char data)
{
    // uart data register empty ?
    while(!(UCSRA & (1<<UDRE)));
    UDR = data;

    return;
}

void uart_puts(const char *s )
{
    while (*s) 
      uart_putc(*s++);

  return;

}

void uart_can_msg(Canmsg *s_msg)
{
    uart_puts("\n\rID: 0x");
    itoa(s_msg->id,buffer, 16);
    uart_puts(buffer);
    uart_puts("\n\rLength: 0x");
    itoa(s_msg->length,buffer, 16);
    uart_puts(buffer);

    uart_puts("\n\rRTR: ");
    itoa(s_msg->rtr,buffer, 16);
    uart_puts(buffer);

    for(int i = 0; i < s_msg->length; i++)
    {
        uart_puts("\n\rData: 0x");
        itoa(s_msg->data[i],buffer, 16);
        uart_puts(buffer);
    }
    
    uart_puts("\n\r");
    return;
}
