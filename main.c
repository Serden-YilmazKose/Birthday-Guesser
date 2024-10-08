#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// Prototype of birthday input function
void getBirthday(int *d, int *m, int *y, bool *isLeap);
// Check if the year is a leap year
bool isLeapYear(int y);
// Check how many days are in the given month
int monthLength(int m, bool isLeap);
// Prototype for find birth weekday function
const char* weekday(int d, int m, int y, bool isLeap);
// Find the yearly doomsday based on month
void getDoomsDay(int m, bool isLeap, int *doom);
// Find the doomsday based on the year
int getAnchorDay(int y);


int main()
{
    // Ask user for birth day, month and year
    // https://www.w3schools.com/c/c_user_input.php

    // create necessary integers

    int day, month, year;
    bool isLeap;

    // time for the input
    getBirthday(&day, &month, &year, &isLeap);
    printf("Your birthday is %d.%d.%d!", day, month, year);

    // Day of week
    const char* dayOfWeek = weekday(day, month, year, isLeap);
    printf("\nYou were born on a %s!", dayOfWeek);


    return 0;
}


// Find the day of week you were born on, using the following algorithm
// https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week
const char* weekday(int d, int m, int y, bool isLeap) {
    // Make an array of weekdays
    const char* weekdays[] = {"Sunday","Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

    // use getDoomsDay to find the doomsday based on the month
    int doomsDay;
    getDoomsDay(m, isLeap, &doomsDay);

    // use getDoomsYear to find the doomsday based on the year
    int anchorDay = getAnchorDay(y);

    // Finally, calcualte final doomsday, but making the final answer non zero
    int indexDoomsDay = (anchorDay + (d - doomsDay) + 7) %7;
    return weekdays[indexDoomsDay];
    }

bool isLeapYear(int y) {
    if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) {
    return true;
    }
    return false;
}

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
            printf("\nYour birth month does not have that many days, try again:");
            continue;
        }
    }
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

void getDoomsDay(int m, bool isLeap, int *doom) {
    // we have to find the doomsday of the given month
    // https://en.wikipedia.org/wiki/Doomsday_rule
    if (m == 4 || m == 6 || m == 8 || m == 10 || m == 12) {
        *doom = m;
    }

    else if (m == 1) {
        if (isLeap) {
        *doom = 4;
        }
        else {
        *doom = 3;
        }
    }

    else if (m == 2) {
        if (isLeap) {
        *doom = 4;
        }
        else {
        *doom = 3;
        }
    }

    else if (m == 3) {
        *doom = 0;
    }

    else if (m == 5) {
        *doom = 9;
    }

    else if (m == 7) {
        *doom = 11;
    }

    else if (m == 9) {
        *doom = 5;
    }

    else if (m == 11) {
        *doom = 7;
    }

}

int getAnchorDay(int y) {
    // Return the anchor day based on the YEAR
    // https://en.wikipedia.org/wiki/Doomsday_rule#Finding_a_year's_anchor_day

    // Make an array of doomsday based on century
    const int centuryAnchorDay[4] = {2, 0, 5, 3};
    int century, anchorDay;

    // First, we need to lower the year to the range of 0-400
    y = y % 400;

    // Now, we need to see what century it's in, first, second third, or fourth
    century = y / 100;
    anchorDay = centuryAnchorDay[century];

    // Now that we have the doomsday based on century, lower the year range to 0-100
    y = y % 100;

    // Create variables to find the anchor day
    int a = y / 12;
    int b = y % 12;
    int c = b / 4;

    anchorDay += (a + b + c);
    anchorDay = anchorDay % 7;

    return anchorDay;
}
