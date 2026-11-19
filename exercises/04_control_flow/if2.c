// if2.c
//
// In an if / else if chain, the *first* matching branch wins and the rest
// are skipped. Order matters!
//
// `letter_grade` should return:
//     'A' for 90 and above
//     'B' for 80-89
//     'C' for 70-79
//     'D' for 60-69
//     'F' for anything below 60
//
// It compiles, but it's wrong. Fix it.

// I AM NOT DONE

#include "clings.h"

char letter_grade(int score) {
    if (score >= 60) {
        return 'D';
    } else if (score >= 70) {
        return 'C';
    } else if (score >= 80) {
        return 'B';
    } else if (score >= 90) {
        return 'A';
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
