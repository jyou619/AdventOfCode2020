#include "helpers.h"
#define BUFF 50

void init_2d_arr(void** p, int len) {
    p = (void**) malloc(sizeof(void*));
    for (int i = 0; i < len; i++) {
        p[i] = (void*) malloc(BUFF);
    }
}

void free_2d_arr(void** p, int len) {
    for (int i = 0; i < len; i++) {
        free(p[i]);
    }
    free(p);
}

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
 * Does realloc for 2d arrays. Takes in pointer p, original length, and new length to be
 * realloc.
 */
// void** my_2d_realloc(void** p, size_t ogLength, size_t newLength) {
//     if (newLength == 0) {
//         free_2d_arr(p, ogLength);
//         return NULL;
//     } else if (!p) {
//         return (void**) init_2d_arr(newLength/sizeof(p));
//     } else if (ogLength > newLength) {
//         return p;
//     } else {
//         void** newP = init_2d_arr(newLength/(sizeof(p)));
//         if (newP) {
//             memcpy(newP, p, ogLength);
//             free_2d_arr(p, ogLength/(sizeof(p)));
//         }
//         return newP;
//     }
// }