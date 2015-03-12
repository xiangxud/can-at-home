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


#ifndef CANDEV_H
#define CANDEV_H

#define STATUS_FILE "./status.xml"
#define CHGADDR_FILE "./chgaddr.txt"
#define CHGADDR_FILE_TMP "./chgaddr.txt.tmp"


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

// change state in xml file
int16_t changeDevData(uint32_t addr, uint16_t data);

// reads out the chgaddr file
uint32_t getchgaddr();

 #endif
