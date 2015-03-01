#
# Author: Felix Schulze
# Date:    28/02/2015
#
# Desc:   Makefile
# Ver.:      0.01
#
#

TARGET = demo

all: main.o bcm2835.o mcp2515.o
	gcc -o $(TARGET) main.o bcm2835.o mcp2515.o

main.o: main.c
	gcc -c -std=gnu99 main.c -Wall

bcm2835.o: bcm2835.c
	gcc -c -std=gnu99 bcm2835.c -Wno-pointer-to-int-cast

mcp2515.o: mcp2515.c
	gcc -c -std=gnu99 mcp2515.c -Wall




clean:
	rm -f $(TARGET)
	rm -f main.o
	rm -f bcm2835.o
	rm -f mcp2515.o