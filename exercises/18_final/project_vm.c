// project_vm.c - FINAL PROJECT: A tiny virtual machine
//
// Congratulations on making it this far! The final project is a small
// stack-based virtual machine: the same idea that powers the JVM, Python's
// interpreter, and WebAssembly. It uses nearly everything from the course:
// enums, structs, unions-free tagged data, arrays, pointers, switch,
// dynamic memory, function pointers and error handling.
//
// A program is an array of Instructions. Each has an opcode and an operand
// (only some opcodes use the operand). The VM has:
//   * a value stack (long values)
//   * a program counter `pc`: index of the next instruction to run
//   * an output StrBuf-like buffer where OP_PRINT writes
//
// Opcodes (`a` is the operand):
//   OP_PUSH a     push a
//   OP_POP        discard the top value
//   OP_DUP        push a copy of the top value
//   OP_SWAP       swap the top two values
//   OP_ADD, OP_SUB, OP_MUL, OP_DIV, OP_MOD
//                 pop b, pop a, push (a op b). Division/mod by 0 is an error.
//   OP_LT         pop b, pop a, push 1 if a < b else 0
//   OP_JMP a      jump to instruction a
//   OP_JZ a       pop v; if v == 0 jump to instruction a
//   OP_LOAD a     push the value of variable slot a (8 slots, start at 0)
//   OP_STORE a    pop v and store it in variable slot a
//   OP_PRINT      pop v and append it to the output followed by '\n'
//   OP_HALT       stop successfully
//
// vm_run returns VM_OK, or an error:
//   VM_ERR_STACK_UNDERFLOW  popping from an empty stack
//   VM_ERR_STACK_OVERFLOW   pushing onto a full stack (STACK_MAX)
//   VM_ERR_DIV_ZERO
//   VM_ERR_BAD_JUMP         jump target outside the program
//   VM_ERR_BAD_SLOT         variable slot outside 0..7
//   VM_ERR_NO_HALT          ran past the end of the program
//   VM_ERR_STEP_LIMIT       executed more than max_steps instructions
//                           (protects against infinite loops)
//
// The output buffer must grow dynamically (malloc/realloc), and vm_free
// must release it.
//
// Design tip: write small static helpers, e.g. `static VmError push(Vm *vm,
// long v)` and `static VmError pop(Vm *vm, long *out)`, and use them
// everywhere. For the arithmetic ops, consider a table of function pointers
// indexed by opcode, or a switch.

// I AM NOT DONE

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
    size_t sp;               // number of values on the stack
    long slots[NUM_SLOTS];
    size_t pc;
    char *out;               // heap allocated, '\0'-terminated (or NULL)
    size_t out_len;
    size_t out_cap;
} Vm;

// Write your code here:
//   void vm_init(Vm *vm)
//   void vm_free(Vm *vm)
//   VmError vm_run(Vm *vm, const Instruction *prog, size_t len, long max_steps)

#define LEN(a) (sizeof(a) / sizeof((a)[0]))

int main(void) {
    Vm vm;

    // 2 + 3 * 4
    Instruction arith[] = {
        {OP_PUSH, 2}, {OP_PUSH, 3}, {OP_PUSH, 4}, {OP_MUL, 0},
        {OP_ADD, 0},  {OP_PRINT, 0}, {OP_HALT, 0},
    };
    vm_init(&vm);
    CHECK_INT(vm_run(&vm, arith, LEN(arith), 1000), VM_OK);
    CHECK_STR(vm.out, "14\n");
    vm_free(&vm);

    // Countdown: for (i = 3; 0 < i; i = i - 1) print(i);
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

    // Factorial of 20 (the biggest that fits in a 64-bit long), plus a
    // lot of output to make sure the buffer grows.
    Instruction fact[] = {
        /* 0 */ {OP_PUSH, 1},  {OP_STORE, 0},          // acc = 1
        /* 2 */ {OP_PUSH, 1},  {OP_STORE, 1},          // i = 1
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

    // Errors
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
