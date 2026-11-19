// if2.c - solution

#include "clings.h"

char letter_grade(int score) {
    if (score >= 90) {
        return 'A';
    } else if (score >= 80) {
        return 'B';
    } else if (score >= 70) {
        return 'C';
    } else if (score >= 60) {
        return 'D';
    } else {
        return 'F';
    }
}

int main(void) {
    CHECK_INT(letter_grade(95), 'A');
    CHECK_INT(letter_grade(90), 'A');
    CHECK_INT(letter_grade(85), 'B');
    CHECK_INT(letter_grade(70), 'C');
    CHECK_INT(letter_grade(61), 'D');
    CHECK_INT(letter_grade(12), 'F');

    return clings_report();
}
