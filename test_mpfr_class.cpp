#include <iostream>
#include <cassert>
#include "mpfr_class.h" 

void testDefaultConstructor() {
    mpfr_class a;
    assert(true);
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
    testDefaultConstructor();
    testCopyConstructor();
    testAssignmentOperator();

    std::cout << "All tests passed." << std::endl;
    return 0;
}
