#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Prototype of birthday input function
void getBirthday(int *d, int *m, int *y);
// Check if the year is a leap year
bool isLeapYear(int *y);
// Check how many days are in the given month
int monthLength(int *m, bool *isLeap);
// Prototype for find birth weekday function
int weekday();


int main()
{
    // Ask user for birth day, month and year
    // https://www.w3schools.com/c/c_user_input.php

    // create necessary integers
    int day;
    int month = -1;
    int year = -1;

    // time for the input
    getBirthday(&day, &month, &year);

    return 0;
}


// Find the day of week you were born on, using the following algorithm
// https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week
int weekday() {
    return 0;
    }

bool isLeapYear(int *y) {
    if (*y % 4 != 0) {
    return false;
    }
    return true;
}

void getBirthday(int *d, int *m, int *y)  {
    // Get birth year first, since a leap year will change the possible birth dates in February
    printf("Input your birth year: ");
    while (1) {
        if (scanf("%d", y) != 1) {
            printf("\nInvalid input, try again: ");
            while(getchar() != '\n');
            continue;
        }
        break;
    }
    // Check if the birth year is a leap year
    bool leap = isLeapYear(y);

    // Get user's birth MONTH
    printf("\nInput your birth month (0-31): ");
    while (1) {
        if (scanf("%d", m) != 1) {
            printf("\nInvalid input, try again: ");
            while(getchar() != '\n');
            continue;
        }
        if (*m >= 1 && *m <= 12) {
            break;
        }
    }

    // Get user's birth DAY, but take into account the different number of days in different months!
    // Verify how many days are in the given month
    int monthLen = monthLength(m, &leap);
    printf("\nInput your birth day (0-31): ");
    while (1) {
        if (scanf("%d", m) != 1) {
            printf("\nInvalid input, try again: ");
            while(getchar() != '\n');
            continue;
        }
        if (*m >= 1 && *m <= monthLen) {
            break;
        }
        else if (*m > monthLen) {
            printf("\nYour birth month does not have that many days, try again:");
            continue;
        }
    }
}

int monthLength(int *m, bool *isLeap) {
    int longer[7] = {1, 3, 5, 7, 8, 10, 12};
    int shorter[4] = {4, 6, 9, 11};

    for(int i = 0; i < 7 / sizeof(longer); i++) {
        if (*m == i) {
        return 31;
        }
    }

    for(int i = 0; i < 4 / sizeof(longer); i++) {
        if (*m == i) {
        return 30;
        }
    }

    if (*m == 2) {
        if (*isLeap) {
            return 29;
        }
        else {
            return 28;
        }
    }
}
