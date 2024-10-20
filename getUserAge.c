#include <stdio.h>
#include <stdbool.h>

#include "getUserBirthday.h"
struct Date{
    int day;
    int month;
    int year;
};

struct Person{
    struct Date birthday;
    char name[256];
    int age;
};

// Get today's date
void getToday(struct Date *date);
// Find the distance between given date and birthday
void getAge(const struct Date *date, struct Person *person);

void getAge(const struct Date *date, struct Person *person) {
    // Find distance between given date and birth date
    // If the current mo nth is greater than the birth month, we can subtract current year for birth year
    // to get the age in years (ignoring months and days). This is the easiest route
    bool isValid = false;
    bool isYear = false;

    if (date->year == person->birthday.year) {
        isYear = true;
    }
    if (isYear) {
        if (date->month == person->birthday.month) {
            if (date->day >= person->birthday.day) {
                isValid = true;
            }
            else {
                isValid = false;
            }
        }
        else if (date->month > person->birthday.month) {
            isValid = false;
        }
        else {
            isValid = true;
        }
    }
    if (date->year < person->birthday.year) {
        isValid = false;
    }
    else {
        isValid = true;
    }

    if (isValid) {
        if (date->month > person->birthday.month){
            person->age = date->year - person->birthday.year;
        }
        else if (date->month == person->birthday.month && date->day >= person->birthday.day){
            person->age = date->year - person->birthday.year;
        }
        else if ((date->month == person->birthday.month && date->day < person->birthday.day) || (date->month < person->birthday.month)) {
            person->age = date->year - person->birthday.year - 1;
        }
        printf("Your age is: %d\n", person->age);
    }
    else {
        printf("Invalid date\n");
    }

    // Check if the user's birthday is, today!
    if (date->month == person->birthday.month && date->day == person->birthday.day) {
        printf("Happy birthday %s, you are %d years old!\n", person->name, person->age);
    }
}

void getToday(struct Date *date) {
    // Ask for the current date
    printf("Input current year: ");
    while (1) {
        if (scanf("%d", &date->year) != 1) {
            printf("\nInvalid input, try again: ");
            while(getchar() != '\n');
            continue;
        }
        break;
    }
    bool isLeap = isLeapYear(date->year);

    printf("\nInput the current month(1-12): ");
    while (1) {
        if (scanf("%d", &date->month) != 1) {
            printf("\nInvalid input, try again: ");
            while(getchar() != '\n');
            continue;
        }
        if (date->month >= 1 && date->month <= 12) {
            break;
        }
        else {
            printf("\nInvalid month, there are only 12 months in the year, try again: ");
        }
    }

    int monthLen = monthLength(date->month, isLeap);
    printf("\nInput current day(1-%d): ", monthLen);
    while (1) {
        if (scanf("%d", &date->day) != 1) {
            printf("\nInvalid input, try again: ");
            while(getchar() != '\n');
            continue;
        }
        if (date->day >= 1 && date->day <= monthLen) {
            break;
        }
        else {
            printf("\nThe current month  does not have that many days, try again: ");
            continue;
        }
    }
    getchar();
    printf("Today's date is %d.%d.%d!\n", date->day, date->month, date->year);
}
