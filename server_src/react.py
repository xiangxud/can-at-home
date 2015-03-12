#!/usr/bin/env python2.7

#
# Author: Felix Schulze
# Date:   12/03/2015
#
# ----------------------------------------------------------------------------
# "THE BEER-WARE LICENSE" (Revision 42):
# <mail@felixschulze.com> wrote this file. As long as you retain this notice you
# can do whatever you want with this stuff. If we meet some day, and you think
# this stuff is worth it, you can buy me a beer in return Felix Schulze
# ----------------------------------------------------------------------------
#/

import sys
import string
import os

CHGADDR_FILE = "./chgaddr.txt"

def setDev(addr, data):
	print "Addr: " + str(addr);
	print "Data: " + str(data);
	os.system("./chgxml " + str(addr) + " "+ str(data))
	return

def chgaddr(addr):
	fd = open(CHGADDR_FILE, "r")
	lines = fd.readlines()
	fd.close()

	fd =  open(CHGADDR_FILE, "w")
	fd.write(str(addr) + "\n")

	for l in lines:
		fd.write(l)

	fd.close


if(len(sys.argv) < 3):
	print ("Error")
	sys.exit()


# swtich kitchen, light kitchen
if(sys.argv[1] == "501"):
	setDev(500, string.atoi(sys.argv[2]))
	chgaddr(500)
	sys.exit()

if(sys.argv[1] == "123123"):
	#set addr to device
	#set addr to change
	sys.exit()
