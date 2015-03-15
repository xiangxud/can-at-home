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

#ifndef LOGHELPER_H
#define LOGHELPER_H

#include "mcp2515.h" 

#define LOG_FILE "./log.txt"

void new_log_entry(char *s);

void new_can_log_entry(int dir, Canmsg *s_msg);


#endif