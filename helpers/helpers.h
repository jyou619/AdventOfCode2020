#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

void merge_sort(int* a, int i, int j);
void merge(int* a, int i, int m, int j);
void init_2d_arr(void** p, int len);
void free_2d_arr(void** p, int len);
void* my_realloc(void* p, size_t ogLength, size_t newLength);
void** my_2d_realloc(void** p, size_t ogLength, size_t newLength);
int file_to_array(FILE* f, char* filename, char*    * a);
void display_array(char** a, int len);
