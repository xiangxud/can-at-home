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
import myfunc as func


if(len(sys.argv) < 3):
	print ("Error use ./react.py addr state timestamp")
	sys.exit()


#change new data in xml file
func.manipulateXML_State(int(sys.argv[1]), int(sys.argv[2]))
func.manipulateXML_Timestamp(int(sys.argv[1]), int(sys.argv[3]))

#log change in extra file
filename =  "./data/"+ sys.argv[1] + "-" + func.getSensName(int(sys.argv[1])) + "-" + func.getSensLocation(int(sys.argv[1])) + ".csv"
fd = open(filename, "a")
fd.write(sys.argv[3] + ", " + sys.argv[2] + "\n")
fd.close()


# swtich0-kitchen 502, light0-kitchen 500
if(sys.argv[1] == "502"):

	light0 = 500

	func.manipulateXML_State(light0, int(sys.argv[2]))
	func.chgaddr(light0)
	sys.exit()

# dimmer0-kitchen 503, light1-kitchen 501
if(sys.argv[1] == "503"):

	light1 = 501
	
	func.manipulateXML_State(light1, int(sys.argv[2]))
	func.chgaddr(light1)
	sys.exit()

# temperature-actual0-kitchen 504, temperature-target0-kitchen 505, heating0-kitchen 506
if(sys.argv[1] == "504" or sys.argv[1] == "505" ):
	
	temperatureActual0 = 504
	temperatureTarget0 = 505
	heating0 =  506

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