CC = gcc
CFLAGS = -g -Wall -pedantic -std=c99

include $(HOME)/code/AdventOfCode2020/helpers/filelist.mk

day8: day9.c
	$(CC) $(CFLAGS) $(LIBSRCS) day9.c -lm -o day9

clean:
	rm -f *.o day9