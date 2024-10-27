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
    int ageYear;
    int ageMonth;
    int ageDay;
};

// Get today's date
void getToday(struct Date *date);
// Find the distance between given date and birthday
void getAge(const struct Date *date, struct Person *person);
// If the user so chooses, print the exact age of the user
void getExactAge (const struct Date *date, struct Person *person);
// Check if input date is valid, AFTER the birthday
void isValidDate(const struct Date *date, struct Person *person, bool *validDate);

void getExactAge (const struct Date *date, struct Person *person) {
    printf("Finding exact age...\n");
    // Make variable to check if user has had his/her birthday this year
    bool birthdayPassed = false;
    // check if birhtday has passed
    if (date->month < person->birthday.month || (date->month == person->birthday.month && date->day >= person->birthday.day)) {
        birthdayPassed = false;
    }
    else {
        birthdayPassed = true;
    }
    // If the birthday has passed, add the amount of months in between the dates, months too
    if (birthdayPassed) {
        person->ageMonth = date->month - person->birthday.month;
        if (date->month >= person->birthday.month) {
            if (date->day >= person->birthday.day) {
                person->ageDay = date->day - person->birthday.day;
            }
            else {
                person->ageDay = (30 + date->day) - person->birthday.day;
                person->ageMonth--;
            }
        }
    }
    else {
        person->ageMonth = 12 + (date->month - person->birthday.month);
        if (date->day < person->birthday.day) {
            person->ageDay = (30 + date->day) - person->birthday.day;
            person->ageMonth--;
        }
        else {
            person->ageDay = date->day - person->birthday.day;
        }
    }

    // Finally, print the user's age
    printf("You are %d years, %d months, and %d days old!\n", person->ageYear, person->ageMonth, person->ageDay);
}

void isValidDate(const struct Date *date, struct Person *person, bool *validDate) {
    // Find distance between given date and birth date
    // If the current mo nth is greater than the birth month, we can subtract current year for birth year
    // to get the age in years (ignoring months and days). This is the easiest route
    bool isYear = false;
    if (date->year == person->birthday.year) {
        isYear = true;
    }
    if (isYear) {
        if (date->month == person->birthday.month) {
            if (date->day >= person->birthday.day) {
                *validDate = true;
            }
            else {
                *validDate = false;
            }
        }
        else if (date->month > person->birthday.month) {
            *validDate = false;
        }
        else {
            *validDate = true;
        }
    }
    if (date->year < person->birthday.year) {
        *validDate = false;
    }
    else {
        *validDate = true;
    }
}

void getAge(const struct Date *date, struct Person *person) {
    // Find distance between given date and birth date
    // If the current mo nth is greater than the birth month, we can subtract current year for birth year
    // to get the age in years (ignoring months and days). This is the easiest route
    // First, get the current date
    bool isValid = false;
    while (!isValid) {
        getToday(date);
        isValidDate(date, person, &isValid);
        if (!isValid) {
            printf("Invalid date, try again.\n");
        }
    }
    if (isValid) {
        if (date->month > person->birthday.month){
            person->ageYear = date->year - person->birthday.year;
        }
        else if (date->month == person->birthday.month && date->day >= person->birthday.day){
            person->ageYear = date->year - person->birthday.year;
        }
        else if ((date->month == person->birthday.month && date->day < person->birthday.day) || (date->month < person->birthday.month)) {
            person->ageYear = date->year - person->birthday.year - 1;
        }
        printf("Your age is: %d\n", person->ageYear);

        // Ask user if s/he would like to get their age in months and days
        // https://stackoverflow.com/questions/18627163/yes-no-loop-in-c
        char answer;
        while (1)  {
            printf("Would you like to get your age in months and days, along with years? Enter Y or N: ");
            // If the answer is a valid, and is Y, then give the age in months and days
            if (scanf(" %c", &answer) == 1) {
                if (answer == 'Y') {
                    getExactAge (date, person);
                    // break the while statement
                    break;
            }
                // If user types N, then kindly comply :]
                else if (answer == 'N') {
                    printf("\nYou entered [N]. Thank you for your input.\n");
                    break;
            }
                // Otherwise, continue
                else {
                    printf("Invalid input. Enter Y or N.\n");
                }
            }
            // Clear input new line
            //while(getchar() != "\n");
        }
    }

    else {
        printf("Invalid date\n");
    }

    // Check if the user's birthday is, today!
    if (date->month == person->birthday.month && date->day == person->birthday.day) {
        printf("Happy birthday %s, you are %d years old!\n", person->name, person->ageYear);
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
