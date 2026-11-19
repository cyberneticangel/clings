// enums1.c - solution

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
    case PURPLE:
        return 0x800080;
    }
    return 0;
}

typedef enum { LIGHT_RED, LIGHT_YELLOW, LIGHT_GREEN } TrafficLight;

TrafficLight next_light(TrafficLight current) {
    switch (current) {
    case LIGHT_RED:
        return LIGHT_GREEN;
    case LIGHT_GREEN:
        return LIGHT_YELLOW;
    case LIGHT_YELLOW:
        return LIGHT_RED;
    }
    return LIGHT_RED;
}

int main(void) {
    CHECK_INT(hex_code(RED), 0xFF0000);
    CHECK_INT(hex_code(BLUE), 0x0000FF);
    CHECK_INT(hex_code(PURPLE), 0x800080);

    CHECK_INT(next_light(LIGHT_RED), LIGHT_GREEN);
    CHECK_INT(next_light(LIGHT_GREEN), LIGHT_YELLOW);
    CHECK_INT(next_light(LIGHT_YELLOW), LIGHT_RED);

    CHECK_INT(BLUE, 2);

    return clings_report();
}
