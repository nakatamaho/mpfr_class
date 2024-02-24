#include <iostream>
#include <iomanip>
#include <cmath>           // For std::log2 function
#include "../mpfr_class.h" // Include the definition of mpfr_class

int main() {
    // Calculate the number of bits corresponding to a precision of 50 digits
    const int digits = 50;
    const double bits_per_digit = std::log2(10.0);                                     // Calculate how many bits are needed per digit
    const long precision_bits = static_cast<long>(std::ceil(digits * bits_per_digit)); // Total bits for 50 digits

    // Set precision
    mpfr::defaults::set_default_prec(precision_bits); // Apply this precision to all mpfr_class variables

    // Set initial values for calculating exp(1)
    mpfr::mpfr_class x(1.0);    // Initialize x as 1 for calculating exp(1)
    mpfr::mpfr_class sum(1.0);  // Initialize sum as 1 for the first term of the series (0! = 1)
    mpfr::mpfr_class term(1.0); // Initialize the first term of the series as 1
    int n = 1;                  // Counter for the series term number

    // Calculate exp(1) using the Taylor series
    while (term > mpfr::mpfr_class(std::pow(10.0, -digits))) { // Continue until precision reaches 50 digits
        term *= x / mpfr::mpfr_class(n);                       // Calculate the next term in the series
        sum += term;                                           // Add the current term to the sum
        ++n;                                                   // Increment term counter
    }

    // Output the result with fixed point notation and set precision to 50 digits
    std::cout << std::fixed << std::setprecision(digits) << "Calculated exp(1) using Taylor series: " << sum << std::endl;

    return 0;
}
