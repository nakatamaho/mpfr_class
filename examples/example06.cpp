#include <iostream>
#include <mpfr.h>
#include "../mpfr_class.h"

void calculate_and_print_rumps_example(int prec) {
    mpfr::defaults::set_default_prec(prec);
    mpfr::mpfr_class a("77617.0"), b("33096.0");
    mpfr::mpfr_class result = mpfr::mpfr_class("333.75") * b * b * b * b * b * b + (a * a) * ((mpfr::mpfr_class("11") * (a * a) * (b * b)) - (b * b * b * b * b * b) - (mpfr::mpfr_class("121") * (b * b) * (b * b)) - mpfr::mpfr_class("2")) + mpfr::mpfr_class("5.5") * b * b * b * b * b * b * b * b + mpfr::mpfr_class("0.5") * (a / b);

    std::cout.precision(34);
    std::cout << "Precision: " << prec << " bits" << std::endl;
    std::cout << "Result: " << result << std::endl << std::endl;
}

int main() {
    std::cout << "Rump's example" << std::endl;
    calculate_and_print_rumps_example(53);
    calculate_and_print_rumps_example(113);
    calculate_and_print_rumps_example(256);
    calculate_and_print_rumps_example(512);

    return 0;
}
