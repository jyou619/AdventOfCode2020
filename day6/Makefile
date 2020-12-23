CC = gcc
CFLAGS = -g -Wall -pedantic -std=c99

include $(HOME)/code/AdventOfCode2020/helpers/filelist.mk

day6: day6.c
	$(CC) $(CFLAGS) $(LIBSRCS) day6.c -lm -o day6

clean:
	rm -f *.o day6