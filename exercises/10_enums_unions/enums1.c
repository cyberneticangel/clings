// enums1.c
//
// An enum defines a set of named integer constants:
//
//     enum Direction { NORTH, EAST, SOUTH, WEST };   // 0, 1, 2, 3
//
// Enums make code much more readable than magic numbers. When you switch on
// an enum without a `default:`, the compiler can warn you if you forgot to
// handle one of the values (-Wswitch).
//
// Someone added PURPLE to the enum but didn't update `hex_code`.
// Fix it, then implement `next_light`.

// I AM NOT DONE

#include "clings.h"

typedef enum { RED, GREEN, BLUE, PURPLE } Color;

unsigned hex_code(Color c) {
    switch (c) {
    case RED:
        return 0xFF0000;
    case GREEN:
        return 0x00FF00;
    case BLUE:
        return 0x0000FF;
    }
    return 0;
}

typedef enum { LIGHT_RED, LIGHT_YELLOW, LIGHT_GREEN } TrafficLight;

// red -> green -> yellow -> red -> ...
TrafficLight next_light(TrafficLight current) {
    // TODO
}

int main(void) {
    CHECK_INT(hex_code(RED), 0xFF0000);
    CHECK_INT(hex_code(BLUE), 0x0000FF);
    CHECK_INT(hex_code(PURPLE), 0x800080);

    CHECK_INT(next_light(LIGHT_RED), LIGHT_GREEN);
    CHECK_INT(next_light(LIGHT_GREEN), LIGHT_YELLOW);
    CHECK_INT(next_light(LIGHT_YELLOW), LIGHT_RED);

    // Enum values are just ints.
    CHECK_INT(BLUE, FIXME);

    return clings_report();
}
