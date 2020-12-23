#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>

void *my_realloc(void* p, size_t ogLength, size_t newLength);
char *strremove(char *str, const char *sub);
