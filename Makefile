CC=gcc
CFLAGS=-Wall
LIBS=-lpruio
OUTFILES=first second third

first: _first/first.c
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

second: _second/second.c
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

third: _third/third.c
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f $(OUTFILES)