/*
 * Author: Felix Schulze
 * Date:   22/02/2015
 *
 *
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <mail@felixschulze.com> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Felix Schulze
 * ----------------------------------------------------------------------------
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

