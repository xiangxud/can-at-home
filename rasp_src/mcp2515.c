/*	
 * Author: Felix Schulze
 * Date:   28/02/2015
 *
 *
 */

#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include "bcm2835.h"
 #include "mcp2515.h"

void mcp_write_reg(uint8_t addr, uint8_t data)
{
	char buf[] = {SPI_WRITE, addr, data};
	bcm2835_spi_writenb(buf, sizeof(buf));

	return;
}

uint8_t mcp_read_reg(uint8_t addr)
{
	char buf[] = {SPI_READ, addr, 0xff};

	bcm2835_spi_transfern(buf, sizeof(buf));
	
	return buf[2];
}

void mcp_bit_mod(uint8_t addr, uint8_t mask, uint8_t data)
{
	char buf[] = {SPI_BIT_MOD, addr, mask,data};
	bcm2835_spi_writenb(buf, sizeof(buf));
	
	return;
}

void mcp_init(void)
{


	bcm2835_spi_begin();
	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_32);
	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
	bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
	bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
	bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW); 

	
	bcm2835_spi_transfer(SPI_RESET);
	usleep(10);

	// set can clock rate

	/*
	mcp_write_reg( RXM0SIDH, 0 );
	mcp_write_reg( RXM0SIDL, 0 );
	mcp_write_reg( RXM0EID8, 0 );
	mcp_write_reg( RXM0EID0, 0 );

	mcp_write_reg( RXM1SIDH, 0 );
	mcp_write_reg( RXM1SIDL, 0 );
	mcp_write_reg( RXM1EID8, 0 );
	mcp_write_reg( RXM1EID0, 0 );

	mcp_write_reg(CNF3, R_CNF3);
	mcp_write_reg(CNF2, R_CNF2);
	mcp_write_reg(CNF1, R_CNF1);
	mcp_write_reg(CANINTE, (1<<RX1IE)|(1<<RX0IE));
	*/
	char buf[] = {SPI_WRITE, RXM0SIDH ,0, 0, 0, 0 ,0, 0, 0, 0, CNF3, CNF2, CNF1, (1<<RX1IE)|(1<<RX0IE)};

 	bcm2835_spi_transfern(buf, sizeof(buf));

	// clear msg masks
	mcp_write_reg( RXB0CTRL, (1<<RXM1)|(1<<RXM0) );
	mcp_write_reg( RXB1CTRL, (1<<RXM1)|(1<<RXM0) );

	// enable normal mode
   	//mcp_bit_mod( CANCTRL, 0xE0, 0);

	// for debugging enable loopback mode
	mcp_bit_mod(CANCTRL, 0xE0, 0x40);
	return;
}


uint8_t can_send_msg(Canmsg *s_msg)
{

	uint8_t addr;
	char buf0[] = {SPI_READ_STAT, 0xff};

	if(s_msg->length > 8)
		return 2;

	// search for free tx buffer
	bcm2835_spi_transfern(buf0, sizeof(buf0));

	addr = buf0[1];

   	if(!(addr & (1<<TXB0CNTRL_TXREQ)))
   		addr = 0;
   	else if (!(addr & (1<<TXB1CNTRL_TXREQ)))
   		addr = 0x02;
   	else if (!(addr & (1<<TXB2CNTRL_TXREQ)))
   		addr = 0x04;
   	else
   		//no free tx buffer found
   		return 1;

   	

   	char buf[16] = {SPI_WRITE | addr, SPI_WRITE, TXB0SIDH, (uint8_t) (s_msg->id>>3), (uint8_t) (s_msg->id<<5), 0, 0};
   	uint8_t bufsize = 7+1+s_msg->length;

   	// if request ?
   	if(s_msg->rtr)
   		buf[7] = (1<<RTR) | s_msg->length;
   	else
   	{
   		buf[7] = (s_msg->length);

   		for(uint8_t i = 0; i < s_msg->length; i++)
   			buf[i+8] = (s_msg->data[i]);
   	}

	for(int i = 0; i <bufsize; i++)
		printf(" %x", buf[i]);

   	bcm2835_spi_transfern(buf, bufsize);


   	if(addr == 0)
  
   		bcm2835_spi_transfer(SPI_RTS | 0x01);
   	else
   		bcm2835_spi_transfer(SPI_RTS | addr);

   	return 0;
}

uint8_t mcp_read_rx_stat(void)
{
	char buf[] = {SPI_RX_STAT, 0xff};
	bcm2835_spi_transfern(buf, sizeof(buf));

	return buf[1];
}

uint8_t can_get_msg(Canmsg *s_msg)
{
	uint8_t status = mcp_read_rx_stat();
	char buf[14];

	for(int i = 1; i<14; i++)
		buf[i] = 0xff;

	// message in buffer0
	if(status & (1<<6))
		buf[0] = SPI_READ_RX_BUF;
	
	// message in buffer1
	else if(status & (1<<7))
		buf[0]  = SPI_READ_RX_BUF | 0x04;
	
	// no message
	else
		return 1;


	bcm2835_spi_transfern(buf, sizeof(buf));

	// read std id
	s_msg -> id = (uint16_t) buf[1] << 3;
	s_msg -> id |= (uint16_t) buf[2] >> 5;
	s_msg->length = buf[5] & 0x0f;

	for(uint8_t i =0 ; i < s_msg->length; i++)
		s_msg->data[i] = buf[6+i];


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
