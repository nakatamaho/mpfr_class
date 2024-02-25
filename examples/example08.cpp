// https://rosettacode.org/wiki/Pathological_floating_point_problems
#include <iostream>
#include <mpfr.h>
#include "../mpfr_class.h"

void calculate_sequence(int prec) {
    mpfr::defaults::set_default_prec(prec);
    mpfr::mpfr_class v1(2), v2(-4), vn, diff;
    int m = 10000;
    const mpfr::mpfr_class eps("1e-64");
    std::cout.precision(50);
    bool hasConverged = false;

    for (int n = 3; n <= m && !hasConverged; ++n) {
        vn = mpfr::mpfr_class("111") - mpfr::mpfr_class("1130") / v2 + mpfr::mpfr_class("3000") / (v2 * v1);

        diff = abs(vn - v2);

        if (diff < eps) {
            hasConverged = true;
            std::cout << "Sequence has converged at v" << n << " using precicision: " << prec << " bits" << std::endl;
            std::cout << "correct limit is 6" << std::endl;
        }
        v1 = v2;
        v2 = vn;
        std::cout << "v" << n << ": " << vn << std::endl;
    }
}

int main() {
    calculate_sequence(53);
    calculate_sequence(113);
    calculate_sequence(256);
    calculate_sequence(2048);
    calculate_sequence(4096);

    return 0;
}
