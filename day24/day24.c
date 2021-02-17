#define _GNU_SOURCE
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define BUFF                9999
#define HASH                37
#define NUM_OF_DIRECTIONS   6
#define WHITE               0
#define BLACK               1
#define GRIDSIZE            305
#define DAYS                100

typedef enum {
    E,
    SE,
    SW,
    W,
    NW,
    NE
} Direction;

typedef struct {
    int x;
    int y;
    int z;
} Coordinate;

void travel(Direction d, Coordinate* c) {
    switch (d) {
        case E:
            c->x++;
            c->y--;
            break;
        case SE:
            c->z++;
            c->y--; 
            break;
        case SW:
            c->x--;
            c->z++;
            break;
        case W: 
            c->x--;
            c->y++;
            break;
        case NW:
            c->z--;
            c->y++;
            break;
        case NE: 
            c->x++;
            c->z--;
            break;
        default:
            return;
    }
}

Direction get_move(char* s) {
    if (s[0] == 'e') {
        return E;
    } else if (s[0] == 's' && s[1] == 'e') {
        return SE;
    } else if (s[0] == 's' && s[1] == 'w') {
        return SW;
    } else if (s[0] == 'w') {
        return W;
    } else if (s[0] == 'n' && s[1] == 'w') {
        return NW;
    } else if (s[0] == 'n' && s[1] == 'e') {
        return NE;
    } else {
        return HASH;
    }
}

void reset_position(Coordinate* v) {
    v->x = 0;
    v->y = 0;
    v->z = 0;
}

int hasher(Coordinate* vector) {
    return (vector->x + (HASH * vector->y) + (HASH * HASH * vector->z));
}

void flipper(bool tiles[BUFF], Coordinate* vector, int* blacks) {
    if (tiles[hasher(vector)] == WHITE) {
        tiles[hasher(vector)] = BLACK;
        *blacks += 1;
    } else {
        tiles[hasher(vector)] = WHITE;
        *blacks -= 1;
    }
}

bool follows_rule(bool tiles[BUFF], Coordinate* vector) {
    int ruleTiles = 0;
    Coordinate cursor = *vector;
    if (tiles[hasher(&cursor)] == WHITE) {
        for (int i = E; i < NUM_OF_DIRECTIONS; i++) {
            travel(i, &cursor);
            if (tiles[hasher(&cursor)] == BLACK) {
                ruleTiles++;
            }
            cursor = *vector;
        }
        if (ruleTiles == 2) {
            return true;
        }
    } else {
        for (int i = E; i < NUM_OF_DIRECTIONS; i++) {
            travel(i, &cursor);
            if (tiles[hasher(&cursor)] == WHITE) {
                ruleTiles++;
            }
            cursor = *vector;
        }
        if (ruleTiles == 0 || ruleTiles > 2) {
            return true;
        }
    }
    return false;
}

int main() {
    FILE* f = fopen("input.txt", "r");
    if (f == NULL) {
        perror("fopen");
        exit(1);
    }

    char l[BUFF], *s;
    bool tiles[BUFF] = { 0 };
    Coordinate empty[BUFF] = { 0 };
    Coordinate toFlip[BUFF] = { 0 };
    int blacks = 0;

    Coordinate* vector = malloc(sizeof(Coordinate));
    reset_position(vector);

    for (int i = 0; fgets(l, BUFF, f); i++) {
        s = l;
        while (strcmp(s, "\n")) {
            Direction d = get_move(s);
            travel(d, vector);
            if (d == E || d == W) {
                s++;
            } else {
                s += 2;
            }
        }
        flipper(tiles, vector, &blacks);
        reset_position(vector);        
    }
    // blacks = 0;
    // for (int c = 0; c < DAYS; c++) {
    //     for (int i = -GRIDSIZE; i < GRIDSIZE; i++) {
    //         for (int j = -GRIDSIZE; j < GRIDSIZE; j++) {
    //             for (int k = -GRIDSIZE; k < GRIDSIZE; k++) {
    //                 vector->x = i;
    //                 vector->y = j;
    //                 vector->z = k;
    //                 if (follows_rule(tiles, vector)) {
    //                     toFlip[hasher(vector)] = *vector;
    //                 }
    //             }
    //         }
    //     }
    //     for (int x = 0; x < BUFF; x++) {
    //         flipper(tiles, &toFlip[x], &blacks);
    //     }
    //     memcpy(toFlip, empty, BUFF);
    // }
    printf("black tiles: %d\n", blacks);
}