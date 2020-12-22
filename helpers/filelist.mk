HELPER_LIBPATH=$(HOME)/code/AdventOfCode2020/helpers

CFLAGS += -I$(HELPER_LIBPATH) 

LIBSRCS += $(HELPER_LIBPATH)/process_file.c $(HELPER_LIBPATH)/prints.c $(HELPER_LIBPATH)/memory.c