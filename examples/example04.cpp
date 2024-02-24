#include <iostream>
#include <iomanip>
#include <cmath>
#include "../mpfr_class.h" // Adjust the path to the header file appropriately

int main() {
    int decimal_precision = 50;                                                         // You can change this value to adjust the precision
    int bit_precision = static_cast<int>(std::ceil(decimal_precision * std::log2(10))); // Calculate bit precision from decimal

    // Initialization and precision setting
    mpfr::mpfr_class x(1.0);   // Initial value x_0 = 1.0
    mpfr::mpfr_class two(2.0); // Constant 2
    x.set_prec(bit_precision); // Set the precision of x based on calculated bit precision

    std::cout << std::fixed << std::setprecision(decimal_precision); // Set output to fixed point notation with desired digits

    // Calculating sqrt(2) using Newton's method
    for (int i = 0; i < 10; ++i) { // For example, calculate with 10 iterations
        x = (x + two / x) / 2;     // x_{n+1} = (x_n + 2 / x_n) / 2
        std::cout << "Iteration " << i + 1 << ": " << x << std::endl;
    }

    // Comparison with mpfr::sqrt
    mpfr::mpfr_class sqrt2 = mpfr::mpfr_class::sqrt(two, MPFR_RNDN); // Calculate sqrt(2) using MPFR
    std::cout << "Result using mpfr::sqrt: " << sqrt2 << std::endl;

    return 0;
}
