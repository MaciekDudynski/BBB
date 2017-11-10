CC=gcc
CFLAGS=-Wall
LIBS=-lpruio
OUTFILES=zero first second third

zero: _zero/zero.c
	$(CC) $(CFLAGS) -o $@ $^

first: _first/first.c
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

second: _second/second.c
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

third: _third/third.c
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f $(OUTFILES)