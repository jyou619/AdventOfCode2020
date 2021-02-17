CC = gcc
CFLAGS = -g -Wall -pedantic -std=c99

include $(HOME)/code/AdventOfCode2020/helpers/filelist.mk

day24: day24.c
	$(CC) $(CFLAGS) $(LIBSRCS) day24.c -lm -o day24

clean:
	rm -f *.o day24