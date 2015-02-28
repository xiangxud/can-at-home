#
# Author: Felix Schulze
# Date:    28/02/2015
#
# Desc:   Makefile
# Ver.:      0.01
#
#

TARGET = demo

all: main.o bcm2835.o
	gcc -o $(TARGET) main.o bcm2835.o 

main.o: main.c
	gcc -c -std=gnu99 main.c -Wall

bcm2835.o: bcm2835.c
	gcc -c -std=gnu99 bcm2835.c -Wall



clean:
	rm $(TARGET)
	rm main.o
	rm bcm2835.o
