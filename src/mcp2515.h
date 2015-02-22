/*
 * Author: Felix Schulze
 * Date:   21/02/2015
 *
 *
 */

#ifndef MCP2515_H
#define MCP2515_H

//Define bitrate in kbps
//#define BITRATE	125
//#define BITRATE	250
//#define BITRATE	500
//#define BITRATE	1000

#define MCP_SPI_RESET 0b11000000
#define MCP_SPI_READ 0b00000011
#define MCP_SPI_READ_RX_BUF 0b10010000
#define MCP_SPI_WRITE 0b00000010
#define MCP_SPI_LOAD_TF_BUF 0b01000000
#define MCP_SPI_RTS	0b10000000
#define MCP_SPI_READ_STAT 0b10100000
#define MCP_SPI_RX_STAT 0b10110000
#define MCP_SPI_BIT_MOD 0b00000101

#define BFPCTRL 0x0C
#define TXRTSCTRL 0x0D
#define CANSTAT 0x0E
#define CANCTRL 0x0F
#define TEC 0x1C
#define REC 0x1D
#define CNF3 0x28
#define CNF2 0x29
#define CNF1 0x2A
#define CANINTE 0x2B
#define CANINTF 0x2C
#define EFLG 0x2D
#define TXB0CTRL 0x30 
#define TXB1CTRL 0x40
#define TXB2CTRL 0x50
#define RXB0CTRL 0x60
#define RXB1CTRL 0x70

#define BRP0 0
#define BRP1 1
#define BRP2 2
#define BRP3 3
#define BRP4 4
#define BRP5 5
#define SJW0 6
#define SJW1 7

#define PRSEG0 0
#define PRSEG1 1
#define PRSEG2 2
#define PHSEG10 3
#define PHSEG11 4
#define PHSEG12 5
#define SAM 6
#define BTLMODE 7

#define PHSEG20 0
#define PHSEG21 1
#define PHSEG22 2
#define WAKFIL 6
#define SOF 7

#define R_CNF1 (1<<BRP2) | (1<<BRP1) | (1<<BRP0)
#define R_CNF2 (1<<BTLMODE) | (1<<PHSEG11)
#define R_CNF3 (1<<PHSEG21)

#endif