#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Prototype of birthday input function
void getBirthday(int *d, int *m, int *y);
// Check if the year is a leap year
bool isLeapYear(int *y);
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
    if (!isLeapYear(&year)) {
        printf("Not Leap Year");
        }
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
    printf("Input your birth day (0-31): ");
    while (1) {
        if (scanf("%d", d) != 1) {
        printf("Invalid input, try again: ");
        while(getchar() != '\n');
        continue;
            }
        // check if input is an integer and if the input is in the appropriate range
        // https://islandclass.org/2020/05/14/checking-for-integers-c-code/
        if (*d >= 1 && *d <= 31) {
            break;
            }
    }

    printf("\nInput your birth month (1-12): ");
    while (*m < 0 || *m > 12) {
        scanf("%d", m);
        }
    printf("\nInput your birth year: ");
    scanf("%d", y);
}
