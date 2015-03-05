#
# Author: Felix Schulze
# Date:    28/02/2015
#
# Desc:   Makefile
# Ver.:      0.01
#
#

TARGET = canserver

all: main.o 
	gcc -o $(TARGET) main.o

main.o: main.c
	gcc -c -std=gnu99 main.c -Wall



clean:
	rm -f $(TARGET)
	rm -f main.o
