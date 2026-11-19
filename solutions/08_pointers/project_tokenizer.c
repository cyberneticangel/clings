// project_tokenizer.c - solution

#include <ctype.h>
#include <stddef.h>
#include <string.h>

#include "clings.h"

char *trim(char *s) {
    while (isspace((unsigned char)*s)) {
        s++;
    }
    char *end = s + strlen(s);
    while (end > s && isspace((unsigned char)end[-1])) {
        end--;
    }
    *end = '\0';
    return s;
}

size_t split(char *s, char sep, char *parts[], size_t max_parts) {
    if (max_parts == 0) {
        return 0;
    }
    size_t n = 0;
    parts[n++] = s;
    for (char *p = s; *p != '\0' && n < max_parts; p++) {
        if (*p == sep) {
            *p = '\0';
            parts[n++] = p + 1;
        }
    }
    return n;
}

void reverse_range(int *begin, int *end) {
    while (end - begin > 1) {
        end--;
        int tmp = *begin;
        *begin = *end;
        *end = tmp;
        begin++;
    }
}

void rotate_left(int *arr, size_t n, size_t k) {
    if (n == 0) {
        return;
    }
    k %= n;
    reverse_range(arr, arr + k);
    reverse_range(arr + k, arr + n);
    reverse_range(arr, arr + n);
}

size_t dedupe(int *arr, size_t n) {
    if (n == 0) {
        return 0;
    }
    int *write = arr + 1;
    for (int *read = arr + 1; read < arr + n; read++) {
        if (*read != write[-1]) {
            *write++ = *read;
        }
    }
    return (size_t)(write - arr);
}

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
        CHECK(parts[0] == csv);
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
