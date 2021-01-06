CC = gcc
CFLAGS = -g -Wall -pedantic -std=c99

include $(HOME)/code/AdventOfCode2020/helpers/filelist.mk

day8: day8.c
	$(CC) $(CFLAGS) $(LIBSRCS) day8.c -lm -o day8

clean:
	rm -f *.o day8