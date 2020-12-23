#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "memory.h"

#define BUFF            99999

// Field values
#define BIRTH_YEAR      "byr"
#define ISSUE_YEAR      "iyr"
#define EXPIR_YEAR      "eyr"
#define HEIGHT          "hgt"
#define HAIR_COLOR      "hcl"
#define EYE_COLOR       "ecl"
#define PASSPORT_ID     "pid"
#define COUNTRY_ID      "cid"

// Eye colours
#define AMBER           "amb"
#define BLUE            "blu"
#define BROWN           "brn"
#define GREY            "gry"
#define GREEN           "grn"
#define HAZEL           "hzl"
#define OTHER           "oth"

typedef struct PP_Fields{
    bool birth_year;
    bool issue_year;
    bool expir_year;
    bool height;
    bool hair_color;
    bool eye_color;
    bool passport_id;
    bool country_id;
} pp_feilds;

bool check_field(struct PP_Fields *passport, char* field) {
    if (strcmp(field, BIRTH_YEAR) == 0) passport->birth_year = true;
    else if (strcmp(field, ISSUE_YEAR) == 0) passport->issue_year = true;
    else if (strcmp(field, EXPIR_YEAR) == 0) passport->expir_year = true;
    else if (strcmp(field, HEIGHT) == 0) passport->height = true;
    else if (strcmp(field, HAIR_COLOR) == 0) passport->hair_color = true;
    else if (strcmp(field, EYE_COLOR) == 0) passport->eye_color = true;
    else if (strcmp(field, PASSPORT_ID) == 0) passport->passport_id = true;
    else if (strcmp(field, COUNTRY_ID) == 0) passport->country_id = true;
    else return false;
    return true;
}

bool is_present(struct PP_Fields *passport, char* line) {
    char s[BUFF];
    s[0] = line[0];
    s[1] = line[1];
    s[2] = line[2];

    char* value = strremove(line, s);
    // Converts value string into int for comparing; must be within 1920, 2002 range
    if (strcmp(s, BIRTH_YEAR) == 0) {
        int n = atoi(value);
        if (n < 1920 || n > 2002) {
            return false;
        } else {
            passport->birth_year = true;
        }
    } else if (strcmp(s, ISSUE_YEAR) == 0) { // Same as above but with 2010, 2020
        int n = atoi(value);
        if (n < 2010 || n > 2020) {
            return false;
        } else {
            passport->issue_year = true;
        }
    } else if (strcmp(s, EXPIR_YEAR) == 0) { // Same as above but with 2020, 2030
        int n = atoi(value);
        if (n < 2020 || n > 2030) {
            return false;
        } else {
            passport->expir_year = true;
        }
    } else if (strcmp(s, HEIGHT) == 0) {
        // Getting unit
        char unit[2];
        unit[0] = value[strlen(value) - 2];
        unit[1] = value[strlen(value) - 1];
        unit[2] = '\0';

        // Getting measurement
        int h = atoi(strremove(value, unit));

        if (strcmp(unit, "cm") == 0 && h >= 150 && h <= 193) passport->height = true;
        else if (strcmp(unit, "in") == 0 && h >= 59 && h <= 76) passport->height = true;
        else return false;

    } else if (strcmp(s, HAIR_COLOR) == 0) {
        if (line[0] == '#' && strlen(line) == 7) {
            for (int i = 1; i < 7; i++) {
                if (!isxdigit(line[i])) {
                    return false;
                } else {
                    passport->hair_color = true;
                }
            }
        } else {
            return false;
        }
    } else if (strcmp(s, EYE_COLOR) == 0) {
        value[3] = '\0';
        if ((strcmp(value, AMBER) == 0) || (strcmp(value, BLUE) == 0) || (strcmp(value, BROWN) == 0)
         || (strcmp(value, GREY) == 0) || (strcmp(value, GREEN) == 0) || (strcmp(value, HAZEL) == 0)
         || (strcmp(value, OTHER) == 0)) {
            passport->eye_color = true;
        } else {
            return false;
        }
    } else if (strcmp(s, PASSPORT_ID) == 0) {
        if ((strlen(value) == 9) && atoi(value)) {
            passport->passport_id = true;
        } else {
            return false;
        }
    } else if (strcmp(s, COUNTRY_ID) == 0) {
        passport->country_id = true;
    }
    return true;
}

void init_passport(struct PP_Fields *passport){
    passport->birth_year = false;
    passport->country_id = false;
    passport->expir_year = false;
    passport->eye_color = false;
    passport->hair_color = false;
    passport->height = false;
    passport->issue_year = false;
    passport->passport_id = false;
}

bool valid_passport(char* batch) {
    char token[BUFF];
    int j = 0;
    struct PP_Fields passport;
    init_passport(&passport);

    for (int i = 0; i < strlen(batch); i++) {
        // End of field, start new token
        if (batch[i] == '\n' || batch[i] == ' ') {
            if (!is_present(&passport, token)) {
                memset(token, 0, BUFF);
                return false;
            }
            memset(token, 0, BUFF);
            j = 0;
        } else if (batch[i] == ':') { // If end of field ID, validify field
            if (!check_field(&passport, token)) {
                return false;
            }
        } else {
            token[j] = batch[i];
            j++;
        }
    }
    return (passport.birth_year && passport.issue_year && passport.expir_year && 
            passport.height && passport.hair_color && passport.eye_color && passport.passport_id);
}

int main() {
    char batch[BUFF];
    FILE* f = fopen("input.txt", "r");
        if (f == NULL) {
            perror("fopen");
            return 0;
        }
        int i = 0, valid = 0;
        char c;

        // Loading file into string
        while ( (c = getc(f)) != EOF ) {
            batch[i] = c;
            if ((c == '\n' && batch[i - 1] == '\n')) {
                i = 0;
                if (valid_passport(batch)){
                    valid++;
                } 
                memset(batch, 0, strlen(batch));
            } else {
                i++;
            }
        }
        
    printf("Number of valid passports: %d\n", valid + valid_passport(batch)); // Kinda shitty way but
    return 1;                                                                 // needed to check last
}
