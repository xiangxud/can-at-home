#!/usr/bin/env python3

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

timestamp = int(time())

#change new data in xml file
func.manipulateXML_State(int(sys.argv[1]), int(sys.argv[2]))
func.manipulateXML_Timestamp(int(sys.argv[1]), timestamp)

#log change in extra file
filename =  "./data/"+ sys.argv[1] + "-" + func.getSensName(int(sys.argv[1])) + "-" + func.getSensLocation(int(sys.argv[1])) + ".csv"
fd = open(filename, "a")
fd.write(str(timestamp) + ", " + sys.argv[2] + "\n")
fd.close()

sys.exit()