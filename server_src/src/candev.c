/*
 * Author: Felix Schulze
 * Date:   07/03/2015
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
#include <unistd.h>
#include <inttypes.h>
#include <time.h>

#include "candev.h"


int16_t countDev()
{
	int count = 0;
	FILE* f = fopen(STATUS_FILE, "r");
	if(f == NULL) return -1;

	char temp[100]; 

	while(fgets(temp,100,f) != NULL)
	{
		if(strstr(temp,"device") != NULL) 
			count ++;
	}
	
return count/2;
}

int16_t getDev(int count, xmlObj* xmlptr)
{
	FILE* f = fopen(STATUS_FILE, "r");
	char *wptr0 = NULL;
	char *wptr1 = NULL;
	if(f == NULL) return -1;
	int e = 0;

	char temp[100]; 

	while(fgets(temp,100,f) != NULL)
	{
		if(strstr(temp,"device no") != NULL) 
		{
			wptr0 = memchr(temp, '"', 50) + 1;
			wptr1 = memchr(wptr0, '"', 50) ;
			*wptr1 = 0;
			xmlptr[e].devnum = atoi(wptr0);

			for(int i = 0; i<20; i++)
			{
				fgets(temp,100,f);
				wptr0 = memchr(temp, '>', 50) + 1;
				wptr1 = memchr(wptr0, '<', 50) ;
				if(strstr(temp,"location") != NULL) 
				{
					*wptr1 = 0;
					strcpy (xmlptr[e].location, wptr0);
				}
				else if(strstr(temp,"name") != NULL) 
				{
					*wptr1 = 0;
					strcpy (xmlptr[e].name, wptr0);
				}
				else if(strstr(temp,"addr") != NULL) 
				{
					*wptr1 = 0;
					xmlptr[e].addr = atoi(wptr0);
				}
				else if(strstr(temp,"type") != NULL) 
				{
					*wptr1 = 0;
					xmlptr[e].type = atoi(wptr0);
				}
				else if(strstr(temp,"state") != NULL) 
				{
					*wptr1 = 0;
					xmlptr[e].state = atoi(wptr0);
				}
				else if(strstr(temp,"timestamp") != NULL) 
				{
					*wptr1 = 0;
					xmlptr[e].timestamp = atoi(wptr0);
				}
				else if (strstr(temp,"device") != NULL) 
				{
					break;
				}
			}
			e++;
		}			
	}	
return 0;
}

int16_t changeDevData(uint32_t addr, uint16_t data)
{
	char buffer[50];
	sprintf(buffer, "./chgxml.py %" PRIu32" %i",addr, data);
	system(buffer);

	return 0;
}

uint32_t getchgaddr()
{
		
	char straddr[9];
	char buffer[50];
	FILE *fd, *fdt;
	uint8_t a = 0;

	sprintf(buffer, "chmod 777 %s",CHGADDR_FILE);


	fd = fopen(CHGADDR_FILE, "r");

	while(fgets(straddr, 8, fd))
		a++;

	fclose(fd);

	if(a<1)
		return 0;
		


	fd = fopen(CHGADDR_FILE, "r");
	fdt = fopen(CHGADDR_FILE_TMP, "w");

	for(int i= 0; i<a-1 && fgets(straddr, 8, fd) != 0; i++)
		fputs(straddr, fdt);

	fgets(straddr, 8, fd);

	fclose(fd);
	fclose(fdt);

	remove(CHGADDR_FILE);
	rename(CHGADDR_FILE_TMP, CHGADDR_FILE);
	system(buffer);

	
	return atoi(straddr);
}