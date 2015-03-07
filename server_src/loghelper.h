/*
 * Author: Felix Schulze
 * Date:    07/03/2015
 *
 *
 */

#ifndef LOGHELPER_H
#define LOGHELPER_H

#define LOG_FILE "./log.txt"

uint8_t begin_new_log();

void new_log_entry(char *s);

void close_log();


#endif