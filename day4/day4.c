#include "helpers.h"

#define BUFF            99999
#define BIRTH_YEAR      "byr"
#define ISSUE_YEAR      "iyr"
#define EXPIR_YEAR      "eyr"
#define HEIGHT          "hgt"
#define HAIR_COLOR      "hcl"
#define EYE_COLOR       "ecl"
#define PASSPORT_ID     "pid"
#define COUNTRY_ID      "cid"

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

    printf("batch[i]: %s\n", batch);

    for (int i = 0; i < strlen(batch); i++) {
        // printf("batch[i]: %c\n", batch[i]);
        // End of field, start new token
        if (batch[i] == '\n' || batch[i] == ' ') {
            memset(token, 0, strlen(token));
            j = 0;
        } else if (batch[i] == ':') { // If end of field ID, validify field
            if (!check_field(&passport, token)) {
                return false;
            }
        } else {
            token[j] = batch[i];
            j++;
            // printf("token: %s, batch[i]: %c\n", token, batch[i]);
        }
    }
    printf("Answer: %d\n", (passport.birth_year && passport.issue_year && passport.expir_year && 
            passport.height && passport.hair_color && passport.eye_color && passport.passport_id));
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
                if (valid_passport(batch)) valid++;
                memset(batch, 0, strlen(batch));
            } else {
                i++;
            }
        }
        
    printf("Number of valid passports: %d\n", valid + valid_passport(batch)); // Kinda shitty way but
    return 1;                                                                 // needed to check last
}
