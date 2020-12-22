#include "helpers.h"

/**
 * Converts filename FILE f into an array separated by newlines.
 * Populates fi
 */
int file_to_array(FILE* f, char* filename, char** a) {
    f = fopen(filename, "r");
        if (f == NULL) {
            perror("fopen");
            return 0;
        }

        char* line = NULL;
        size_t len = 0;
        ssize_t n;
        int i = 0;

        while ((n = getline(&line, &len, f)) != -1) {
            a = (char**) my_realloc((void**) a, sizeof(a), (sizeof(char*) * (i + 1)) + n);
            a[i++] = strdup(line);
        }
        return i;
}


