#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <my_string.h>

#define MAX                888
#define BUFF               20
#define ACC                "acc"
#define JMP                "jmp"
#define NOP                "nop"

typedef struct GameState{
    int acc;
    int opNum;
} GameState;

bool has_seen(int op, bool seen[MAX]) {
    if (seen[op]) {
        return true;
    } else {
        return false;
    }
}

void run(GameState *game, char* ops[MAX]) {
    char s[3];
    s[0] = ops[game->opNum][0];
    s[1] = ops[game->opNum][1];
    s[2] = ops[game->opNum][2];

    chopper(ops[game->opNum], strlen(s));
    if (strcmp(s, ACC) == 0) {
        int val = atoi(ops[game->opNum]);
        game->acc += val;
        game->opNum++;
    } else if (strcmp(s, JMP) == 0) {
        int val = atoi(ops[game->opNum]);
        game->opNum += val;
    } else if (strcmp(s, NOP) == 0) {
        game->opNum++;
    }
}

int main() {
    FILE* f = fopen("input.txt", "r");
    if (f == NULL) {
        perror("fopen");
        return 0;
    }

    bool seen[MAX] = { 0 };
    char *ops[MAX], l[BUFF];
    GameState game;
    game.acc = 0;
    game.opNum = 0;

    for (int i = 0; fgets(l, BUFF, f); i++) {
        ops[i] = malloc(sizeof(char) * strlen(l));
        strcpy(ops[i], l);
    }

    while(1) {
        if (has_seen(game.opNum, seen)) {
            printf("Loop detected: acc=%d\n", game.acc);
            break;
        }
        seen[game.opNum] = 1;
        run(&game, ops);
    }
}