#include "mpfr_class.h"
#include <iostream>

int main() {
    mpfr::mpfr_class num1(1.5);
    mpfr::mpfr_class num2(2.5);
    mpfr::mpfr_class result = num1 + num2;
    std::cout << "Result of 1.5 + 2.5 = " << result << std::endl;
    return 0;
}
