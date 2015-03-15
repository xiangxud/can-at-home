/*	
 * Author: Felix Schulze
 * Date:   28/02/2015
 *
 * 
 *
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <mail@felixschulze.com> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Felix Schulze
 * ----------------------------------------------------------------------------
 */

#include <stdio.h>
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
	#ifdef NORMAL_MODE
   		mcp_bit_mod( CANCTRL, 0xE0, 0);
   	#endif

   	// for debugging enable loopback mode
	#ifdef LOOPBACK_MODE
   		mcp_bit_mod(CANCTRL, 0xE0, 0x40);
   	#endif


   	#ifdef DEBUG
	   	printf(":: DEBUG -- Init\n\r");
		printf("RXM0SIDH : %x\n\r",mcp_read_reg( RXM0SIDH));
		printf("RXM0SIDL : %x\n\r",mcp_read_reg( RXM0SIDL));
		printf("RXM0EID8 : %x\n\r",mcp_read_reg( RXM0EID8));
		printf("RXM0EID0 : %x\n\r",mcp_read_reg( RXM0EID0));
		printf("RXM1SIDH : %x\n\r",mcp_read_reg( RXM1SIDH));
		printf("RXM1SIDH : %x\n\r",mcp_read_reg( RXM1SIDL));
		printf("RXM1EID8 : %x\n\r",mcp_read_reg( RXM1EID8));
		printf("RXM1EID0 : %x\n\r",mcp_read_reg( RXM1EID0));
		printf("CNF3 : %x\n\r",mcp_read_reg(CNF3));
		printf("CNF2 : %x\n\r",mcp_read_reg(CNF2));
		printf("CNF1: %x\n\r",mcp_read_reg(CNF1));
		printf("CANINTE: %x\n\r",mcp_read_reg(CANINTE));
	#endif
	
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

   	
   	char buf[18] = {SPI_LOAD_TX_BUF | addr, (uint8_t) (s_msg->id>>21), (uint8_t) ((s_msg->id>>13) & 0xE0)  | (1<<EXIDE) | (uint8_t) ((s_msg->id>>16) & 0x03), (uint8_t) (s_msg->id>>8), (uint8_t) s_msg->id};
   	uint8_t bufsize = 5+1+s_msg->length;


   	// if request ?
   	if(s_msg->rtr)
   		buf[5] = (1<<RTR) | s_msg->length;
   	else
   	{
   		buf[5] = (s_msg->length);

   		for(uint8_t i = 0; i < s_msg->length; i++)
   			buf[i+6] = (s_msg->data[i]);
   	}


   	bcm2835_spi_transfern(buf, bufsize);

   	// Debug Read back for first TXS block
   	#ifdef DEBUG
	   	printf(":: DEBUG -- Send msg\n");
		printf("TXB0SIDH : %x\n",mcp_read_reg(TXB0SIDH));
		printf("TXB0SIDL : %x\n",mcp_read_reg(TXB0SIDL));
		printf("TXB0EID8 : %x\n",mcp_read_reg(TXB0EID8));
		printf("TXB0EID0 : %x\n",mcp_read_reg(TXB0EID0));
		printf("TXB0DLC : %x\n",mcp_read_reg(TXB0DLC));
		printf("TXB0D0 : %x\n",mcp_read_reg(TXB0D0));
		printf("TXB0D1 : %x\n",mcp_read_reg(TXB0D1));
		printf("TXB0D2 : %x\n",mcp_read_reg(TXB0D2));
		printf("TXB0D3 : %x\n",mcp_read_reg(TXB0D3));
		printf("TXB0D4 : %x\n",mcp_read_reg(TXB0D4));
		printf("TXB0D5 : %x\n",mcp_read_reg(TXB0D5));
		printf("TXB0D6 : %x\n",mcp_read_reg(TXB0D6));
		printf("TXB0D7 : %x\n",mcp_read_reg(TXB0D7));
	#endif
	



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

	// assemble can address
	s_msg -> id = ((uint32_t) buf[1] << 21) | ((uint32_t) (buf[2] & 0xE0) << 13) | ((uint32_t) (buf[2]  & 0x03) << 16) | ((uint32_t) buf[3] << 8) | buf[4];


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
