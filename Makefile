CC=gcc
CFLAGS=-Wall
LIBS=-lpruio

first: _first/first.c
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

second: _second/second.c
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
