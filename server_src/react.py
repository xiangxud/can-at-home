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
import myfunc as func
from time import *



if(len(sys.argv) < 3):
	print ("Error use ./react.py addr state")
	sys.exit()

argaddr = sys.argv[1]
argstate = sys.argv[2]

timestamp = int(time())

print ("./react\n")

#change new data in xml file
func.manipulateXML_State(int(argaddr), int(argstate))
func.manipulateXML_Timestamp(int(argaddr), timestamp)

#log change in extra file

filename =  "./data/"+ argaddr + "-" + func.getSensName(int(argaddr)) + "-" + func.getSensLocation(int(argaddr)) + ".csv"
fd = open(filename, "a")
fd.write(str(timestamp) + ", " + argstate + "\n")
fd.close()



# swtich0-kitchen 502, light0-kitchen 500
if(argaddr == "502"):

	light0 = 500

	func.manipulateXML_State(light0, int(argstate))
	func.chgaddr(light0)
	sys.exit()

# dimmer0-kitchen 503, light1-kitchen 501
if(argaddr == "503"):

	light1 = 501
	
	func.manipulateXML_State(light1, int(argstate))
	func.chgaddr(light1)
	sys.exit()

# temperature-actual0-kitchen 504, temperature-target0-kitchen 505, heating0-kitchen 506
if(argaddr == "504" or argaddr == "505" ):
	
	temperatureActual0 = 504
	temperatureTarget0 = 505
	heating0 =  506
	print ("heating")

	#if acutal temperature less than target temperature heating on
	if(int(func.getSensState(temperatureActual0)) < int(func.getSensState(temperatureTarget0))):
		func.manipulateXML_State(heating0, 1)
		func.chgaddr(heating0)

	#if acutal temperature greater or equal than target temperature heating off
	if(int(func.getSensState(temperatureActual0)) >= int(func.getSensState(temperatureTarget0))):
		func.manipulateXML_State(heating0, 0)
		func.chgaddr(heating0)

	sys.exit()

sys.exit()
