/*
 * Author: Felix Schulze
 * Date:    07/03/2015
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include "candev.h"


int16_t countDev()
{
	int count = 0;
	FILE* f = fopen(STATUS_FILE, "r");
	if(f == NULL) return -1;

	char temp[100]; 

	while(fgets(temp,100,f) != NULL)
	{
		if(strstr(temp,"Device") != NULL) 
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

	//printf("\nPrint %i: ", i);
	while(fgets(temp,100,f) != NULL)
	{
		if(strstr(temp,"Device No") != NULL) 
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
				else if (strstr(temp,"Device") != NULL) 
				{
					break;
				}
			}
			e++;
		}			
	}	
return 0;
}
