# Makefile for common

OBJS = pagedir.o
LIB = common.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb -I../libcs50
CC = gcc

$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS)

pagedir.o: pagedir.h
	$(CC) $(CFLAGS) pagedir.c -c

.PHONY: clean

clean:
	rm -f *~ *.o
	rm -f *.a