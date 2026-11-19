// project_receipt.c - solution

#include "clings.h"

int main(void) {
    int pasta = 1450;
    int pizza = 1675;
    int salad = 925;
    int drinks = 3 * 350;

    const int tax_percent = 8;
    const int tip_percent = 15;
    const int people = 3;

    int subtotal = pasta + pizza + salad + drinks;
    int tax = subtotal * tax_percent / 100;
    int tip = subtotal * tip_percent / 100;
    int total = subtotal + tax + tip;
    int per_person = total / people;
    int leftover = total % people;

    CHECK_INT(subtotal, 5100);
    CHECK_INT(tax, 408);
    CHECK_INT(tip, 765);
    CHECK_INT(total, 6273);
    CHECK_INT(per_person, 2091);
    CHECK_INT(leftover, 0);

    int dessert = 800;
    subtotal = subtotal + dessert;
    tax = subtotal * tax_percent / 100;
    tip = subtotal * tip_percent / 100;
    total = subtotal + tax + tip;
    per_person = total / people;
    leftover = total % people;

    CHECK_INT(subtotal, 5900);
    CHECK_INT(total, 7257);
    CHECK_INT(per_person, 2419);
    CHECK_INT(leftover, 0);

    return clings_report();
}
