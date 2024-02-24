#include <iostream>
#include <iomanip>
#include <cmath>           // For std::log2 function
#include "../mpfr_class.h" // Include the definition of mpfr_class

int main() {
    // Calculate the number of bits corresponding to a precision of 50 digits
    const int decimal_precision = 50;
    const double bits_per_digit = std::log2(10.0);                                                // Calculate how many bits are needed per digit
    const long precision_bits = static_cast<long>(std::ceil(decimal_precision * bits_per_digit)); // Total bits for 50 decimal_precision

    // Set precision
    mpfr::defaults::set_default_prec(precision_bits + 5); // Apply this precision to all mpfr_class variables
    // unless +5, we'll get several inaccurate last decimal precision.

    // Set initial values for calculating exp(1)
    mpfr::mpfr_class x(1.0);    // Initialize x as 1 for calculating exp(1)
    mpfr::mpfr_class sum(1.0);  // Initialize sum as 1 for the first term of the series (0! = 1)
    mpfr::mpfr_class term(1.0); // Initialize the first term of the series as 1
    int n = 1;                  // Counter for the series term number

    // Calculate e using the Taylor series
    while (term > mpfr::mpfr_class(std::pow(10.0, -decimal_precision))) { // Continue until precision reaches 50 decimal_precision
        term *= x / mpfr::mpfr_class(n);                                  // Calculate the next term in the series
        sum += term;                                                      // Add the current term to the sum
        ++n;                                                              // Increment term counter
    }

    // Output the result with fixed point notation and set precision to 50 decimal_precision
    std::cout << "Calculating e in " << decimal_precision << " decimal precision" << std::endl;
    std::cout << std::fixed << std::setprecision(decimal_precision) << "using Taylor series:  " << sum << std::endl;
    // Calculate and output the value of e using MPFR's const_e function

    mpfr::mpfr_class const_e;
    const_e = mpfr::exp(mpfr::mpfr_class(1)); // Calculate the value of e using MPFR
    std::cout << "using MPFR's const_e: " << const_e << std::endl;

    return 0;
}
