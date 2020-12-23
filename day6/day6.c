#include <stdio.h>
#include <string.h>

#define BUFF        9999
#define NUM_OF_QS   26

int group_answer_count(char* group) {
    printf("group:\n%s\n", group);
    int questions[NUM_OF_QS] = { 0 };
    int count = 0, x = 0;
    for (int i = 0; i < strlen(group); i++) {
        if (group[i] != '\n') {
            x = group[i] - 'a';
            if (!questions[x]) {
                count++;
                questions[x] = 1;
            } 
        }
    }
    return count;
}

int group_answer_count_part2(char* group) {
    printf("group:\n%s\n", group);
    int questions[NUM_OF_QS] = { 0 };
    int count = 0, x = 0, nPeople = 0;
    for (int i = 0; i < strlen(group); i++) {
        if (group[i] != '\n') {
            x = group[i] - 'a';
            questions[x]++;
        } else {
            nPeople++;
        }
    }
    nPeople -= 1;
    for (int j = 0; j < NUM_OF_QS; j++) {
        if (questions[j] == nPeople) count++;
    }
    return count;
}

int main() {
    FILE* f = fopen("input.txt", "r");
    if (f == NULL) {
        perror("fopen");
        return 0;
    }

    char group[BUFF], c;
    int i = 0, count = 0;

    while ( (c = getc(f)) != EOF ) {
        group[i] = c;
        if ((c == '\n' && group[i - 1] == '\n')) {
            count += group_answer_count_part2(group);
            memset(group, 0, strlen(group));
            i = 0;
        } else {
            i++;
        }
    }
    printf("Total yes count: %d\n", count + group_answer_count(group));
    return 1;                                                                 
}