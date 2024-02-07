#include <iostream>
#include <cassert>
#include <cstring>
#include <string>

#include "mpfr_class.h"

using namespace mpfrcxx;

// Asserts that the mpfr_class object equals the expected string representation
void assertMpfrEquals(mpfrcxx::mpfr_class &mpfrObj, const char *expected, int base = defaults::base, int precision = 10) {
    char formatString[64];
    // Adjust the comparison based on the base
    char buffer[64];
    switch (base) {
    case 10:
        std::sprintf(formatString, "%%.%dRf", precision);         // Generates format string like "%.10Rf"
        mpfr_sprintf(buffer, formatString, mpfrObj.get_mpfr_t()); // Uses generated format string
        break;

    case 16:
        std::sprintf(formatString, "%%.%dRa", precision);         // Generates format string like "%.10Rf"
        mpfr_sprintf(buffer, formatString, mpfrObj.get_mpfr_t()); // Uses generated format string
        break;

    default:
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

    // Testing initialization with a hexadecimal number using an assignment operator
    const char *expectedHexValue = "0x3.243f6a8885a3p+0";
    mpfr_class e(expectedHexValue, 16);
    assertMpfrEquals(e, expectedHexValue, 16, 12);
    std::cout << "Assignment initialization with hexadecimal '" << expectedHexValue << "' test passed." << std::endl;

    defaults::base = 16;
    // Testing initialization with a hexadecimal number using a constructor
    mpfr_class f;
    e = expectedHexValue;
    assertMpfrEquals(e, expectedHexValue, defaults::base, 12);
    std::cout << "Constructor initialization with hexadecimal '" << expectedHexValue << "' test passed." << std::endl;
    defaults::base = 10;
}

// Function to test equality of two mpfr_class instances with the same value
void testEqualitySameValue() {
    mpfr_class a, b;
    a = "3.14";     // Set value of a
    b = "3.14";     // Set value of b to the same as a
    assert(a == b); // Should be true
    std::cout << "Test equality with the same value passed." << std::endl;
}

// Function to test equality of two mpfr_class instances with different values
void testEqualityDifferentValue() {
    mpfr_class a, c;
    a = "3.14";        // Set value of a
    c = "2.17";        // Set value of c to a different value
    assert(!(a == c)); // Should be false
    std::cout << "Test equality with different values passed." << std::endl;
}

void testSqrt() {
    // Test Case 1: Calculate the square root of a positive number
    mpfr_class a;
    a = "4.0"; // Square root of 4.0 is 2.0
    mpfr_class result = mpfr_class::sqrt(a);
    std::string expected = "2.0000000000";
    assertMpfrEquals(result, expected.c_str());

    // Test Case 2: Calculate the square root of 0
    mpfr_class b("0.0"); // Square root of 0.0 is 0.0
    result = mpfr_class::sqrt(b);
    expected = "0.0000000000";
    assertMpfrEquals(result, expected.c_str());

    // Test Case 3: Calculate the square root of a negative number (should raise an error)
    mpfr_class c("-1.0");
    result = mpfr_class::sqrt(c);
    assert(result.is_nan()); // Check if the result is NaN
    std::cout << "Test square root of a negative number (should be NaN) passed." << std::endl;
}

// Test function for set_prec and get_prec
void testSetAndGetPrec() {
    mpfr_class a; // Default precision
    mpfr_prec_t defaultPrec = a.get_prec();
    std::cout << "Default precision: " << defaultPrec << " bits" << std::endl;

    mpfr_prec_t newPrec = 128; // New precision to set
    a.set_prec(newPrec);
    mpfr_prec_t retrievedPrec = a.get_prec();
    std::cout << "New precision: " << retrievedPrec << " bits" << std::endl;

    // Assert that the new precision is correctly set and retrieved
    assert(retrievedPrec == newPrec);
    std::cout << "Test passed: Precision was successfully set and retrieved." << std::endl;
}
void testLog() {
    mpfr_class a("1.0");
    mpfr_class result = mpfr_class::log(a);
    // log(1) = 0
    std::string expected = "0.0000000000";
    assertMpfrEquals(result, expected.c_str());
    std::cout << "Log test passed." << std::endl;
}

void testLog10() {
    mpfr_class a("10.0");
    mpfr_class result = mpfr_class::log10(a);
    // log10(10) = 1
    std::string expected = "1.0000000000";
    assertMpfrEquals(result, expected.c_str());
    std::cout << "Log10 test passed." << std::endl;
}

void testLog2() {
    mpfr_class a("2.0");
    mpfr_class result = mpfr_class::log2(a);
    // log2(2) = 1
    std::string expected = "1.0000000000";
    assertMpfrEquals(result, expected.c_str());
    std::cout << "Log2 test passed." << std::endl;
}

int main() {
    testDefaultPrecision();
    testDefaultRoundingMode();
    testDefaultConstructor();
    testCopyConstructor();
    testAssignmentOperator();
    testInitializationAndAssignmentDouble();
    testInitializationAndAssignmentString();
    testEqualitySameValue();
    testEqualityDifferentValue();
    testSetAndGetPrec();
    testSqrt();
    testLog();
    testLog10();
    testLog2();

    std::cout << "All tests passed." << std::endl;

    return 0;
}
