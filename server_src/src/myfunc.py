import xml.etree.ElementTree as ET

XML_FILE = "../data/status.xml"
CHGADDR_FILE = "../var/chgaddr.txt"

#As Example
#Readout the hole XML file
'''
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

def manipulateXML(search_addr, set_state):

	tree = ET.parse(XML_FILE)
	root = tree.getroot()

	for device in root.findall('device'):

		if(int(device.find('addr').text) == search_addr):
			dstate = device.find('state')
			dstate.text = str(set_state)
		

	tree.write(XML_FILE)
	return

def setDev(addr, data):
	print "Addr: " + str(addr);
	print "Data: " + str(data);
	manipulateXML(addr, data)
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