#include <iostream>
#include <iomanip>
#include <cmath>           // For std::pow function
#include "../mpfr_class.h" // Set the correct path to the mpfr_class definition header

int main() {
    // Set initial values
    mpfr::mpfr_class one(1.0);
    mpfr::mpfr_class two(2.0);
    mpfr::mpfr_class four(4.0);
    mpfr::mpfr_class a(one), b(one / mpfr::sqrt(two)), t(0.25), p(one);
    mpfr::mpfr_class a_next, b_next, t_next, pi;

    std::cout << std::fixed << std::setprecision(50); // Set output to fixed-point notation with 50 digits of precision

    for (int i = 0; i < 5; ++i) { // Number of iterations
        a_next = (a + b) / two;
        b_next = mpfr::sqrt(a * b);
        t_next = t - p * mpfr::pow(a - a_next, 2);
        p = two * p;

        // Update values for the next iteration
        a = a_next;
        b = b_next;
        t = t_next;

        // Calculate pi
        pi = mpfr::pow(a + b, two) / (four * t);

        std::cout << "Iteration " << i + 1 << ": π " << pi << std::endl;
    }

    return 0;
}
