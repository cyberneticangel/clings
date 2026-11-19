// intro1.c
//
// Welcome to clings! These exercises will teach you C, one small step at a
// time, by having you read and fix small programs.
//
// How it works:
//   * Each exercise is a .c file that either doesn't compile yet, or compiles
//     but fails some checks.
//   * Your job is to fix it. `./clings` watches your files and re-checks the
//     exercise every time you save.
//   * Exercises are compiled with lots of warnings turned into errors, plus
//     AddressSanitizer and UndefinedBehaviorSanitizer. Those tools catch many
//     classic C bugs (reading out of bounds, leaking memory, ...) that would
//     otherwise silently "work" until they didn't.
//   * When an exercise passes, delete the `I AM NOT DONE` line to move on.
//   * Stuck? Press `h` in watch mode, or run `./clings hint <name>`.
//
// This exercise already compiles and passes! Read through it, then delete the
// line below to continue.

// I AM NOT DONE

#include <stdio.h>

// Every C program starts executing in a function called `main`.
// `int` means main returns an integer to the operating system:
// 0 means success, anything else means failure.
int main(void) {
    printf("Hello and welcome to clings!\n");
    return 0;
}
