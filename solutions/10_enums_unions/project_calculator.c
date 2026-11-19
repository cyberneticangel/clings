// project_calculator.c - solution

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

size_t tokenize(const char *input, Token *out, size_t cap) {
    size_t n = 0;
    const char *p = input;
    while (*p != '\0' && n < cap) {
        if (isspace((unsigned char)*p)) {
            p++;
        } else if (isdigit((unsigned char)*p)) {
            long value = 0;
            while (isdigit((unsigned char)*p)) {
                value = value * 10 + (*p - '0');
                p++;
            }
            out[n].kind = TOK_NUM;
            out[n].num = value;
            n++;
        } else {
            out[n].kind = TOK_OP;
            out[n].op = *p;
            n++;
            p++;
        }
    }
    return n;
}

CalcError evaluate(const Token *tokens, size_t n, long *result) {
    long stack[STACK_MAX];
    size_t top = 0;
    for (size_t i = 0; i < n; i++) {
        const Token *t = &tokens[i];
        switch (t->kind) {
        case TOK_NUM:
            stack[top++] = t->num;
            break;
        case TOK_OP: {
            if (top < 2) {
                return CALC_STACK_UNDERFLOW;
            }
            long b = stack[--top];
            long a = stack[--top];
            long r = 0;
            switch (t->op) {
            case '+': r = a + b; break;
            case '-': r = a - b; break;
            case '*': r = a * b; break;
            case '/':
                if (b == 0) {
                    return CALC_DIV_BY_ZERO;
                }
                r = a / b;
                break;
            }
            stack[top++] = r;
            break;
        }
        }
    }
    if (top != 1) {
        return CALC_LEFTOVER;
    }
    *result = stack[0];
    return CALC_OK;
}

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
