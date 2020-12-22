#include "helpers.h"
#define BUFF            1
#define MINMAX          0
#define GETCHAR         1
#define PASSWORD        2

bool check_password(char* password, int min, int max, char key) {
    int counter = 0;
    for (int i = 0; i < strlen(password); i++) {
        if (password[i] == key) {
            counter++;
        }
    }
    if (counter > max || counter < min) {
        return false;
    } else {
        return true;
    }
}


bool is_valid_password(char* line) {
    int min, max, i = 0;
    char c;
    char *token;

    token = strtok(line, " ");

    while (token != NULL) {
        switch (i) {
            case MINMAX: {
                char *t;
                int j = 0;
                while( (t = strsep(&token, "-")) != NULL ) {
                    if (j == 0) {
                        min = atoi(t);
                    } else if (j == 1) {
                        max = atoi(t);
                        break;
                    }
                    j++;
                }
                break;
            } case GETCHAR:
                c = token[0];
                break;
            case PASSWORD:
                return check_password(token, min, max, c);

        }
        token = strtok(NULL, " ");
        i++;
    }
    return false;
}

bool check_password_part2(char* password, int pos1, int pos2, char key) {
    if ( ((password[pos1 - 1] == key) && (password[pos2 - 1] != key)) 
            || ((password[pos1 - 1] != key) && (password[pos2 - 1] == key)) ) {
        printf("%d-%d %c: %s",pos1, pos2, key, password);
        return true;
    }
    return false;
}


bool is_valid_password_part2(char* line) {
    int pos1, pos2, i = 0;
    char c;
    char *token;

    token = strtok(line, " ");

    while (token != NULL) {
        switch (i) {
            case MINMAX: {
                char *t;
                int j = 0;
                while( (t = strsep(&token, "-")) != NULL ) {
                    if (j == 0) {
                        pos1 = atoi(t);
                    } else if (j == 1) {
                        pos2 = atoi(t);
                        break;
                    }
                    j++;
                }
                break;
            } case GETCHAR:
                c = token[0];
                break;
            case PASSWORD:
                return check_password_part2(token, pos1, pos2, c);

        }
        token = strtok(NULL, " ");
        i++;
    }
    return false;
}


int main() {
    FILE* f = fopen("input.txt", "r");
        if (f == NULL) {
            perror("fopen");
            return 0;
        }

        char* line = NULL;
        size_t len = 0;
        ssize_t n;
        int i = 0;

        while ((n = getline(&line, &len, f)) != -1) {
            if (is_valid_password_part2(line)) {
                i++;
            }
        }
        printf("i:%d\n", i);
    return 1;
}
