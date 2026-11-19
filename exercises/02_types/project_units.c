// project_units.c - PROJECT: Unit converter
//
// Put your knowledge of types to work. Fill in each TODO with an
// expression. Watch out for:
//   * integer division where you want a fractional result
//   * types that are too small for the value
//   * casting a double to an int truncates toward zero
//
// Formulas:
//   fahrenheit = celsius * 9 / 5 + 32
//   1 mile = 1.609344 km
//   1 KiB = 1024 bytes, 1 MiB = 1024 KiB, 1 GiB = 1024 MiB

// I AM NOT DONE

#include <stdint.h>

#include "clings.h"

int main(void) {
    // --- temperature ---
    int celsius = 37;
    double fahrenheit = 0; // TODO
    CHECK_DBL(fahrenheit, 98.6);

    // --- distance ---
    double marathon_km = 42.195;
    double marathon_miles = 0; // TODO
    CHECK_DBL(marathon_miles, 26.218757);

    // Whole miles only (truncate):
    int whole_miles = 0; // TODO
    CHECK_INT(whole_miles, 26);

    // --- data sizes ---
    // A 4 GiB file. Choose a type that can hold its size in bytes!
    int file_bytes = 4 * 1024 * 1024 * 1024; // TODO: fix the type (and maybe the expression)
    CHECK_INT(file_bytes, 4294967296);

    // Size of a 1500000 byte file in MiB, as a double:
    int photo_bytes = 1500000;
    double photo_mib = 0; // TODO
    CHECK_DBL(photo_mib, 1.430511);

    // --- characters ---
    // Convert a digit character to its numeric value, and back.
    char digit_char = '7';
    int digit_value = 0; // TODO: use digit_char and '0'
    CHECK_INT(digit_value, 7);

    char next_char = 0;  // TODO: the character for digit_value + 1
    CHECK_INT(next_char, '8');

    return clings_report();
}
