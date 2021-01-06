#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <my_string.h>

#define MAX                888
#define BUFF               20
// #define ACC                "acc"
// #define JMP                "jmp"
// #define NOP                "nop"

typedef enum {
    ACC,
    JMP,
    NOP
} OP;

typedef struct Operation {
    OP op;
    int val;
} Operation;

typedef struct BootState{
    int acc;
    int opNum;
} BootState;

OP op_code(char* l) {
    char s[3]; s[0] = l[0]; s[1] = l[1]; s[2] = l[2]; s[3] = '\0';

    if (strcmp(s, "acc") == 0) {
        return ACC;
    } else if (strcmp(s, "jmp") == 0) {
        return JMP;
    } else if (strcmp(s, "nop") == 0) {
        return NOP;
    }
    return 0;
}

bool has_seen(int op, bool seen[MAX]) {
    if (seen[op]) {
        return true;
    } else {
        return false;
    }
}

void run(BootState *boot, Operation *ops) {
    switch (ops[boot->opNum].op) {
        case ACC:
            boot->acc += ops[boot->opNum].val;
            boot->opNum++;
            break;
        case JMP:
            boot->opNum += ops[boot->opNum].val;
            break;
        case NOP:
            boot->opNum++;
            break;
    }
}

bool terminates(BootState *boot, bool seen[MAX], Operation *ops, int lines) {
    while(!has_seen(boot->opNum, seen)) {
        seen[boot->opNum] = 1;
        run(boot, ops);
        if (boot->opNum == lines) {
            return true;
        }
    }
    return false;
}

int main() {
    FILE* f = fopen("input.txt", "r");
    if (f == NULL) {
        perror("fopen");
        return 0;
    }

    int lines = 0;
    bool seen[MAX] = { 0 };
    char l[BUFF];
    Operation ops[MAX];
    BootState boot;
    boot.acc = 0;
    boot.opNum = 0;

    for (int i = 0; fgets(l, BUFF, f); i++) {
        char s[BUFF]; strcpy(s, l); chopper(s, 3);

        ops[i].op = op_code(l);
        ops[i].val = atoi(s);
        lines++;
    }
    
    // for (int i = 0; i < lines; i++) {
    //     printf("op:%d, val:%d\n", ops[i].op, ops[i].val);
    // }

    // Part one
    // if (!terminates(&boot, seen, ops, lines)) {
    //     printf("Loop detected! acc=%d\n", boot.acc);
    // }

    // Part two
    for (int i = 0; i < lines; i++) {
        switch (ops[i].op) {
            case JMP:
                ops[i].op = NOP;
                if (terminates(&boot, seen, ops, lines)) {
                    printf("Termination complete: changed line %d, acc=%d\n", i, boot.acc);
                    return 1;
                }
                ops[i].op = JMP;
                break;
            case NOP:
                ops[i].op = JMP;
                if (terminates(&boot, seen, ops, lines)) {
                    printf("Termination complete: changed line %d, acc=%d\n", i, boot.acc);
                    return 1;
                }
                ops[i].op = NOP;
                break;
            default:
                continue;
        }
    }
}   