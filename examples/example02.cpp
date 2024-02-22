// examples/example02.cpp
#include "../mpfr_class.h"
#include <iostream>
#include <iomanip>
#include <mpfr.h>

int main() {
    mpfrcxx::mpfr_class num(2.0);
    mpfrcxx::mpfr_class result;
    result = mpfrcxx::mpfr_class::sqrt(num);
std::cout << "Square root of 4.0 = " << std::setprecision(50) << result << std::endl;
    return 0;
}
