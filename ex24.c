#include <stdio.h>
#include "dbg.h"
#include <string.h>
#include <stdlib.h>

#define MAX_DATA 100

typedef enum EyeColor {
    BLUE_EYES, GREEN_EYES, BROWN_EYES,
    BLACK_EYES, OTHER_EYES
} EyeColor;

const char *EYE_COLOR_NAMES[] = {
    "Blue", "Green", "Brown", "Black", "Other"
};

typedef struct Person {
    int age;
    char first_name[MAX_DATA];
    char last_name[MAX_DATA];
    EyeColor eyes;
    float income;
} Person;

int main(int argc, char *argv[])
{
    Person you = { .age = 0 };
    int i = 0;
    char *in = NULL;

    printf("What's your First Name? ");

    in = fgets(you.first_name, MAX_DATA - 1, stdin);

    check(in != NULL, "Failed to read first name");

    printf("What's your Last Name? ");

    in = fgets(you.last_name, MAX_DATA - 1, stdin);

    check(in != NULL, "Failed to read last name");

    printf("How old are you? ");

    char age[MAX_DATA];
    fgets(age, MAX_DATA - 1, stdin);

    int rc = atoi(age);

    you.age = rc;

    check(rc > 0, "You have to enter a number.");

    printf("What color are your eyes:\n");

    for(i = 0; i <= OTHER_EYES; i++) {
        printf("%d) %s\n", i + 1, EYE_COLOR_NAMES[i]);
    }

    printf("> ");

//    int eyes = -1;
//    rc = fscanf(stdin, "%d", &eyes);

    char eyes[MAX_DATA];
    fgets(eyes, MAX_DATA - 1, stdin);

    int eye_code = atoi(eyes);

    rc = eye_code;

    check(rc > 0, "You have to enter a number.");

    you.eyes = eye_code - 1;

    check(you.eyes <= OTHER_EYES && you.eyes >= 0, "Do it right, that's not an option");

    printf("How much do you make an hour? ");

    char income_input[MAX_DATA];
    fgets(income_input, MAX_DATA - 1, stdin);

    int income = atof(income_input);

    you.income = income;

    check(rc > 0, "Enter a floating point number");

    printf("------ Result ------ \n");

    printf("First Name: %s", you.first_name);
    printf("Last Name: %s", you.last_name);
    printf("age: %d\n", you.age);
    printf("eye color: %s\n", EYE_COLOR_NAMES[you.eyes]);
    printf("income: %f", you.income);
    return 0;
    error:
      return -1;
}