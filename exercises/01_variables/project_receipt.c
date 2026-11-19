// project_receipt.c - PROJECT: Splitting the bill
//
// Every section ends with a small project that pulls together everything
// you've learned so far. Projects are bigger than exercises and have fewer
// hints in the code. Take your time!
//
// You and two friends went out for dinner. Work out the bill.
//
// Money in programs is usually stored as a whole number of *cents*,
// never as floating point (you'll see why in the next section).
//
// Declare and compute each of the variables used in the checks below:
//
//   subtotal     - the sum of all the dishes and drinks
//   tax          - 8% of the subtotal, rounded DOWN to a whole cent
//                  (integer arithmetic rounds down for you)
//   tip          - 15% of the subtotal (before tax), rounded down
//   total        - subtotal + tax + tip
//   per_person   - total split between the 3 people, rounded down
//   leftover     - the cents that don't divide evenly (whoever pays the
//                  leftover gets a free mint)
//
// Use `const` for values that never change.

// I AM NOT DONE

#include "clings.h"

int main(void) {
    int pasta = 1450;    // $14.50
    int pizza = 1675;
    int salad = 925;
    int drinks = 3 * 350;

    // TODO: declare and compute the variables here.

    CHECK_INT(subtotal, 5100);
    CHECK_INT(tax, 408);
    CHECK_INT(tip, 765);
    CHECK_INT(total, 6273);
    CHECK_INT(per_person, 2091);
    CHECK_INT(leftover, 0);

    // Someone orders dessert after all! Update the subtotal and recompute
    // everything (you can reassign the same variables).
    int dessert = 800;
    // TODO

    CHECK_INT(subtotal, 5900);
    CHECK_INT(total, 7257);
    CHECK_INT(per_person, 2419);
    CHECK_INT(leftover, 0);

    return clings_report();
}
