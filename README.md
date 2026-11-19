# clings

Small exercises to get you used to reading and writing C, in the spirit of
[rustlings](https://github.com/rust-lang/rustlings).

You learn by fixing small programs. Each exercise either doesn't compile or
fails some checks. Your job is to fix it. A watcher re-checks your work every
time you save, then moves you on to the next exercise.

The exercises start with `printf` and variables and go up to pointers,
dynamic memory, data structures, file I/O and error handling. Every section
ends with a **project**: a small but real program that uses everything you've
learned so far. The final project is a working stack-based virtual machine.

```
Current exercise: exercises/08_pointers/pointers2.c

  x exercises/08_pointers/pointers2.c:37: a
      expected: 2
      got:      1
  1 of 4 checks failed

Progress: [###########################-----------------------] 44/83
[h] hint  [l] list  [r] re-run  [q] quit  (saving a file re-runs automatically)
```

## Getting started

You need:

- A C compiler: `gcc` or `clang`
- `bash` (3.2+ works, so the macOS default is fine)
- Linux or macOS. On Windows, use WSL.

```sh
git clone https://github.com/cyberneticangel/clings.git
cd clings
./clings
```

Then open the exercise it names in your editor and start fixing.

## How it works

- Each exercise is a single `.c` file in `exercises/`. Read the comments at
  the top: they teach the concept and say what to do.
- `FIXME` marks a blank you must fill in. It's deliberately undefined, so the
  file won't compile until you replace it.
- Checks like `CHECK_INT(actual, expected)` and `CHECK_STR(...)` come from
  [`include/clings.h`](include/clings.h). When one fails you see the
  expected and actual values.
- Once an exercise compiles and every check passes, press **`n`** in watch
  mode to move on. clings then deletes the exercise's `// I AM NOT DONE`
  line for you (you can also delete it yourself). Moving on is manual so you
  have a moment to re-read the code and make sure you understand why it
  works.

### The compiler is strict on purpose

Exercises are built with:

```
-std=c17 -Wall -Wextra -Werror -fsanitize=address,undefined
```

Many classic C bugs compile without complaint and then misbehave quietly.
clings turns them into loud errors so you learn to recognize them:

| Bug                                   | Caught by                      |
| ------------------------------------- | ------------------------------ |
| `if (x = 5)`, `a < b < c`             | warnings (as errors)           |
| missing `break` in a `switch`         | `-Wimplicit-fallthrough`       |
| reading/writing past an array's end   | AddressSanitizer               |
| use after `free`, double `free`       | AddressSanitizer               |
| forgetting to `free`                  | LeakSanitizer (Linux)          |
| signed integer overflow               | UndefinedBehaviorSanitizer     |

Sanitizer reports look scary, but the useful part is easy to find: look for
the first line that points to *your* file and line number.

## Commands

| Command                  | What it does                                            |
| ------------------------ | ------------------------------------------------------- |
| `./clings`               | Watch mode: work through the exercises in order         |
| `./clings run <name>`    | Compile and run a single exercise                       |
| `./clings hint <name>`   | Show the hint for an exercise                           |
| `./clings list`          | List every exercise and whether it's done               |
| `./clings verify`        | Check everything in order and stop at the first unfinished one |
| `./clings next`          | Print the next unfinished exercise                      |

In watch mode:

| Key | Action |
| --- | ------ |
| `n` | Next exercise (once the current one passes). When reviewing, step forward |
| `b` | Back to the previous, already finished exercise, to review or tinker with it |
| `c` | While reviewing, jump straight back to your current exercise |
| `h` | Show a hint |
| `l` | List all exercises |
| `r` | Re-run the checks |
| `q` | Quit (your progress is saved in the files themselves) |

If you break a finished exercise while reviewing it, it becomes your current
exercise again until you fix it.

Set `CC=clang ./clings` to use a different compiler.

## Curriculum

| #  | Topic              | You'll learn                                                    | Project |
| -- | ------------------ | --------------------------------------------------------------- | ------- |
| 00 | Intro              | how clings works, `#include`, `main`                            | |
| 01 | Variables          | declarations, assignment, scope, `const`                        | **receipt**: split a restaurant bill |
| 02 | Types              | `char`/`int`/`double`, `sizeof`, casts, overflow, `<stdint.h>`  | **units**: a unit converter |
| 03 | Operators          | `/` and `%`, precedence, `++`, comparison & logic gotchas       | **clock**: time, coins & checksums |
| 04 | Control flow       | `if`, `switch` & fall-through, `for`/`while`/`do`, `break`      | **numbers**: FizzBuzz, Collatz, primes, perfect numbers |
| 05 | Functions          | prototypes, signatures, pass-by-value, `static`, recursion      | **calendar**: leap years, day of week |
| 06 | Arrays             | indexing, bounds, decay to pointers, 2D arrays                  | **stats**: mean, median, sorting, histograms |
| 07 | Strings            | `'\0'`, `strcmp`, writing `strlen`, literals vs arrays, `snprintf` | **text**: word count, palindromes, Caesar cipher |
| 08 | Pointers           | `&` and `*`, out-parameters, pointer arithmetic, `NULL`, dangling pointers, `**` | **tokenizer**: in-place trim/split, rotate, dedupe |
| 09 | Structs            | definitions, `typedef`, `->`, nesting, arrays of structs        | **inventory**: a shop inventory system |
| 10 | Enums & unions     | enums with `switch`, tagged unions                              | **calculator**: an RPN calculator |
| 11 | Memory             | `malloc`/`free`, leaks, use-after-free, `realloc`, `calloc`     | **strbuf**: a growable string builder |
| 12 | Preprocessor       | macro pitfalls, `#if`, `#x`, include guards                      | **xmacros**: `MIN`/`SWAP`/test macros, X-macros |
| 13 | Function pointers  | callbacks, `qsort` comparators, `void *`                        | **events**: an event bus with callbacks |
| 14 | Bits               | `& \| ^ ~ << >>`, masks, flags                                  | **bitset**: a bitset and the Sieve of Eratosthenes |
| 15 | Data structures    | linked lists, `Node **` tricks, binary search trees             | **wordfreq**: a hash map word counter |
| 16 | File I/O           | `FILE *`, `fprintf`, `fgets`, `sscanf`                          | **csv**: a CSV report generator |
| 17 | Error handling     | `strtol` + `errno`, error codes, `goto` cleanup                 | **config**: a config parser with line-numbered errors |
| 18 | Final              |                                                                 | **vm**: a stack-based virtual machine |

There are 83 exercises in total, 18 of them projects.

## Stuck?

1. Re-read the comment at the top of the exercise.
2. Read the compiler error or sanitizer report carefully. The answer is
   often right there.
3. Press `h` (or run `./clings hint <name>`).
4. Reference solutions are in [`solutions/`](solutions/). Try not to peek
   too early!

To start an exercise over, restore it with git:

```sh
git checkout -- exercises/08_pointers/pointers2.c
```

## Repository layout

```
clings             the runner (a bash script)
info               the order exercises are presented in
include/clings.h   CHECK macros used by the exercises
exercises/         the exercises, by topic
solutions/         reference solutions, same layout
hints/             one hint per exercise
scripts/           maintainer tools
```

## Contributing

Each exercise needs a matching file in `solutions/`, a hint in
`hints/<name>.txt`, and an entry in `info`. Before sending a change, run:

```sh
scripts/check-all.sh            # and: CC=clang scripts/check-all.sh
```

It checks that every solution passes and that every exercise fails as
shipped.

## License

[MIT](LICENSE)
