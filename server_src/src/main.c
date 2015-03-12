/*
 * Author: Felix Schulze
 * Date:    04/03/2015
 *
 * Desc:   RaspberryPi Server Code
 * Ver.:      0.02
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
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <inttypes.h>

#include "candev.h"
#include "loghelper.h"
#include "bcm2835.h"
#include "mcp2515.h"



int main(int argc, char** argv)
{
	int devcnt;
	xmlObj *state_ptr;
	char log[200];
	Canmsg newCanmsg;

	printf("Raspberry Pi CAN-at-Home Server\nFelix Schulze 2015\nmail@felixschulze.com\n\n");

	// check if program runs as root
	if(getuid() != 0)
	{
		printf("Run program as root!\n");
		return 1;
	}

	// count devices for allocationg memory
	devcnt = countDev();

	if(devcnt == -1)
	{
		printf("Could not open status.xml\n");
		return 1;
	}

	if(begin_new_log() == -1)
	{
		printf("Could not open log.txt\n");
		return 1;
	}

	
	sprintf(log, "Found %i Devices in XML File\n", devcnt);
	new_log_entry(log);

	// allocate memory for xmlObj structs
	state_ptr = malloc(devcnt * (sizeof(xmlObj)));

	if(state_ptr == NULL)
	{
		printf("Not enough memory!\n");
		return 1;
	}

	// get the devices in a struct back
	getDev(devcnt, state_ptr);

	for(int i = 0; i < devcnt; i++)
	{
		new_log_entry("Found the following Device:\n");
		sprintf(log, "	Dev No: %i\n",state_ptr[i].devnum );
		new_log_entry(log);
		sprintf(log, "	Location: %s\n",state_ptr[i].location);
		new_log_entry(log);
		sprintf(log, "	Name: %s\n",state_ptr[i].name);
		new_log_entry(log);
		// with inttypes.h new formatstring "%" PRIu32 for uint32_t
		sprintf(log, "	Addr: %" PRIu32"\n",state_ptr[i].addr );
		new_log_entry(log);
		sprintf(log, "	Type: %i\n",state_ptr[i].type);
		new_log_entry(log);
		sprintf(log, "	State: %i\n",state_ptr[i].state);
		new_log_entry(log);
	}

	// init spi interface
	/*if (!bcm2835_init())
		return 1;
	new_log_entry("BCM2835 SPI interface successfully initialized\n");
	
	// init can controller
	mcp_init();
	new_log_entry("MCP2515 CAN controller successfully initialized\n");
	*/

	
	while(1)
	{
		// check for new data
			//changeDevData(123123,6);
			//if new data comes in save in xml file and send to python script
			
		// check chgaddr.txt for new data
			//getDev(devcnt, state_ptr);
		 	//newCanmsg.id = xxx;
			//can_send_msg(newCanmsg);

	}
	

	// close files, clear memory and stop spi access
	free(state_ptr);
	void close_log();
	//bcm2835_spi_end();

return 0;
}