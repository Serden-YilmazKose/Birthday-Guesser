#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

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
// Ask and get user's name
void getName(char *getname);
// Get gematrial value of given name
int getGematria(const char *gemName);
// Get zodiac sign, by ChatGPT
const char* getZodiacSign(int *d, int *m);
// Find how long it has been since the birthday
int howLong(int *d, int *m, int *y, bool *isLeap);

int main() {
    // create necessary integers
    int day, month, year, gematria;
    bool isLeap;
    char name[256];

    // time for the input
    getBirthday(&day, &month, &year, &isLeap);
    printf("Your birthday is %d.%d.%d!", day, month, year);

    // Day of week
    const char* dayOfWeek = weekday(day, month, year, isLeap);
    const char* dayOfWeekCentury = weekday(day, month, year + 100, isLeap);
    printf("\nYou were born on a %s!", dayOfWeek);

    // Get the user's name
    getName(name);
    printf("Your name is: %s", name);

    // Now find the gematria value of the name
    gematria = getGematria(name);
    printf("\nThe gematria value of your name is: %d", gematria);

    // Get Zodiac sign using our function
    const char* zodiac = getZodiacSign(&day, &month);
    printf("\nYour Zodiac sign is: %s", zodiac);

    printf("\n\nYour birthday is %d.%d.%d, you were born on a %s, you turn 100 on a %s.", day, month, year, dayOfWeek, dayOfWeekCentury);
    printf("\nYour name is %s, and the gematria value of your name is %d. Also, you are a %s.\n", name, gematria, zodiac);
    
    // What more could I add?
    // Find how long it has been since the user's birthday
    int today, tomonth, toyear;
    bool isToLeap;
    int length = howLong(&today, &tomonth, &toyear, &isToLeap);
    return 0;
}

int howLong(int *d, int *m, int *y, bool *isLeap) {
    // Ask for the current date
    printf("Input current year: ");
    while (1) {
        if (scanf("%d", y) != 1) {
            printf("\nInvalid input, try again: ");
            while(getchar() != '\n');
            continue;
        }
        break;
    }
    *isLeap = isLeapYear(*y);

    printf("\nInput the current month(1-12): ");
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

    int monthLen = monthLength(*m, isLeap);
    printf("\nInput current day(1-%d): ", monthLen);
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
            printf("\nThe current month  does not have that many days, try again: ");
            continue;
        }
    }
    getchar(); 
    printf("Your birthday is %d.%d.%d!\n", *d, *m, *y);
    printf("We shall now see how old you are!\n"); 
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

int getGematria(const char *gemName){
    // Were going to need a dictionary of each letter in the English alphabet

    // Run while loop for each character of the name, and add the value to the gematria integer (but exclude non letters)
    int gematria = 0;
    while (*gemName){
        // Get character at the specific pointer and make it uppercase
        char letter = toupper(*gemName);
        // If it is a letter, add the value of the letter to gematria
        if (letter >= 'A' && letter <= 'Z'){
            gematria += letter - 'A' + 1;
        }
        *gemName++;
    }
    return gematria;
}

void getName(char *getname){
    // Ask for user's name
    printf("\nEnter your name: ");
    fgets(getname, 256, stdin);
    size_t nameLen = strlen(getname);
    // Remove newline
    if (nameLen > 0 && getname[nameLen - 1] =='\n') {
        getname[nameLen - 1] = '\0';
    }
}

const char* weekday(int d, int m, int y, bool isLeap) {
    // Find the day of week you were born on, using the following algorithm
    // https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week
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
