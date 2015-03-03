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

	// set can clock rate
	mcp_write_reg(CNF1, R_CNF1);
	mcp_write_reg(CNF2, R_CNF2);
	mcp_write_reg(CNF3, R_CNF3);

	mcp_write_reg(CANINTE, (1<<RX1IE)|(1<<RX0IE));

	// clear msg masks
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

	// enable normal mode
   	//mcp_bit_mod( CANCTRL, 0xE0, 0);

	// for debugging enable loopback mode
	mcp_bit_mod(CANCTRL, 0xE0, 0x40);
	return;
}


uint8_t can_send_msg(Canmsg *s_msg)
{

	uint8_t addr;

	if(s_msg->length > 8)
		return 2;

	// search for free tx buffer
	PORT_CS &= ~(1<<P_CS);
   	spi_trans(SPI_READ_STAT);
   	addr = spi_trans(0xff);
   	PORT_CS |= (1<<P_CS);

   	if(!(addr & (1<<TXB0CNTRL_TXREQ)))
   		addr = 0;
   	else if (!(addr & (1<<TXB1CNTRL_TXREQ)))
   		addr = 0x02;
   	else if (!(addr & (1<<TXB2CNTRL_TXREQ)))
   		addr = 0x04;
   	else
   		//no free tx buffer found
   		return 1;


	PORT_CS &= ~(1<<P_CS);
	spi_trans(SPI_LOAD_TX_BUF  | addr);
	
	// send std id to mcp2515
	mcp_write_reg(TXB0SIDH, (uint8_t) (s_msg->id>>3));
	mcp_write_reg(TXB0SIDL, (uint8_t) (s_msg->id<<5));
   
   	// jump of register for ext id
   	spi_trans(0);
   	spi_trans(0);

   	// if request ?
   	if(s_msg->rtr)
   		spi_trans((1<<RTR) | s_msg->length);
   	else
   	{
   		spi_trans(s_msg->length);

   		for(uint8_t i = 0; i < s_msg->length; i++)
   			spi_trans(s_msg->data[i]);
   	}

   	PORT_CS |= (1<<P_CS);

   	// do nothing one cycle for toggle cs
   	asm volatile ("nop");

   	PORT_CS &= ~(1<<P_CS);

   	if(addr == 0)
   		spi_trans(SPI_RTS | 0x01);
   	else
   		spi_trans(SPI_RTS | addr);

   	PORT_CS |= (1<<P_CS);

   	return 0;
}

uint8_t mcp_read_rx_stat(void)
{
	uint8_t data;
	PORT_CS &= ~(1<<P_CS);
	spi_trans(SPI_RX_STAT);
	data = spi_trans(0xff);
	PORT_CS |= (1<<P_CS);

	return data;
}

uint8_t can_get_msg(Canmsg *s_msg)
{
	uint8_t status = mcp_read_rx_stat();

	// message in buffer0
	if(status & (1<<6)) 
	{
		PORT_CS &= ~(1<<P_CS);
		spi_trans(SPI_READ_RX_BUF);
	}
	// message in buffer1
	else if(status & (1<<7))
	{
		PORT_CS &= ~(1<<P_CS);
		spi_trans(SPI_READ_RX_BUF | 0x04);
	}
	// no message
	else
	{
		return 1;
	}

	// read std id
	s_msg -> id = (uint16_t) spi_trans(0xff) << 3;
	s_msg -> id |= (uint16_t) spi_trans(0xff) >> 5;

	// jump over register for ext id
	spi_trans(0xff);
	spi_trans(0xff);

	s_msg->length = spi_trans(0xff) & 0x0f;

	for(uint8_t i =0 ; i < s_msg->length; i++)
		s_msg->data[i] = spi_trans(0xff);

	PORT_CS |= (1<<P_CS);

	// rtr msg ?
	if(status & (1<<3))
		s_msg->rtr = 1;
	else
		s_msg->rtr = 0;

	// clear interrupt flag for mcp2515
	if(status & (1<<6))
		mcp_bit_mod(CANINTF, (1<<RX0IF), 0);
	else
		mcp_bit_mod(CANINTF, (1<<RX1IF), 0);

	return 0;

}
