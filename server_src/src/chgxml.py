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



if(len(sys.argv) < 3):
	print ("Error")
	sys.exit()

func.manipulateXML(int(sys.argv[1]), int(sys.argv[2]))

sys.exit()