#define _GNU_SOURCE
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX             99999
#define PREAMBLE_SIZE   25

bool pairFinder(int sum, int* a, int size, int pos) {

    for (int i = pos; i < size + pos; i++) {
        for (int j = pos + 1; j < size + pos + 1; j++) {
            if ((a[i] + a [j]) == sum) {
                return true;
            }
        }
    }
    return false;
}

void contiguousFinder(int n, int* a, int len) {
    for (int i = 0; i < len; i++) {
        int min = a[i], max = a[i], sum = a[i];

        for (int j = i + 1; j < len; j++) {
            sum += a[j];
            if (min > a[j]) min = a[j];
            if (max < a[j]) max = a[j];
            if (sum == n) {
                printf("Answer: %d\n", min + max);
                return;
            } else if (sum > n) {
                break;
            } 
        }
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

    int counter = PREAMBLE_SIZE;

    while (pairFinder(a[counter], a, PREAMBLE_SIZE, counter - PREAMBLE_SIZE)) {
        counter++;
    }

    int part1 = a[counter];
    printf("%d\n", i);
    
    contiguousFinder(part1, a, i);

}