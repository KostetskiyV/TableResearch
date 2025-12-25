#include <string.h>
#include <ctype.h>
#include "date_check.h"

#define LEAP_YEAR_MULTIPLICITY 4
#define LEAP_YEAR_MULTIPLICITY_FALSE 100
#define LEAP_YEAR_MULTIPLICITY_TRUE 400

bool date_check(char *date)
{
    // DD-MM-YYYY
    int day, month, year;
    if (strlen(date) != 10)
        return false;

    if (!isdigit(date[0]) || !isdigit(date[1]) || date[2] != '-' || !isdigit(date[3]) || !isdigit(date[4]) ||
     date[5] != '-' || !isdigit(date[6]) || !isdigit(date[7]) || !isdigit(date[8]) || !isdigit(date[9]))
        return false;
    
    date2int(date, &day, &month, &year);

    if (month <= 0 || month > 12 || year < 1900 || year > 2025)
        return false;
    return check_day(day, month, year);
}

void date2int(char *date, int *day, int *month, int *year)
{
    *day = (int) ((date[0] - '0') * 10 + date[1] - '0');
    *month = (int) ((date[3] - '0') * 10 + date[4] - '0');
    *year = ((int) (date[6] - '0')) * 1000 + ((int) (date[7] - '0')) * 100 + ((int) (date[8] - '0')) * 10 + ((int) (date[9] - '0'));
}

bool is_leap(int year)
{
    if (year % LEAP_YEAR_MULTIPLICITY == 0)
    {
        if (year % LEAP_YEAR_MULTIPLICITY_FALSE == 0)
            return (year % LEAP_YEAR_MULTIPLICITY_TRUE == 0);
        return true;
    }
    return false;
}

bool check_day(int day, int month, int year)
{
    int max_day;
    switch (month)
    {
        case 1:
            max_day = JANUARY_DAYS;
            break;
        case 2:
            if (is_leap(year))
                max_day = FEBRUARY_DAYS_LEAP;
            else
                max_day = FEBRUARY_DAYS;
            break;
        case 3:
            max_day = MARCH_DAYS;
            break;
        case 4:
            max_day = APRIL_DAYS;
            break;
        case 5:
            max_day = MAY_DAYS;
            break;
        case 6:
            max_day = JUNE_DAYS;
            break;
        case 7:
            max_day = JULY_DAYS;
            break;
        case 8:
            max_day = AUGUST_DAYS;
            break;
        case 9:
            max_day = SEPTEMBER_DAYS;
            break;
        case 10:
            max_day = OCTOBER_DAYS;
            break;
        case 11:
            max_day = NOVEMBER_DAYS;
            break;
        case 12:
            max_day = DECEMBER_DAYS;
            break;
    }
    return (day >= 1 && day <= max_day);
}