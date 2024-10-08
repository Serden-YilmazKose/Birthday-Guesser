#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Prototype of birthday input function
void getBirthday(int *d, int *m, int *y);
// Check if the year is a leap year
bool isLeapYear(int y);
// Check how many days are in the given month
int monthLength(int m, bool isLeap);
// Prototype for find birth weekday function
int weekday();


int main()
{
    // Ask user for birth day, month and year
    // https://www.w3schools.com/c/c_user_input.php

    // create necessary integers

    int day = 0;
    int month = -1;
    int year;

    // time for the input
    getBirthday(&day, &month, &year);

    return 0;
}


// Find the day of week you were born on, using the following algorithm
// https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week
int weekday() {
    return 0;
    }

bool isLeapYear(int y) {
    if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) {
    return true;
    }
    return false;
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
    bool leap = isLeapYear(*y);

    // Get user's birth MONTH
    printf("\nInput your birth month (1-12): ");
    while (1) {
        if (scanf("%d", m) != 1) {
            printf("\nInvalid input, try again: ");
            while(getchar() != '\n');
            continue;
        }
        if (*m >= 1 && *m <= 12) {
            break;
        }
        else {
            printf("\nInvalid month, there are only 12 months in the year, try again: ");
        }
    }

    // Get user's birth DAY, but take into account the different number of days in different months!
    // Verify how many days are in the given month
    int monthLen = monthLength(*m, leap);
    printf("\nInput your birth day (1-%d): ", monthLen);
    while (1) {
        if (scanf("%d", d) != 1) {
            printf("\nInvalid input, try again: ");
            while(getchar() != '\n');
            continue;
        }
        if (*d >= 1 && *d <= monthLen) {
            break;
        }
        else {
            printf("\nYour birth month does not have that many days, try again:");
            continue;
        }
    }
}

int monthLength(int m, bool isLeap) {
    const int intLong = 7;
    const int intShort = 4;
    int longer[] = {1, 3, 5, 7, 8, 10, 12};
    int shorter[] = {4, 6, 9, 11};

    for(int i = 0; i < intLong; i++) {
        if (m == longer[i]) {
        return 31;
        }
    }

    for(int i = 0; i < intShort; i++) {
        if (m == shorter[i]) {
        return 30;
        }
    }

    if (m == 2) {
        if (isLeap == true) {
            return 29;
        }
        else {
            return 28;
        }
    }
    return 0;
}
