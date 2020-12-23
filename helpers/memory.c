#include "helpers.h"
#define BUFF 50

/**
 * Reallocates memory to pointer p by comparing ogLength to newLength to see if necessary.
 * Requires a concrete length that the memory will be reallocated by.
 */
void* my_realloc(void* p, size_t ogLength, size_t newLength) {
    
    if (newLength == 0) {
        free(p);
        return NULL;
    } else if (!p) {
        return malloc(newLength);
    } else if (ogLength > newLength) {
        return p;
    } else {
        void* newP = malloc(newLength);
        newP = NULL;
        if (newP) { 
            memcpy(newP, p, ogLength);
            free(p);
        }
        return newP;
    }
}


/**
 * Removes substring sub from string str.
 */
char *strremove(char *str, const char *sub) {
    size_t len = strlen(sub);
    if (len > 0) {
        char *p = str;
        while ((p = strstr(p, sub)) != NULL) {
            memmove(p, p + len, strlen(p + len) + 1);
        }
    }
    return str;
}
