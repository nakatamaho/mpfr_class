// examples/example02.cpp
#include "mpfr_class.h"
#include <iostream>
#include <iomanip>
#include <mpfr.h>

int main() {
    mpfr::mpfr_class num(2.0);
    mpfr::mpfr_class result;
    result = sqrt(num);
    std::cout << "Square root of 2.0 = " << std::setprecision(50) << result << std::endl;
    return 0;
}
