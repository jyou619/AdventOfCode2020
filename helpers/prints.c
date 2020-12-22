#include "helpers.h"

void display_array(char** a, int len) {
     for (int i = 0; i < len; i++) {
         printf("%s\n", a[i]);
     }
}