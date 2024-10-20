#ifndef GETUSERAGE_INCLUDED
#define GETUSERAGE_INCLUDED

struct Date;
struct Person;

// Get today's date
void getToday(struct Date *date);
// Find the distance between given date and birthday
void howLongAgo(const struct Date *date, struct Person *person);

#endif // GETUSERAGE_INCLUDED
