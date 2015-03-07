/*
 * Author: Felix Schulze
 * Date:    07/03/2015
 *
 *
 */


#ifndef CANDEV_H
#define CANDEV_H

#define STATUS_FILE "./status.xml"

typedef struct
{
	uint16_t  devnum;
	char location[25];
	char name[25];
	uint32_t   addr;
	uint16_t   type;
	uint16_t state;
} xmlObj;


// count devices in xml file
int16_t countDev();

// readout all devices in xml file
int16_t getDev(int count, xmlObj* xmlptr);

 #endif
