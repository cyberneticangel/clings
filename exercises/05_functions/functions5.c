// functions5.c
//
// A function can call itself. That's *recursion*. Every recursive function
// needs a *base case* that stops the recursion; otherwise it calls itself
// forever until it runs out of stack space and crashes.
//
// Both functions below have a broken base case. Running this crashes with a
// "stack-overflow" error. Fix them.
//
//     factorial(0) = 1,  factorial(n) = n * factorial(n - 1)
//     fib(0) = 0, fib(1) = 1,  fib(n) = fib(n - 1) + fib(n - 2)

// I AM NOT DONE

#include "clings.h"

long factorial(int n) {
    if (n == 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

int fib(int n) {
    if (n == 0) {
        return 0;
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
