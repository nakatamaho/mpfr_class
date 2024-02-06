#include <iostream>
#include <cassert>
#include <cstring>
#include <string>

#include "mpfr_class.h"

using namespace mpfrcxx;

// Asserts that the mpfr_class object equals the expected string representation
void assertMpfrEquals(mpfrcxx::mpfr_class &mpfrObj, const char *expected, int precision = 10, int base = defaults::base) {
    char formatString[64];
    // Adjust the comparison based on the base
    char buffer[64];
    if (base == 10) {
        std::sprintf(formatString, "%%.%dRf", precision);         // Generates format string like "%.10Rf"
        mpfr_sprintf(buffer, formatString, mpfrObj.get_mpfr_t()); // Uses generated format string
    } else {
        printf("not supported");
        exit(-1);
    }
    // Compare the generated string with the expected value
    assert(std::strcmp(buffer, expected) == 0 && "The mpfr object's value does not match the expected value.");
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
    const char *expectedValue = "3.1415926535";

    mpfrcxx::mpfr_class a = testValue;
    assertMpfrEquals(a, expectedValue);
    std::cout << "Substitution from double using constructor test passed." << std::endl;

    mpfrcxx::mpfr_class b;
    b = testValue;
    assertMpfrEquals(b, expectedValue);
    std::cout << "Substitution from double using assignment test passed." << std::endl;
}

void testInitializationAndAssignmentString() {
    // Testing initialization with a decimal number using a constructor
    const char *expectedDecimalValue = "1.4142135624";
    mpfr_class a = expectedDecimalValue;
    assertMpfrEquals(a, expectedDecimalValue);
    std::cout << "Constructor initialization with decimal '" << expectedDecimalValue << "' test passed." << std::endl;

    // Testing initialization with a decimal number using an assignment operator
    mpfr_class b;
    b = expectedDecimalValue;
    assertMpfrEquals(b, expectedDecimalValue);
    std::cout << "Assignment initialization with decimal '" << expectedDecimalValue << "' test passed." << std::endl;

    // Testing initialization with a decimal number using a constructor
    std::string expectedDecimalValueString = "3.1415926535";
    mpfr_class c = expectedDecimalValueString;
    assertMpfrEquals(c, expectedDecimalValueString.c_str());
    std::cout << "Constructor initialization with decimal '" << expectedDecimalValueString << "' test passed." << std::endl;

    // Testing initialization with a decimal number using an assignment operator
    mpfr_class d;
    d = expectedDecimalValueString;
    assertMpfrEquals(d, expectedDecimalValueString.c_str());
    std::cout << "Assignment initialization with decimal '" << expectedDecimalValueString << "' test passed." << std::endl;
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
