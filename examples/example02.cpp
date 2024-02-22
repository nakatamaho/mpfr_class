// examples/example02.cpp
#include "../mpfr_class.h"
#include <iostream>
#include <mpfr.h>

int main() {
mpfrcxx::mpfr_class num(4.0);
mpfrcxx::mpfr_class result;
    mpfr_sqrt(result.value, num.value, MPFR_RNDN);
std::cout << "Square root of 4.0 = " << result << std::endl;
    return 0;
}
