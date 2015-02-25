/*
 * Author: Felix Schulze
 * Date:   21/02/2015
 *
 *
 */

#include <util/delay.h>
#include "spi.h"
#include "mcp2515.h"

void mcp_write_reg(uint8_t addr, uint8_t data)
{
	PORT_CS &= ~(1<<P_CS);

	spi_trans(SPI_WRITE);
	spi_trans(addr);
	spi_trans(data);

	PORT_CS |= (1<<P_CS);
	
	return;
}

uint8_t mcp_read_reg(uint8_t addr)
{
	uint8_t data;

	PORT_CS &= ~(1<<P_CS);

	spi_trans(SPI_READ);
	spi_trans(addr);
	data = spi_trans(0xff);

	PORT_CS |= (1<<P_CS);
	
	return data;
}

void mcp_bit_mod(uint8_t addr, uint8_t mask, uint8_t data)
{
	PORT_CS &= ~(1<<P_CS);

	spi_trans(SPI_BIT_MOD);
	spi_trans(addr);
	spi_trans(mask);
	spi_trans(data);

	PORT_CS |= (1<<P_CS);
	
	return;
}

void mcp_init(void)
{

	spi_init();

	PORT_CS &= ~(1<<P_CS);
	spi_trans(SPI_RESET);
	_delay_ms(1);
	PORT_CS |= (1<<P_CS);
	_delay_ms(10);

	mcp_write_reg(CNF1, R_CNF1);
	mcp_write_reg(CNF2, R_CNF2);
	mcp_write_reg(CNF3, R_CNF3);

	mcp_write_reg(CANINTE, (1<<RX1IE)|(1<<RX0IE));

	mcp_write_reg( RXB0CTRL, (1<<RXM1)|(1<<RXM0) );
	mcp_write_reg( RXB1CTRL, (1<<RXM1)|(1<<RXM0) );

	mcp_write_reg( RXM0SIDH, 0 );
	mcp_write_reg( RXM0SIDL, 0 );
	mcp_write_reg( RXM0EID8, 0 );
	mcp_write_reg( RXM0EID0, 0 );

	mcp_write_reg( RXM1SIDH, 0 );
	mcp_write_reg( RXM1SIDL, 0 );
	mcp_write_reg( RXM1EID8, 0 );
	mcp_write_reg( RXM1EID0, 0 );


   	 mcp_bit_mod( CANCTRL, 0xE0, 0);

	return;
}

void can_send_message(stdCanmsg *s_msg)
{
	 uint8_t length = s_msg->length;

	mcp_write_reg(TXB0SIDH, (uint8_t) (s_msg->id>>3));
	mcp_write_reg(TXB0SIDL, (uint8_t) (s_msg->id<<5));
   
   	if (s_msg->rtr)
   	{
        		/* Eine RTR Nachricht hat zwar eine Laenge,
           		aber keine Daten */
       
       		// Nachrichten Laenge + RTR einstellen
      		  mcp_write_reg(TXB0DLC, (1<<RTR) | length);
   	}
   	else
   	{
        		// Nachrichten Laenge einstellen
      		 mcp_write_reg(TXB0DLC, length);
       
       		 // Daten
        		for (uint8_t i=0;i<length;i++)
        		{
            			mcp_write_reg(TXB0D0 + i, s_msg->data[i]);
            		}
	}
   
   	// CAN Nachricht verschicken
   	PORT_CS &= ~(1<<P_CS);
   	spi_trans(SPI_RTS | 0x01);
   	PORT_CS |= (1<<P_CS);
}