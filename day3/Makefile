CC = gcc
CFLAGS = -g -Wall -pedantic -std=c99

include $(HOME)/code/AdventOfCode2020/helpers/filelist.mk

day3: day3.c
	$(CC) $(CFLAGS) $(LIBSRCS) day3.c -o day3

clean:
	rm -f *.o day3