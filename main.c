#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#include "getUserBirthday.h"
#include "doomsday.h"
#include "userName.h"
#include "getUserAge.h"

struct Date{
    int day;
    int month;
    int year;
};

struct Person{
    struct Date birthday;
    char name[256];
    int ageYear;
    int ageMonth;
    int ageDay;
};

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
    //int today, tomonth, toyear;
    struct Date todayDate = {0, 0, 0};
    struct Date userBirthday = {day, month, year};
    struct Person userPerson = {userBirthday, "", 0, 0, 0};
    strcpy(userPerson.name, name);

    // getToday(&todayDate);
    printf("We shall now see how old you are!\n");
    getAge(&todayDate, &userPerson);

    return 0;
}
