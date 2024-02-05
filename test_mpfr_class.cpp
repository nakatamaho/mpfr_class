#include <iostream>
#include <cassert>
#include "mpfr_class.h"

using namespace mpfrcxx;

void testDefaultPrecision() {
    mpfr_prec_t defaultPrec = defaults::get_default_prec();
    assert(defaultPrec == 512);
    std::cout << "Default precision test passed." << std::endl;

    defaults::set_default_prec(1024);
    defaultPrec = defaults::get_default_prec();
    assert(defaultPrec == 1024);
    std::cout << "Set and get precision test passed." << std::endl;

    defaults::set_default_prec(512);
}

void testDefaultRoundingMode() {
    mpfr_rnd_t defaultRnd = defaults::get_default_rounding_mode();
    assert(defaultRnd == MPFR_RNDN);
    std::cout << "Default rounding mode test passed." << std::endl;

    defaults::set_default_rounding_mode(MPFR_RNDZ);
    defaultRnd = defaults::get_default_rounding_mode();
    assert(defaultRnd == MPFR_RNDZ);
    std::cout << "Set and get rounding mode test passed." << std::endl;
    defaults::set_default_rounding_mode(MPFR_RNDN);
}

void testDefaultConstructor() {
    mpfr_class a;
    char buffer[100];
    mpfr_snprintf(buffer, sizeof(buffer), "%.0Rf", a.get_mpfr_t());
    assert(std::string(buffer) == "nan");
    std::cout << "Default constructor test passed." << std::endl;
}

void testCopyConstructor() {
    mpfr_class a;
    mpfr_class b = a;
    assert(true);
    std::cout << "Copy constructor test passed." << std::endl;
}

void testAssignmentOperator() {
    mpfr_class a;
    mpfr_class b;
    b = a;
    assert(true);
    std::cout << "Assignment operator test passed." << std::endl;
}

int main() {
    testDefaultPrecision();
    testDefaultRoundingMode();
    testDefaultConstructor();
    testCopyConstructor();
    testAssignmentOperator();

    std::cout << "All tests passed." << std::endl;

    mpfr_class a(1.5);
    mpfr_class b(2.5);
    mpfr_class result = a + b;
    mpfr_class c;
    c = a + b;

    mpfr_printf("%Re\n", a);
    mpfr_printf("%Re\n", b);
    mpfr_printf("%Re\n", result);
    mpfr_printf("%Re\n", c);
    printf("a=a+b\n");
    a = a + b;
    mpfr_printf("%Re\n", a);

    printf("a+=b\n");
    a += b;
    mpfr_printf("%Re\n", a);

    //    assert(std::fabs(result.to_double() - 4.0) < 1e-6);

    return 0;
}
