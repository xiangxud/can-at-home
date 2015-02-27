/*
 * Author: Felix Schulze
 * Date:   22/02/2015
 *
 *
 */

#ifndef UART_H
#define UART_H

#include "mcp2515.h"

#define BAUD_SELECT(baudRate,xtalCpu) ((xtalCpu)/((baudRate)*16l)-1)

// init the uart interface
void uart_init(unsigned int baudrate);

// send char via uart
void uart_putc(unsigned char data);

// send string via uart
void uart_puts(const char *s );

// send the content of a can msg
void uart_can_msg(Canmsg *s_msg);


#endif

