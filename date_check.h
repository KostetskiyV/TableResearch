#ifndef DATE_CHECK_H__
#define DATE_CHECK_H__

#include <stdbool.h>

#define JANUARY_DAYS 31
#define FEBRUARY_DAYS 28
#define FEBRUARY_DAYS_LEAP 29
#define MARCH_DAYS 31
#define APRIL_DAYS 30
#define MAY_DAYS 31
#define JUNE_DAYS 30
#define JULY_DAYS 31
#define AUGUST_DAYS 31
#define SEPTEMBER_DAYS 30
#define OCTOBER_DAYS 31
#define NOVEMBER_DAYS 30
#define DECEMBER_DAYS 31

bool date_check(char *date);
void date2int(char *date, int *day, int *month, int *year);
bool is_leap(int year);
bool check_day(int day, int month, int year);

#endif