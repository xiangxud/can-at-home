/*
 * Author: Felix Schulze
 * Date:    07/03/2015
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include "loghelper.h"


FILE *lgf;

uint8_t begin_new_log()
{
	lgf = fopen(LOG_FILE, "w+");
	if(lgf == NULL)
		return -1;

	return 0;
}

void new_log_entry(char *s)
{

	

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

	fwrite(msg , 1 , search-msg , lgf );

	return;
}

void close_log()
{
	fclose(lgf);
	return;
}