#
# Author: Felix Schulze
# Date:    28/02/2015
#
# Desc:   Makefile
# Ver.:      0.01
#
#

TARGET = canserver
BUILDDIR = build

all: helper main.o candev.o loghelper.o bcm2835.o mcp2515.o
	gcc -o $(TARGET) $(BUILDDIR)/main.o $(BUILDDIR)/candev.o $(BUILDDIR)/loghelper.o  $(BUILDDIR)/mcp2515.o  $(BUILDDIR)/bcm2835.o
	gcc -o chgxml ./src/chgxml.c -std=gnu99 -Wall

helper:
	mkdir -p $(BUILDDIR)
	touch ./chgaddr.txt

main.o: ./src/main.c
	gcc -c -std=gnu99 ./src/main.c -Wall -o $(BUILDDIR)/main.o

candev.o: ./src/candev.c
	gcc -c -std=gnu99 ./src/candev.c -Wall -o $(BUILDDIR)/candev.o

loghelper.o: ./src/loghelper.c
	gcc -c -std=gnu99 ./src/loghelper.c -Wall -o $(BUILDDIR)/loghelper.o

bcm2835.o: ./src/bcm2835.c
	gcc -c -std=gnu99 ./src/bcm2835.c -Wno-pointer-to-int-cast -o $(BUILDDIR)/bcm2835.o

mcp2515.o: ./src/mcp2515.c
	gcc -c -std=gnu99 ./src/mcp2515.c -Wall -o $(BUILDDIR)/mcp2515.o




clean:
	rm -f $(TARGET)
	rm -f chgxml
	rm -rf $(BUILDDIR)/
	rm -f log.txt
	rm -f chgaddr.txt