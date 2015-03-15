import xml.etree.ElementTree as ET

XML_FILE = "./data/status.xml"
CHGADDR_FILE = "./var/chgaddr.txt"

#As Example
#Readout the hole XML file
'''
tree = ET.parse(XML_FILE)
root = tree.getroot()

for device in root.findall('device'):
	dnumber = device.get('no')
	dlocation = device.find('location').text
	dname = device.find('name').text
	daddr = device.find('addr').text
	dtype = device.find('type').text
	dstate = device.find('state').text

	print "Device: " + dnumber
	print "  Location: " + dlocation
	print "  Name: " + dname
	print "  Addr: " + daddr
	print "  Type: " + dtype
	print "  State: " + dstate
'''

def manipulateXML_State(search_addr, set_state):

	tree = ET.parse(XML_FILE)
	root = tree.getroot()

	for device in root.findall('device'):

		if(int(device.find('addr').text) == search_addr):
			dstate = device.find('state')
			dstate.text = str(set_state)
		

	tree.write(XML_FILE)
	return

def manipulateXML_Timestamp(search_addr, set_timestamp):

	tree = ET.parse(XML_FILE)
	root = tree.getroot()

	for device in root.findall('device'):

		if(int(device.find('addr').text) == search_addr):
			dstate = device.find('timestamp')
			dstate.text = str(set_timestamp)
		

	tree.write(XML_FILE)
	return

def logEnabled(search_addr):
	tree = ET.parse(XML_FILE)
	root = tree.getroot()
	dtype = "0"

	for device in root.findall('device'):

		if(int(device.find('addr').text) == search_addr):
			dtype = device.find('type').text
	

	if(dtype == "3"):
		return 1
	else:
		return 0

def getSensName(search_addr):
	tree = ET.parse(XML_FILE)
	root = tree.getroot()
	dname = ""

	for device in root.findall('device'):

		if(int(device.find('addr').text) == search_addr):
			dname = device.find('name').text
	

	return dname

def getSensLocation(search_addr):
	tree = ET.parse(XML_FILE)
	root = tree.getroot()
	dlocation = ""

	for device in root.findall('device'):

		if(int(device.find('addr').text) == search_addr):
			dlocation = device.find('location').text
	

	return dlocation

def getSensState(search_addr):
	tree = ET.parse(XML_FILE)
	root = tree.getroot()
	dstate = ""

	for device in root.findall('device'):

		if(int(device.find('addr').text) == search_addr):
			dstate = device.find('state').text
	

	return dstate

def chgaddr(addr):
	fd = open(CHGADDR_FILE, "r")
	lines = fd.readlines()
	fd.close()

	fd =  open(CHGADDR_FILE, "w")
	fd.write(str(addr) + "\n")

	for l in lines:
		fd.write(l)

	fd.close