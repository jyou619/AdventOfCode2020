#include "my_string.h"

/**
 * Removes n number of chars from s
 */
void chopper(char *s, int n) {
    assert(n != 0 && s != 0);
    int len = strlen(s);
    if (n > len) {
        n = len;
    }
    memmove(s, s + n, len - n + 1);
}