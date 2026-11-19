// project_calendar.c - PROJECT: Calendar toolkit
//
// Build a few calendar functions from scratch. Each one should be short;
// later functions should *call* earlier ones rather than repeating logic.
//
//   bool is_leap_year(int year)
//       Divisible by 4, EXCEPT years divisible by 100, EXCEPT years divisible
//       by 400. So 1996 and 2000 are leap years; 1900 and 2023 are not.
//
//   int days_in_month(int month, int year)
//       Months are 1-12. February has 29 days in leap years.
//       Return 0 for an invalid month.
//
//   int day_of_year(int day, int month, int year)
//       1 for January 1st, 32 for February 1st, ...
//
//   int day_of_week(int day, int month, int year)
//       0 = Sunday, 1 = Monday, ..., 6 = Saturday.
//       Hint: January 1st, 1900 was a Monday. Count the days since then
//       (only dates from 1900 onward are tested).
//
// Write the prototypes, the functions, and nothing else. main is done.

// I AM NOT DONE

#include <stdbool.h>

#include "clings.h"

// Write your functions here.

int main(void) {
    CHECK(is_leap_year(1996));
    CHECK(is_leap_year(2000));
    CHECK(!is_leap_year(1900));
    CHECK(!is_leap_year(2023));

    CHECK_INT(days_in_month(1, 2023), 31);
    CHECK_INT(days_in_month(2, 2023), 28);
    CHECK_INT(days_in_month(2, 2024), 29);
    CHECK_INT(days_in_month(4, 2023), 30);
    CHECK_INT(days_in_month(13, 2023), 0);

    CHECK_INT(day_of_year(1, 1, 2023), 1);
    CHECK_INT(day_of_year(1, 2, 2023), 32);
    CHECK_INT(day_of_year(31, 12, 2023), 365);
    CHECK_INT(day_of_year(31, 12, 2024), 366);

    CHECK_INT(day_of_week(1, 1, 1900), 1);   // Monday
    CHECK_INT(day_of_week(20, 7, 1969), 0);  // Moon landing: Sunday
    CHECK_INT(day_of_week(1, 1, 2000), 6);   // Saturday
    CHECK_INT(day_of_week(29, 2, 2024), 4);  // Thursday

    return clings_report();
}
