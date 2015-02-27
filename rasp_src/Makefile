/*
 * Author: Felix Schulze
 * Date:    28/02/2015
 *
 * Desc:   Makefile
 * Ver.:      0.01
 *
 */

TARGET = demo
SRC = main.c

all: main.o
	gcc -o $(TARGET) main.o

main.o: main.c
	gcc -c -std=gnu99 $(SRC)


clean:
	rm $(TARGET)
	rm $(SRC:.c=.o)
