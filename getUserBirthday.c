#include <stdio.h>
#include <stdbool.h>

// Prototype of birthday input function
void getBirthday(int *d, int *m, int *y, bool *isLeap);
// Check if the year is a leap year
bool isLeapYear(int y);
// Check how many days are in the given month
int monthLength(int m, bool isLeap);
// Prototype for find birth weekday function
const char* getZodiacSign(int *d, int *m);

void getBirthday(int *d, int *m, int *y, bool *isLeap)  {
    // Ask user for birth day, month and year
    // https://www.w3schools.com/c/c_user_input.php

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
    *isLeap = isLeapYear(*y);

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
    int monthLen = monthLength(*m, isLeap);
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
            printf("\nYour birth month does not have that many days, try again: ");
            continue;
        }
    }
    getchar();
}

bool isLeapYear(int y) {
    if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) {
    return true;
    }
    return false;
}

int monthLength(int m, bool isLeap) {
    const int intLong = 7;
    const int intShort = 4;
    const int longer[] = {1, 3, 5, 7, 8, 10, 12};
    const int shorter[] = {4, 6, 9, 11};

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

const char* getZodiacSign(int *day, int *month) {
    if ((*month == 1 && *day >= 20) || (*month == 2 && *day <= 18)) return "Aquarius";
    if ((*month == 2 && *day >= 19) || (*month == 3 && *day <= 20)) return "Pisces";
    if ((*month == 3 && *day >= 21) || (*month == 4 && *day <= 19)) return "Aries";
    if ((*month == 4 && *day >= 20) || (*month == 5 && *day <= 20)) return "Taurus";
    if ((*month == 5 && *day >= 21) || (*month == 6 && *day <= 20)) return "Gemini";
    if ((*month == 6 && *day >= 21) || (*month == 7 && *day <= 22)) return "Cancer";
    if ((*month == 7 && *day >= 23) || (*month == 8 && *day <= 22)) return "Leo";
    if ((*month == 8 && *day >= 23) || (*month == 9 && *day <= 22)) return "Virgo";
    if ((*month == 9 && *day >= 23) || (*month == 10 && *day <= 22)) return "Libra";
    if ((*month == 10 && *day >= 23) || (*month == 11 && *day <= 21)) return "Scorpio";
    if ((*month == 11 && *day >= 22) || (*month == 12 && *day <= 21)) return "Sagittarius";
    if ((*month == 12 && *day >= 22) || (*month == 1 && *day <= 19)) return "Capricorn";
    return "Unknown";
}
