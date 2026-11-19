// project_csv.c - PROJECT: CSV report generator
//
// Read employee records from a CSV file, aggregate them, and write a report
// file.
//
// Input format (first line is a header, which you should skip):
//     name,department,salary
//     Ada,Engineering,120000
//     ...
//
//   int load_employees(FILE *in, Employee *out, int cap)
//       Parses up to `cap` records. Skips the header line and any line that
//       doesn't parse. Returns the number of employees loaded.
//       sscanf tip: "%31[^,]" reads up to 31 characters that are NOT commas.
//
//   int summarize(const Employee *emps, int n, DeptSummary *out, int cap)
//       Groups employees by department (in order of first appearance),
//       counting them and summing salaries. Returns the number of
//       departments.
//
//   void write_report(FILE *out, const DeptSummary *depts, int n)
//       Writes one line per department, exactly in this format:
//           Engineering: 3 employees, average 110000
//       (average = total / count, integer division)

// I AM NOT DONE

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

// Write your functions here.

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
