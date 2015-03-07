/*
 * Author: Felix Schulze
 * Date:    04/03/2015
 *
 * Desc:   RaspberryPi Server Code
 * Ver.:      0.02
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <inttypes.h>

#include "candev.h"
#include "loghelper.h"



int main(int argc, char** argv)
{
	int ret;
	xmlObj *state_ptr;
	char log[200];

	printf("Raspberry Pi CAN-at-Home Server\nFelix Schulze 2015\nmail@felixschulze.com\n\n");

	// check if program runs as root
	if(getuid() != 0)
	{
		printf("Run program as root!\n");
		return 1;
	}

	// count devices for allocationg memory
	ret = countDev();

	if(ret == -1)
	{
		printf("Could not open status.xml\n");
		return 1;
	}

	if(begin_new_log() == -1)
	{
		printf("Could not open log.txt\n");
		return 1;
	}

	
	sprintf(log, "Found %i Devices in XML File\n", ret);
	new_log_entry(log);

	// allocate memory for xmlObj structs
	state_ptr = malloc(ret * (sizeof(xmlObj)));

	if(state_ptr == NULL)
	{
		printf("Not enough memory!\n");
		return 1;
	}

	// get the devices in a struct back
	getDev(ret, state_ptr);

	for(int i = 0; i < ret; i++)
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


	// close files and clear memory
	free(state_ptr);
	void close_log();

return 0;
}