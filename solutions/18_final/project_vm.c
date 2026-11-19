// project_vm.c - solution

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clings.h"

#define STACK_MAX 32
#define NUM_SLOTS 8

typedef enum {
    OP_PUSH, OP_POP, OP_DUP, OP_SWAP,
    OP_ADD, OP_SUB, OP_MUL, OP_DIV, OP_MOD, OP_LT,
    OP_JMP, OP_JZ,
    OP_LOAD, OP_STORE,
    OP_PRINT, OP_HALT,
} Opcode;

typedef struct {
    Opcode op;
    long arg;
} Instruction;

typedef enum {
    VM_OK,
    VM_ERR_STACK_UNDERFLOW,
    VM_ERR_STACK_OVERFLOW,
    VM_ERR_DIV_ZERO,
    VM_ERR_BAD_JUMP,
    VM_ERR_BAD_SLOT,
    VM_ERR_NO_HALT,
    VM_ERR_STEP_LIMIT,
} VmError;

typedef struct {
    long stack[STACK_MAX];
    size_t sp;
    long slots[NUM_SLOTS];
    size_t pc;
    char *out;
    size_t out_len;
    size_t out_cap;
} Vm;

void vm_init(Vm *vm) {
    memset(vm, 0, sizeof(*vm));
}

void vm_free(Vm *vm) {
    free(vm->out);
    vm->out = NULL;
    vm->out_len = 0;
    vm->out_cap = 0;
}

static VmError push(Vm *vm, long v) {
    if (vm->sp == STACK_MAX) {
        return VM_ERR_STACK_OVERFLOW;
    }
    vm->stack[vm->sp++] = v;
    return VM_OK;
}

static VmError pop(Vm *vm, long *out) {
    if (vm->sp == 0) {
        return VM_ERR_STACK_UNDERFLOW;
    }
    *out = vm->stack[--vm->sp];
    return VM_OK;
}

static bool emit(Vm *vm, long v) {
    char tmp[32];
    int n = snprintf(tmp, sizeof(tmp), "%ld\n", v);
    size_t needed = vm->out_len + (size_t)n + 1;
    if (needed > vm->out_cap) {
        size_t cap = vm->out_cap ? vm->out_cap : 16;
        while (cap < needed) {
            cap *= 2;
        }
        char *p = realloc(vm->out, cap);
        if (p == NULL) {
            return false;
        }
        vm->out = p;
        vm->out_cap = cap;
    }
    memcpy(vm->out + vm->out_len, tmp, (size_t)n + 1);
    vm->out_len += (size_t)n;
    return true;
}

typedef long (*BinOp)(long, long);
static long op_add(long a, long b) { return a + b; }
static long op_sub(long a, long b) { return a - b; }
static long op_mul(long a, long b) { return a * b; }
static long op_div(long a, long b) { return a / b; }
static long op_mod(long a, long b) { return a % b; }
static long op_lt(long a, long b) { return a < b; }

static BinOp binop_for(Opcode op) {
    switch (op) {
    case OP_ADD: return op_add;
    case OP_SUB: return op_sub;
    case OP_MUL: return op_mul;
    case OP_DIV: return op_div;
    case OP_MOD: return op_mod;
    case OP_LT: return op_lt;
    default: return NULL;
    }
}

#define TRY(expr)                 \
    do {                          \
        VmError try_err_ = (expr); \
        if (try_err_ != VM_OK) {  \
            return try_err_;      \
        }                         \
    } while (0)

VmError vm_run(Vm *vm, const Instruction *prog, size_t len, long max_steps) {
    long steps = 0;
    for (;;) {
        if (vm->pc >= len) {
            return VM_ERR_NO_HALT;
        }
        if (++steps > max_steps) {
            return VM_ERR_STEP_LIMIT;
        }
        Instruction ins = prog[vm->pc++];
        long a, b;
        switch (ins.op) {
        case OP_PUSH:
            TRY(push(vm, ins.arg));
            break;
        case OP_POP:
            TRY(pop(vm, &a));
            break;
        case OP_DUP:
            TRY(pop(vm, &a));
            TRY(push(vm, a));
            TRY(push(vm, a));
            break;
        case OP_SWAP:
            TRY(pop(vm, &b));
            TRY(pop(vm, &a));
            TRY(push(vm, b));
            TRY(push(vm, a));
            break;
        case OP_ADD:
        case OP_SUB:
        case OP_MUL:
        case OP_DIV:
        case OP_MOD:
        case OP_LT:
            TRY(pop(vm, &b));
            TRY(pop(vm, &a));
            if ((ins.op == OP_DIV || ins.op == OP_MOD) && b == 0) {
                return VM_ERR_DIV_ZERO;
            }
            TRY(push(vm, binop_for(ins.op)(a, b)));
            break;
        case OP_JMP:
        case OP_JZ:
            if (ins.arg < 0 || (size_t)ins.arg >= len) {
                return VM_ERR_BAD_JUMP;
            }
            if (ins.op == OP_JZ) {
                TRY(pop(vm, &a));
                if (a != 0) {
                    break;
                }
            }
            vm->pc = (size_t)ins.arg;
            break;
        case OP_LOAD:
        case OP_STORE:
            if (ins.arg < 0 || ins.arg >= NUM_SLOTS) {
                return VM_ERR_BAD_SLOT;
            }
            if (ins.op == OP_LOAD) {
                TRY(push(vm, vm->slots[ins.arg]));
            } else {
                TRY(pop(vm, &vm->slots[ins.arg]));
            }
            break;
        case OP_PRINT:
            TRY(pop(vm, &a));
            if (!emit(vm, a)) {
                return VM_ERR_STACK_OVERFLOW;
            }
            break;
        case OP_HALT:
            return VM_OK;
        }
    }
}

#define LEN(a) (sizeof(a) / sizeof((a)[0]))

int main(void) {
    Vm vm;

    Instruction arith[] = {
        {OP_PUSH, 2}, {OP_PUSH, 3}, {OP_PUSH, 4}, {OP_MUL, 0},
        {OP_ADD, 0},  {OP_PRINT, 0}, {OP_HALT, 0},
    };
    vm_init(&vm);
    CHECK_INT(vm_run(&vm, arith, LEN(arith), 1000), VM_OK);
    CHECK_STR(vm.out, "14\n");
    vm_free(&vm);

    Instruction countdown[] = {
        /* 0 */ {OP_PUSH, 3},  {OP_STORE, 0},
        /* 2 */ {OP_PUSH, 0},  {OP_LOAD, 0},  {OP_LT, 0},  {OP_JZ, 13},
        /* 6 */ {OP_LOAD, 0},  {OP_PRINT, 0},
        /* 8 */ {OP_LOAD, 0},  {OP_PUSH, 1},  {OP_SUB, 0}, {OP_STORE, 0},
        /*12 */ {OP_JMP, 2},
        /*13 */ {OP_HALT, 0},
    };
    vm_init(&vm);
    CHECK_INT(vm_run(&vm, countdown, LEN(countdown), 1000), VM_OK);
    CHECK_STR(vm.out, "3\n2\n1\n");
    vm_free(&vm);

    Instruction fact[] = {
        /* 0 */ {OP_PUSH, 1},  {OP_STORE, 0},
        /* 2 */ {OP_PUSH, 1},  {OP_STORE, 1},
        /* 4 */ {OP_LOAD, 1},  {OP_PUSH, 21}, {OP_LT, 0}, {OP_JZ, 19},
        /* 8 */ {OP_LOAD, 0},  {OP_LOAD, 1},  {OP_MUL, 0}, {OP_DUP, 0},
        /*12 */ {OP_PRINT, 0}, {OP_STORE, 0},
        /*14 */ {OP_LOAD, 1},  {OP_PUSH, 1},  {OP_ADD, 0}, {OP_STORE, 1},
        /*18 */ {OP_JMP, 4},
        /*19 */ {OP_LOAD, 0},  {OP_PRINT, 0}, {OP_HALT, 0},
    };
    vm_init(&vm);
    CHECK_INT(vm_run(&vm, fact, LEN(fact), 10000), VM_OK);
    const char *last = vm.out ? strrchr(vm.out, '\n') : NULL;
    CHECK(last != NULL);
    CHECK(vm.out != NULL && strstr(vm.out, "2432902008176640000\n") != NULL);
    CHECK(vm.out != NULL && strncmp(vm.out, "1\n2\n6\n24\n120\n", 13) == 0);
    vm_free(&vm);
    CHECK(vm.out == NULL);

    struct {
        Instruction prog[4];
        size_t len;
        VmError expected;
    } bad[] = {
        {{{OP_ADD, 0}}, 1, VM_ERR_STACK_UNDERFLOW},
        {{{OP_PUSH, 1}, {OP_PUSH, 0}, {OP_DIV, 0}}, 3, VM_ERR_DIV_ZERO},
        {{{OP_PUSH, 1}, {OP_PUSH, 0}, {OP_MOD, 0}}, 3, VM_ERR_DIV_ZERO},
        {{{OP_JMP, 99}}, 1, VM_ERR_BAD_JUMP},
        {{{OP_LOAD, 8}}, 1, VM_ERR_BAD_SLOT},
        {{{OP_STORE, -1}}, 1, VM_ERR_BAD_SLOT},
        {{{OP_PUSH, 1}}, 1, VM_ERR_NO_HALT},
        {{{OP_JMP, 0}}, 1, VM_ERR_STEP_LIMIT},
        {{{OP_PUSH, 1}, {OP_DUP, 0}, {OP_JMP, 1}}, 3, VM_ERR_STACK_OVERFLOW},
    };
    for (size_t i = 0; i < LEN(bad); i++) {
        vm_init(&vm);
        VmError e = vm_run(&vm, bad[i].prog, bad[i].len, 1000);
        CHECK_INT(e, bad[i].expected);
        vm_free(&vm);
    }

    return clings_report();
}
