/*
 * Author: Felix Schulze
 * Date:   22/02/2015
 *
 *
 */

#ifndef UART_H
#define UART_H


#define BAUD_SELECT(baudRate,xtalCpu) ((xtalCpu)/((baudRate)*16l)-1)

// init the uart interface
void uart_init(unsigned int baudrate);

// send char via uart
void uart_putc(unsigned char data);

// send string via uart
void uart_puts(const char *s );


#endif

