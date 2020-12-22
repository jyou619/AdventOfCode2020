CC = gcc
CFLAGS = -g -Wall -pedantic -std=c99

include $(HOME)/code/AdventOfCode2020/helpers/filelist.mk

day2: day2.c
	$(CC) $(CFLAGS) $(LIBSRCS) day2.c -o day2

clean:
	rm -f *.o day2