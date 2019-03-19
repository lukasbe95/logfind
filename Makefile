CC=gcc
CFLAGS=-Wall -DNDEBUG

all:
	@$(CC) $(CFLAGS) logfind.c -o logfind.o
clean:
	@rm logfind.o
