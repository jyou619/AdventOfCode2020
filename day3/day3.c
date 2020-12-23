#include <stdio.h>
#include <string.h>

#define WIDTH           999
#define HEIGHT          999
typedef struct Coordinate {
    int x;
    int y;
} coordinate;

unsigned long traversed(int right, int down, char map[HEIGHT][WIDTH], int height) {
    // Setting row length and column lengths
    int wSize = strlen(map[0]);
    int hSize = height;
    
    // Coordinates for toboggan
    struct Coordinate toboggan;
    toboggan.x = 0;
    toboggan.y = 0; 
    
    unsigned long treeCount = 0;
    // While we haven't hit bottom
    while (toboggan.y < hSize) {
        toboggan.x += right;
        toboggan.y += down;
        if ( toboggan.x >= wSize ) {
            toboggan.x %= wSize;
        }
        if (map[toboggan.y][toboggan.x] == '#') {
            treeCount++;
        }
    }
    printf("%ld\n", treeCount);
    return treeCount;
}

int main() {
    char map[HEIGHT][WIDTH];
    FILE* f = fopen("input.txt", "r");
        if (f == NULL) {
            perror("fopen");
            return 0;
        }
        int width = 0, height = 0;
        char c;

        // Loading map into structure
        while ( (c = getc(f)) != EOF ) {
            if (c == '\n') {
                height++;
                width = 0;
            } else {
                map[height][width] = c;
                width++;
            }
        }
        printf("Part one: %ld\n", traversed(3, 1, map, height));
        printf("Part two: %ld\n", traversed(3, 1, map, height) * traversed(1, 1, map, height) * traversed(5, 1, map, height) * traversed(7, 1, map, height) * traversed(1, 2, map, height));
    return 1;
}
