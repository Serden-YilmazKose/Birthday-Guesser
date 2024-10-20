#include <stdio.h>
#include <stdbool.h>

const char* weekday(int d, int m, int y, bool isLeap);
// Find the yearly doomsday based on month
void getDoomsDay(int m, bool isLeap, int *doom);
// Find the doomsday based on the year
int getAnchorDay(int y);
// Ask and get user's name

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
