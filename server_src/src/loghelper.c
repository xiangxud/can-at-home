/*
 * Author: Felix Schulze
 * Date:    07/03/2015
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
#include <string.h>
#include <time.h>
#include <inttypes.h>

#include "loghelper.h"
#include "mcp2515.h"



void new_log_entry(char *s)
{

	
	FILE *lgf;
	struct tm *tmp;
	time_t sec;
	char timeString[24];
	char msg[250];
	if(strlen(s) > 220)
		return;
	

	// get time in sec
    sec = time(NULL);
    // get time back in struct
    tmp = localtime(&sec);

   	strftime(timeString, sizeof(timeString), "[ %d.%m.%Y %H:%M:%S ]", tmp);
	
	strcpy(msg, timeString);
	memset(&msg[23], ' ', 6);
	strcpy(&msg[29], s);

	// search end of string for calculating string length
	char *search = strchr(msg, '\n') + 1;

	lgf = fopen(LOG_FILE, "a");
	fwrite(msg , 1 , search-msg , lgf );
	fclose(lgf);

	return;
}


void new_can_log_entry(int dir, Canmsg *s_msg)
{
	char msg[250];
	if (dir == 0)
		sprintf(msg, "Send Message Address: %" PRIu32" Length: %i Data0: %i Data1: %i\n", s_msg->id, s_msg->length, s_msg->data[0], s_msg->data[1]);
	else
		sprintf(msg, "Receive Message Address: %" PRIu32" Length: %i Data0: %i Data1: %i\n", s_msg->id, s_msg->length, s_msg->data[0], s_msg->data[1]);
	
	new_log_entry(msg);

	return;
}