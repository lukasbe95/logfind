CC=gcc
CFLAGS=-Wall -DNDEBUG

all:
	$(CC) $(CFLAGS) logfind.c -o logfind
clean:
	rm logfind
