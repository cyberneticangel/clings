// functions5.c - solution

#include "clings.h"

long factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

int fib(int n) {
    if (n < 2) {
        return n;
    }
    return fib(n - 1) + fib(n - 2);
}

int main(void) {
    CHECK_INT(factorial(1), 1);
    CHECK_INT(factorial(5), 120);
    CHECK_INT(factorial(0), 1);

    CHECK_INT(fib(0), 0);
    CHECK_INT(fib(1), 1);
    CHECK_INT(fib(10), 55);

    return clings_report();
}
