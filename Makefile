CC=gcc
CFLAGS=-Wall -DNDEBUG -g

all:
	@$(CC) $(CFLAGS) logfind.c -o logfind.o
clean:
	@rm logfind.o
