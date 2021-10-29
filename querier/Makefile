# Makefile for querier

OBJS =  ../common/index.c ../libcs50/file.c ../common/word.c ../common/pagedir.c
LLIBS = ../libcs50/libcs50.a
LIBS = 

CFLAGS = -Wall -pedantic -std=c11 -ggdb -I../libcs50  -I../common
CC = gcc

.PHONY: test clean all

all: querier

querier: $(OBJS)
	$(CC) $(CFLAGS) querier.c $(OBJS) $(LLIBS) $(LIBS) -o querier

test: querier
	./testing.sh &> testing.out

clean:
	rm -f *~ *.o *.out
	rm -f core
	rm -f ./querier