CC = gcc
CFLAGS = -g -Wall -pedantic -std=c99

include $(HOME)/code/AdventOfCode2020/helpers/filelist.mk

day7: day7.c
	$(CC) $(CFLAGS) $(LIBSRCS) day7.c -lm -o day7

clean:
	rm -f *.o day7