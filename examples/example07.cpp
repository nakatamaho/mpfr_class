#include <iostream>
#include <mpfr.h>
#include "mpfr_class.h"

void calculate_and_print_kashiwagi_example(mpfr_prec_t prec) {
    mpfr::defaults::set_default_prec(prec);
    mpfr::mpfr_class a("1e9");
    mpfr::mpfr_class one(1);
    mpfr::mpfr_class seven(7);
    mpfr::mpfr_class result = (a * a + one) * (a + one) * (a - one) - a * a * a * a + one / seven;

    std::cout.precision(34);
    std::cout << "Precision: " << prec << " bits" << std::endl;
    std::cout << "Result: " << result << std::endl << std::endl;
}

int main() {
    std::cout << "Kashiwagi's example" << std::endl;

    calculate_and_print_kashiwagi_example(53);  // IEEE 754 double precision
    calculate_and_print_kashiwagi_example(113); // IEEE 754 quadruple precision
    calculate_and_print_kashiwagi_example(256); // Higher precision
    calculate_and_print_kashiwagi_example(512); // Even higher precision
    return 0;
}
