#include "helpers.h"

#define BUFF            99999

#define NUM_OF_ROWS     128
#define NUM_OF_COL      8

#define EMPTY_SEAT      '.'
#define TAKEN_SEAT      'x'

int main() {
    char seats[NUM_OF_ROWS][NUM_OF_COL];

    for (int i = 0; i < NUM_OF_ROWS; i++) {
        for (int j = 0; j < NUM_OF_COL; j++) {
            seats[i][j] = EMPTY_SEAT;
        }
    }

    FILE* f = fopen("input.txt", "r");
        if (f == NULL) {
            perror("fopen");
            return 0;   
        }
        double highest = 0, i = 0, counter = 0;
        double rowMax = NUM_OF_ROWS - 1, rowMin = 0, row = 0;
        double colMax = NUM_OF_COL - 1, colMin = 0, col = 0;
        char c;

        // Loading file into string
        while ( (c = getc(f)) != EOF ) {
            printf("%c", c);
            counter++;
            if (c == '\n'){
                if (i >= highest) {
                    highest = i;
                }
                rowMax = NUM_OF_ROWS - 1;
                rowMin = 0;
                colMax = NUM_OF_COL - 1;
                colMin = 0;
                counter = 0;
            } 
            if (c == 'F') {
                rowMax = floor((rowMax + rowMin)/2);
                if (counter == 7) row = rowMax;
            } else if (c == 'B') {
                rowMin = ceil((rowMax + rowMin)/2);
                if (counter == 7) row = rowMin;
            } else if (c == 'R') {
                colMin = ceil((colMax + colMin)/2);
                if (counter == 10) {
                    col = colMin;
                    i = row * 8 + col;
                    seats[(int)row][(int)col] = TAKEN_SEAT;
                }
            } else if (c == 'L') {
                colMax = floor((colMax + colMin)/2);
                if (counter == 10) {
                    col = colMax;
                    i = row * 8 + col;
                    seats[(int)row][(int)col] = TAKEN_SEAT;
                }
            }
        }

        for (int i = 0; i < NUM_OF_ROWS; i++) {
            for (int j = 0; j < NUM_OF_COL; j++) {
                if (seats[i][j] == '.') {
                    printf("row: %d, col: %d, id: %d\n", i, j, (i * 8 + j));
                }
                printf("%c", seats[i][j]);
            }
            printf("\n");
        }
    return 1;                                                                 
}
