// project_csv.c - solution

#include <stdio.h>
#include <string.h>

#include "clings.h"

typedef struct {
    char name[32];
    char dept[32];
    long salary;
} Employee;

typedef struct {
    char dept[32];
    int count;
    long total;
} DeptSummary;

int load_employees(FILE *in, Employee *out, int cap) {
    char line[256];
    int n = 0;
    if (fgets(line, sizeof(line), in) == NULL) { // header
        return 0;
    }
    while (n < cap && fgets(line, sizeof(line), in) != NULL) {
        Employee e;
        if (sscanf(line, "%31[^,],%31[^,],%ld", e.name, e.dept, &e.salary) == 3) {
            out[n++] = e;
        }
    }
    return n;
}

int summarize(const Employee *emps, int n, DeptSummary *out, int cap) {
    int d = 0;
    for (int i = 0; i < n; i++) {
        int j = 0;
        while (j < d && strcmp(out[j].dept, emps[i].dept) != 0) {
            j++;
        }
        if (j == d) {
            if (d == cap) {
                continue;
            }
            strcpy(out[d].dept, emps[i].dept);
            out[d].count = 0;
            out[d].total = 0;
            d++;
        }
        out[j].count++;
        out[j].total += emps[i].salary;
    }
    return d;
}

void write_report(FILE *out, const DeptSummary *depts, int n) {
    for (int i = 0; i < n; i++) {
        fprintf(out, "%s: %d employees, average %ld\n", depts[i].dept,
                depts[i].count, depts[i].total / depts[i].count);
    }
}

int main(void) {
    FILE *in = tmpfile();
    FILE *out = tmpfile();
    if (in == NULL || out == NULL) {
        perror("tmpfile");
        return 1;
    }
    fputs("name,department,salary\n"
          "Ada,Engineering,120000\n"
          "Grace,Engineering,130000\n"
          "Ken,Sales,70000\n"
          "this line is broken\n"
          "Barbara,Sales,90000\n"
          "Linus,Engineering,80000\n"
          "Margaret,Research,150000\n",
          in);
    rewind(in);

    Employee emps[16];
    int n = load_employees(in, emps, 16);
    CHECK_INT(n, 6);
    if (n >= 3) {
        CHECK_STR(emps[0].name, "Ada");
        CHECK_STR(emps[2].dept, "Sales");
        CHECK_INT(emps[2].salary, 70000);
    }

    DeptSummary depts[8];
    int d = summarize(emps, n, depts, 8);
    CHECK_INT(d, 3);

    write_report(out, depts, d);
    rewind(out);

    char line[128];
    const char *expected[] = {
        "Engineering: 3 employees, average 110000\n",
        "Sales: 2 employees, average 80000\n",
        "Research: 1 employees, average 150000\n",
    };
    int i = 0;
    while (fgets(line, sizeof(line), out) != NULL && i < 3) {
        CHECK_STR(line, expected[i]);
        i++;
    }
    CHECK_INT(i, 3);

    fclose(in);
    fclose(out);
    return clings_report();
}
