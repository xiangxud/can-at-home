/*
 * Author: Felix Schulze
 * Date:    07/03/2015
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

int16_t changeDevData(uint32_t addr, uint16_t data)
{

	FILE* f = fopen(STATUS_FILE, "r+");

	char *wptr0 = NULL;

	fpos_t pos0;
	fpos_t pos1;
	fpos_t tmppos;

	char msg[50];
	char temp[100]; 

	int length0;
	int length1; 
	int length2;

	int e = 0;
	
	int stateforaddr = 0;

	if(f == NULL) return -1;

	sprintf(msg, "<state>%i</state>", data);
	length1 = strlen(msg);

	while(fgets(temp,100,f) != NULL)
	{
		if(strstr(temp,"Device No") != NULL) 
		{
			for(int i = 0; i<20; i++)
			{
				fgetpos(f, &tmppos);
				fgets(temp,100,f);
				wptr0 = memchr(temp, '>', 50) + 1;				

				if(strstr(temp,"addr") != NULL) 
				{

					if(addr == atoi(wptr0))
					{
						// if state is for addr in xml file
						if(stateforaddr == 1)
						{
							// set cursor to begin of line
							fsetpos(f, &pos1);
							// write message
							fputs(msg,f);
							// if needed write spaces to overwrite the last entry
							if(length2 - length1 > 0)
							{
								for(int x = 0; x < length2-length1-1; x++)
								{
									fputs( " ",f);
								}
							}
							return 0;
						}
						
						// if state is after addr in xml file we have to search it
						for(int k = 0; k<20; k++)
						{
							// safe position in case to catch the right message
							fgetpos(f, &pos0);
							// read line in
							fgets(temp,100,f);
							// determine lenght of text, needed for later calculating
							length0 = strlen(temp);
				
							if(strstr(temp,"state") != NULL) 
							{
							
								// set cursor to begin of line
								fsetpos(f, &pos0);
								// write message
								fputs(msg,f);
								// if needed write spaces to overwrite the last entry
								if(length0 - length1 > 0)
								{
									for(int x = 0; x < length0-length1-1; x++)
									{
										fputs( " ",f);
									}
								}
								return 0;

							}
							// if we found Device again there is no state entry
							else if (strstr(temp,"Device") != NULL) 
								return 2;
						}
					}
				}
				
				else if(strstr(temp,"state") != NULL) 
				{
					// if we found a state entry we save the position of the line
					// in case it is the matching state for our address
					pos1=tmppos;
					stateforaddr = 1;
					// determine lenght of text, needed for later calculating
					length2 = strlen(temp);
					
				}
				else if (strstr(temp,"Device") != NULL) 
				{
					// if we found Device again we can discard our saved position
					stateforaddr = 0;
					break;
				}
			}
			e++;
		}			
	}	
return 0;
}