#ifndef GETUSERAGE_INCLUDED
#define GETUSERAGE_INCLUDED

struct Date;
struct Person;

// Get today's date
void getToday(struct Date *date);
// Find the distance between given date and birthday
void getAge(const struct Date *date, struct Person *person);
// Check if input date is valid, AFTER the birthday
void isValidDate(const struct Date *date, struct Person *person, bool *validDate);

#endif // GETUSERAGE_INCLUDED
