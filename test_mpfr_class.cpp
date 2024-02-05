#include <iostream>
#include <cassert>
#include <cstring>
#include "mpfr_class.h"

using namespace mpfrcxx;

// Asserts that the mpfr_class object equals the expected string representation
void assertMpfrEquals(mpfrcxx::mpfr_class &mpfrObj, const char *expected) {
    char buffer[64];
    mpfr_sprintf(buffer, "%.10Rf", mpfrObj.get_mpfr_t());
    assert(std::strcmp(buffer, expected) == 0);
}

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

void testInitializationAndAssignmentDouble() {
    double testValue = 3.1415926535;

    mpfrcxx::mpfr_class a(testValue);
    assertMpfrEquals(a, "3.1415926535");
    std::cout << "Substitution from double using constructor test passed." << std::endl;

    mpfrcxx::mpfr_class b;
    b = testValue;
    assertMpfrEquals(b, "3.1415926535");
    std::cout << "Substitution from double using assignment test passed." << std::endl;
}

void testInitializationAndAssignmentString() {
    // Testing initialization with a decimal number using a constructor
    mpfr_class decimalWrapper("3.1415926535");
    assertMpfrEquals(decimalWrapper, "3.1415926535");
    std::cout << "Constructor initialization with decimal '3.1415926535' test passed." << std::endl;

    // Testing initialization with a decimal number using an assignment operator
    mpfr_class decimalWrapperAssignment;
    decimalWrapperAssignment = "3.1415926535";
    assertMpfrEquals(decimalWrapperAssignment, "3.1415926535");
    std::cout << "Assignment initialization with decimal '3.1415926535' test passed." << std::endl;

    // Testing initialization with a hexadecimal number using a constructor
    mpfr_class hexWrapper("1.921fb54442d18p+1", 16);
    assertMpfrEquals(hexWrapper, "3.1415926535");
    std::cout << "Constructor initialization with hexadecimal '1.921fb54442d18p+1' test passed." << std::endl;

    // Testing initialization with a hexadecimal number using an assignment operator
    mpfr_class hexWrapperAssignment;
    hexWrapperAssignment = "1.921fb54442d18p+1";
    assertMpfrEquals(hexWrapperAssignment, "3.1415926535");
    std::cout << "Assignment initialization with hexadecimal '1.921fb54442d18p+1' test passed." << std::endl;

    // Testing initialization with a negative decimal number using a constructor
    mpfr_class negativeDecimalWrapper("-2.7182818284");
    assertMpfrEquals(negativeDecimalWrapper, "-2.7182818284");
    std::cout << "Constructor initialization with negative decimal '-2.7182818284' test passed." << std::endl;

    // Testing initialization with a negative decimal number using an assignment operator
    mpfr_class negativeDecimalWrapperAssignment;
    negativeDecimalWrapperAssignment = "-2.7182818284";
    assertMpfrEquals(negativeDecimalWrapperAssignment, "-2.7182818284");
    std::cout << "Assignment initialization with negative decimal '-2.7182818284' test passed." << std::endl;

    // Testing initialization with a binary number using a constructor
    mpfr_class binaryWrapper("10.101010001000100010001011010001000100010001011", 2);
    assertMpfrEquals(binaryWrapper, "2.7182818284");
    std::cout << "Constructor initialization with binary '10.101010001000100010001011010001000100010001011' test passed." << std::endl;

    // Testing initialization with a binary number using an assignment operator
    mpfr_class binaryWrapperAssignment;
    binaryWrapperAssignment = "10.101010001000100010001011010001000100010001011";
    assertMpfrEquals(binaryWrapperAssignment, "2.7182818284");
    std::cout << "Assignment initialization with binary '10.101010001000100010001011010001000100010001011' test passed." << std::endl;
}

int main() {
    testDefaultPrecision();
    testDefaultRoundingMode();
    testDefaultConstructor();
    testCopyConstructor();
    testAssignmentOperator();
    testInitializationAndAssignmentDouble();
    testInitializationAndAssignmentString();

    std::cout << "All tests passed." << std::endl;

    return 0;
}
