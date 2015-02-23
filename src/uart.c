/*
 * Author: Felix Schulze
 * Date:   22/02/2015
 *
 *
 */

#include <avr/io.h>
#include "uart.h"

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