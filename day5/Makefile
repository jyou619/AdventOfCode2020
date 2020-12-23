CC = gcc
CFLAGS = -g -Wall -pedantic -std=c99

include $(HOME)/code/AdventOfCode2020/helpers/filelist.mk

day5: day5.c
	$(CC) $(CFLAGS) $(LIBSRCS) day5.c -lm -o day5

clean:
	rm -f *.o day5