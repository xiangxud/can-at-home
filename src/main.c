/*
 * Author: Felix Schulze
 * Date:   21/02/2015
 *
 * Desc:   Can-Demo Code
 * Ver.:   0.01
 *
 */

#define F_CPU 16E6
#define BAUD  9600


#include <avr/io.h>
#include "uart.h"


int main(void)
{
  uart_init(UART_BAUD_SELECT(BAUD, F_CPU));
  sei();

  uart_puts("CAN-Demo Code");

  return 0;
}
