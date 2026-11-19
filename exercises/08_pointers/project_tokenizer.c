// project_tokenizer.c - PROJECT: In-place tokenizer & array tools
//
// Real C code often works *in place*: instead of allocating new strings,
// it modifies the input buffer and hands back pointers into it.
//
//   char *trim(char *s)
//       Removes leading and trailing whitespace. Trailing spaces are removed
//       by writing a '\0'; leading ones by returning a pointer past them.
//
//   size_t split(char *s, char sep, char *parts[], size_t max_parts)
//       Splits s on `sep` by replacing each separator with '\0' and storing
//       a pointer to the start of each piece in parts. Stores at most
//       max_parts pointers (any remaining text stays in the last part).
//       Returns the number of parts. "a,b,,c" gives "a", "b", "", "c".
//
//   void reverse_range(int *begin, int *end)
//       Reverses the elements in [begin, end) using two pointers.
//
//   void rotate_left(int *arr, size_t n, size_t k)
//       Rotates arr left by k places: {1,2,3,4,5} by 2 -> {3,4,5,1,2}.
//       Trick: reverse the first k, reverse the rest, reverse everything.
//
//   size_t dedupe(int *arr, size_t n)
//       arr is sorted. Removes duplicates in place so the unique values are
//       at the front, and returns how many unique values there are.

// I AM NOT DONE

#include <ctype.h>
#include <stddef.h>
#include <string.h>

#include "clings.h"

// Write your functions here.

int main(void) {
    char padded[] = "   hello world  \t\n";
    CHECK_STR(trim(padded), "hello world");
    char empty[] = "    ";
    CHECK_STR(trim(empty), "");

    char csv[] = "name,age,,city";
    char *parts[8];
    size_t n = split(csv, ',', parts, 8);
    CHECK_INT(n, 4);
    if (n == 4) {
        CHECK_STR(parts[0], "name");
        CHECK_STR(parts[1], "age");
        CHECK_STR(parts[2], "");
        CHECK_STR(parts[3], "city");
        CHECK(parts[0] == csv);  // pointers INTO the original buffer
    }

    char path[] = "usr/local/bin/clings";
    n = split(path, '/', parts, 2);
    CHECK_INT(n, 2);
    if (n == 2) {
        CHECK_STR(parts[0], "usr");
        CHECK_STR(parts[1], "local/bin/clings");
    }

    int nums[] = {1, 2, 3, 4, 5, 6, 7};
    rotate_left(nums, 7, 3);
    int rotated[] = {4, 5, 6, 7, 1, 2, 3};
    for (size_t i = 0; i < 7; i++) {
        CHECK_INT(nums[i], rotated[i]);
    }

    int sorted[] = {1, 1, 2, 3, 3, 3, 7, 9, 9};
    size_t u = dedupe(sorted, 9);
    CHECK_INT(u, 5);
    int unique[] = {1, 2, 3, 7, 9};
    for (size_t i = 0; i < 5; i++) {
        CHECK_INT(sorted[i], unique[i]);
    }
    CHECK_INT(dedupe(sorted, 0), 0);

    return clings_report();
}
