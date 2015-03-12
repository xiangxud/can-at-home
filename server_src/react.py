#!/usr/bin/env python2.7

import sys
import string
import os

def setDev(addr, data):
	print "Addr: " + str(addr);
	print "Data: " + str(data);
	os.system("./chgxml " + str(addr) + " "+ str(data))
	return

if(len(sys.argv) < 3):
	print ("Error")
	sys.exit()


# swtich kitchen, light kitchen
if(sys.argv[1] == "501"):
	setDev(500, string.atoi(sys.argv[2]))
	#set addr to change
	sys.exit()

if(sys.argv[1] == "123123"):
	#set addr to device
	#set addr to change
	sys.exit()
