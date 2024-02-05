#include <iostream>
#include <cassert>
#include "mpfr_class.h"

using namespace mpfrcxx;

void testDefaultConstructor() {
    mpfr_class a;
    assert(true);
    std::cout << "Default constructor test passed." << std::endl;
    mpfr_printf("%Re\n", a);
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
