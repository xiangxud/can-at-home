#!/usr/bin/env python2.7

#
# Author: Felix Schulze
# Date:   13/03/2015
#
# ----------------------------------------------------------------------------
# "THE BEER-WARE LICENSE" (Revision 42):
# <mail@felixschulze.com> wrote this file. As long as you retain this notice you
# can do whatever you want with this stuff. If we meet some day, and you think
# this stuff is worth it, you can buy me a beer in return Felix Schulze
# ----------------------------------------------------------------------------
#/

import sys
import myfunc as func
from time import *



if(len(sys.argv) < 3):
	print ("Error use ./react.py addr state")
	sys.exit()

argaddr = sys.argv[1]
argstate = sys.argv[2]


timestamp = int(time())

#change new data in xml file
func.manipulateXML_State(int(argaddr), int(argstate))
func.manipulateXML_Timestamp(int(argaddr), timestamp)


#log change in extra file

filename =  "./data/"+ argaddr + "-" + func.getSensName(int(argaddr)) + "-" + func.getSensLocation(int(argaddr)) + ".csv"
fd = open(filename, "a")
fd.write(str(timestamp) + ", " + argstate + "\n")
fd.close()


sys.exit()