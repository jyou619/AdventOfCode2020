#include <stdio.h>
#include <string.h>

#define BUFF 9999

int main() {
    FILE* f = fopen("input.txt", "r");
    if (f == NULL) {
        perror("fopen");
        return 0;
    }

    return 1;                                                                 
}