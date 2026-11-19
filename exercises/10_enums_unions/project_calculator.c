// project_calculator.c - PROJECT: RPN calculator
//
// Reverse Polish Notation puts operators AFTER their operands, so no
// parentheses are ever needed:
//
//     "3 4 +"        = 3 + 4          = 7
//     "5 1 2 + 4 * + 3 -"  = 5 + (1 + 2) * 4 - 3 = 14
//
// Evaluating it is simple with a stack: push numbers; when you see an
// operator, pop two numbers, apply it, push the result. At the end exactly
// one number should remain.
//
// Your job, in two steps:
//
//   1. size_t tokenize(const char *input, Token *out, size_t cap)
//      Turn the input into Tokens. A Token is a tagged union: either a
//      number (TOK_NUM, value in .num) or an operator (TOK_OP, one of
//      + - * / in .op). Tokens are separated by spaces. Numbers are
//      non-negative integers. Return the number of tokens. (You can assume
//      the input is well-formed and fits in `cap` tokens.)
//
//   2. CalcError evaluate(const Token *tokens, size_t n, long *result)
//      Run the stack algorithm. Return:
//        CALC_OK              on success (store the answer in *result)
//        CALC_STACK_UNDERFLOW if an operator doesn't have two operands
//        CALC_DIV_BY_ZERO     on division by zero
//        CALC_LEFTOVER        if anything other than one value remains
//      Use a plain array of size STACK_MAX as the stack.

// I AM NOT DONE

#include <ctype.h>
#include <stddef.h>

#include "clings.h"

#define STACK_MAX 64

typedef enum { TOK_NUM, TOK_OP } TokenKind;

typedef struct {
    TokenKind kind;
    union {
        long num;
        char op;
    };
} Token;

typedef enum {
    CALC_OK,
    CALC_STACK_UNDERFLOW,
    CALC_DIV_BY_ZERO,
    CALC_LEFTOVER,
} CalcError;

// Write your functions here.

// A helper for the checks: tokenize + evaluate in one go.
CalcError calc(const char *input, long *result) {
    Token tokens[STACK_MAX];
    size_t n = tokenize(input, tokens, STACK_MAX);
    return evaluate(tokens, n, result);
}

int main(void) {
    Token t[8];
    size_t n = tokenize("12 3 +", t, 8);
    CHECK_INT(n, 3);
    if (n == 3) {
        CHECK_INT(t[0].kind, TOK_NUM);
        CHECK_INT(t[0].num, 12);
        CHECK_INT(t[1].num, 3);
        CHECK_INT(t[2].kind, TOK_OP);
        CHECK_INT(t[2].op, '+');
    }

    long r = 0;
    CHECK_INT(calc("3 4 +", &r), CALC_OK);
    CHECK_INT(r, 7);
    CHECK_INT(calc("5 1 2 + 4 * + 3 -", &r), CALC_OK);
    CHECK_INT(r, 14);
    CHECK_INT(calc("100 7 /", &r), CALC_OK);
    CHECK_INT(r, 14);
    CHECK_INT(calc("   42   ", &r), CALC_OK);
    CHECK_INT(r, 42);

    CHECK_INT(calc("1 +", &r), CALC_STACK_UNDERFLOW);
    CHECK_INT(calc("4 0 /", &r), CALC_DIV_BY_ZERO);
    CHECK_INT(calc("1 2 3 +", &r), CALC_LEFTOVER);
    CHECK_INT(calc("", &r), CALC_LEFTOVER);

    return clings_report();
}
