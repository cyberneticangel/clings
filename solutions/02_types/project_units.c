// project_units.c - solution

#include <stdint.h>

#include "clings.h"

int main(void) {
    int celsius = 37;
    double fahrenheit = celsius * 9.0 / 5 + 32;
    CHECK_DBL(fahrenheit, 98.6);

    double marathon_km = 42.195;
    double marathon_miles = marathon_km / 1.609344;
    CHECK_DBL(marathon_miles, 26.218757);

    int whole_miles = (int)marathon_miles;
    CHECK_INT(whole_miles, 26);

    uint64_t file_bytes = 4ULL * 1024 * 1024 * 1024;
    CHECK_INT(file_bytes, 4294967296);

    int photo_bytes = 1500000;
    double photo_mib = photo_bytes / (1024.0 * 1024.0);
    CHECK_DBL(photo_mib, 1.430511);

    char digit_char = '7';
    int digit_value = digit_char - '0';
    CHECK_INT(digit_value, 7);

    char next_char = (char)('0' + digit_value + 1);
    CHECK_INT(next_char, '8');

    return clings_report();
}
