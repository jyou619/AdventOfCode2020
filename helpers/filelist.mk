HELPER_LIBPATH=$(HOME)/code/AdventOfCode2020/helpers

CFLAGS += -I$(HELPER_LIBPATH) 

LIBSRCS += $(HELPER_LIBPATH)/memory.c $(HELPER_LIBPATH)/linked_list.c