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

	spi_trans(MCP_SPI_WRITE);
	spi_trans(addr);
	spi_trans(data);

	PORT_CS |= (1<<P_CS);
	
	return;
}

uint8_t mcp_read_reg(uint8_t addr)
{
	uint8_t data;

	PORT_CS &= ~(1<<P_CS);

	spi_trans(MCP_SPI_READ);
	spi_trans(addr);
	data = spi_trans(0xff);

	PORT_CS |= (1<<P_CS);
	
	return data;
}

void mcp_bit_mod(uint8_t addr, uint8_t mask, uint8_t data)
{
	PORT_CS &= ~(1<<P_CS);

	spi_trans(MCP_SPI_WRITE);
	spi_trans(addr);
	spi_trans(mask)
	spi_trans(data);

	PORT_CS |= (1<<P_CS);
	
	return;
}

void mcp_init(void)
{

	spi_init();

	PORT_CS &= ~(1<<P_CS);
	spi_trans(MCP_SPI_RESET);
	_delay_ms(1);
	PORT_CS |= (1<<P_CS);
	_delay_ms(10);

	mcp_write_reg(CNF1, R_CNF1);
	mcp_write_reg(CNF2, R_CNF2);
	mcp_write_reg(CNF3, R_CNF3);
	


}