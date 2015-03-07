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

all: helper main.o candev.o loghelper.o
	gcc -o $(TARGET) $(BUILDDIR)/main.o $(BUILDDIR)/candev.o $(BUILDDIR)/loghelper.o

helper:
	mkdir -p $(BUILDDIR)

main.o: main.c
	gcc -c -std=gnu99 main.c -Wall -o $(BUILDDIR)/main.o

candev.o: candev.c
	gcc -c -std=gnu99 candev.c -Wall -o $(BUILDDIR)/candev.o

loghelper.o: loghelper.c
	gcc -c -std=gnu99 loghelper.c -Wall -o $(BUILDDIR)/loghelper.o



clean:
	rm -f $(TARGET)
	rm -rf $(BUILDDIR)/