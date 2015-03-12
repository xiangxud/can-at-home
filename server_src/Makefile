#
# Author: Felix Schulze
# Date:    28/02/2015
#
# Desc:   Makefile
# Ver.:      0.02
#
#

TARGET = canserver
BUILDDIR = ./build
SRCDIR = ./src

all: helper main.o candev.o loghelper.o bcm2835.o mcp2515.o
	gcc -o $(TARGET) $(BUILDDIR)/main.o $(BUILDDIR)/candev.o $(BUILDDIR)/loghelper.o  $(BUILDDIR)/mcp2515.o  $(BUILDDIR)/bcm2835.o
	gcc -o chgxml $(SRCDIR)/chgxml.c -std=gnu99 -Wall

helper:
	mkdir -p $(BUILDDIR)
	echo END > ./chgaddr.txt

main.o: $(SRCDIR)/main.c
	gcc -c -std=gnu99 $(SRCDIR)/main.c -Wall -o $(BUILDDIR)/main.o

candev.o: $(SRCDIR)/candev.c
	gcc -c -std=gnu99 $(SRCDIR)/candev.c -Wall -o $(BUILDDIR)/candev.o

loghelper.o: $(SRCDIR)/loghelper.c
	gcc -c -std=gnu99 $(SRCDIR)/loghelper.c -Wall -o $(BUILDDIR)/loghelper.o

bcm2835.o: $(SRCDIR)/bcm2835.c
	gcc -c -std=gnu99 $(SRCDIR)/bcm2835.c -Wno-pointer-to-int-cast -o $(BUILDDIR)/bcm2835.o

mcp2515.o: $(SRCDIR)/mcp2515.c
	gcc -c -std=gnu99 $(SRCDIR)/mcp2515.c -Wall -o $(BUILDDIR)/mcp2515.o




clean:
	rm -f $(TARGET)
	rm -f chgxml
	rm -rf $(BUILDDIR)/
	rm -f log.txt
	rm -f chgaddr.txt