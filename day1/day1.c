#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 99999

void pairFinder(int sum, int* a, int size) {
    int x;

    bool s[MAX] = { 0 };

    for (int i = 0; i < size; i++) {
        x = sum - a[i];
        if (s[x] == 1) {
            printf("Pair for %d found: %d, %d.\nMultiplication is %d\n\r", sum, a[i], x, (a[i] * x));
        }
        s[a[i]] = 1;
    }
}

int main() {
    FILE* f = fopen("input.txt", "r");
    if (f == NULL) {
        perror("fopen");
        exit(1);
    }

    char* line;
    int* a;
    size_t len = 0;
    ssize_t n;
    int i = 0;

    a = (int*) malloc(sizeof(int));

    while ((n = getline(&line, &len, f)) != -1) {
        a[i] = atoi(line);
        i++;
        a = (int*) realloc(a, sizeof(int) * i + 1);
    }

    pairFinder(2020, a, i);

    fclose(f);
    free(a);
    return 1;
}
