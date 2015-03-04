/*
 * Author: Felix Schulze
 * Date:    04/03/2015
 *
 * Desc:   RaspberryPi Server Code
 * Ver.:      0.01
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>

#define STATUS_FILE "./status.xml"

typedef struct
{
    uint16_t  devnum;
    char location[25];
    char name[25];
    uint16_t   addr;
    uint16_t   type;
    uint16_t state;
} xmlObj;


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

			for(int i = 0; i<5; i++)
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
				
			}
			e++;
		}			
	}	
return 0;
}


int main(int argc, char** argv)
{
	int ret;
	xmlObj *state_ptr;

	printf("Raspberry Pi CAN-at-Home Server\nFelix Schulze 2015\nmail@felixschulze.com\n\n");

	// check if program runs as root
	if(getuid() != 0)
	{
		printf("Run program as root!\n");
		return 1;
	}

	// Count devices for allocationg memory
	ret = countDev();

	if(ret == -1)
	{
		printf("Could not open status.xml\n");
		return 1;
	}

	
	printf("Found %i Devices in XML File\n", ret);

	state_ptr = malloc(ret * (sizeof(xmlObj)));

	if(state_ptr == NULL)
	{
		printf("Not enough memory!\n");
		return 1;
	}

	getDev(ret, state_ptr);

	for(int i = 0; i < ret; i++)
	{
		printf("\nDev No: %i\n",state_ptr[i].devnum );
		printf("Location: %s\n",state_ptr[i].location);
		printf("Name: %s\n",state_ptr[i].name);
		printf("Addr: %i\n",state_ptr[i].addr );
		printf("Type: %i\n",state_ptr[i].type);
		printf("State: %i\n",state_ptr[i].state);
	}


	free(state_ptr);

return 0;
}