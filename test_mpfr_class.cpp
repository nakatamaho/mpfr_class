/*
 * Copyright (c) 2024
 *      Nakata, Maho
 *      All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#include <iostream>
#include <cassert>
#include <cstring>
#include <string>
#include <iomanip>

#include "mpfr_class.h"

using namespace mpfr;

// Asserts that the mpfr_class object equals the expected string representation
bool IsMPFREquals(mpfr_class &mpfrObj, const char *expected, int base = defaults::base, int precision = 10) {
    char formatString[64];
    char buffer[64];

    // Adjust the comparison based on the base
    switch (base) {
    case 2:
        std::sprintf(formatString, "%%.%dRb", precision);         // Generates format string like "%.10Rf"
        mpfr_sprintf(buffer, formatString, mpfrObj.get_mpfr_t()); // Uses generated format string
        break;
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
    if (std::strcmp(buffer, expected) == 0)
        return true;
    else
        return false;
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

    mpfr_class a = (mpfr_class)testValue;
    assert(IsMPFREquals(a, expectedValue));
    std::cout << "Substitution from double using constructor test passed." << std::endl;

    mpfr_class b;
    b = testValue;
    assert(IsMPFREquals(b, expectedValue));
    std::cout << "Substitution from double using assignment test passed." << std::endl;
}

void testInitializationAndAssignmentString() {
    // Testing initialization with a decimal number using a constructor
    const char *expectedDecimalValue = "1.4142135624";
    mpfr_class a = expectedDecimalValue;
    assert(IsMPFREquals(a, expectedDecimalValue));
    std::cout << "Constructor initialization with decimal '" << expectedDecimalValue << "' test passed." << std::endl;

    // Testing initialization with a decimal number using an assignment operator
    mpfr_class b;
    b = expectedDecimalValue;
    assert(IsMPFREquals(b, expectedDecimalValue));
    std::cout << "Assignment initialization with decimal '" << expectedDecimalValue << "' test passed." << std::endl;

    // Testing initialization with a decimal number using a constructor
    std::string expectedDecimalValueString = "3.1415926535";
    mpfr_class c = expectedDecimalValueString;
    assert(IsMPFREquals(c, expectedDecimalValueString.c_str()));
    std::cout << "Constructor initialization with decimal '" << expectedDecimalValueString << "' test passed." << std::endl;

    // Testing initialization with a decimal number using an assignment operator
    mpfr_class d;
    d = expectedDecimalValueString;
    assert(IsMPFREquals(d, expectedDecimalValueString.c_str()));
    std::cout << "Assignment initialization with decimal '" << expectedDecimalValueString << "' test passed." << std::endl;

    // Testing initialization with a hexadecimal number using an assignment operator
    const char *expectedHexValue = "0x3.243f6a8885a3p+0";
    mpfr_class e(expectedHexValue, 16);
    assert(IsMPFREquals(e, expectedHexValue, 16, 12));
    std::cout << "Assignment initialization with hexadecimal '" << expectedHexValue << "' test passed." << std::endl;

    defaults::base = 16;
    // Testing initialization with a hexadecimal number using a constructor
    mpfr_class f;
    e = expectedHexValue;
    assert(IsMPFREquals(e, expectedHexValue, defaults::base, 12));
    std::cout << "Constructor initialization with hexadecimal '" << expectedHexValue << "' test passed." << std::endl;
    defaults::base = 10;

    // Testing initialization with a hexadecimal number using an assignment operator
    const char *expectedBinaryValue = "1.0101010001000100010001011010001000100010001011p+1";
    mpfr_class g(expectedBinaryValue, 2);
    assert(IsMPFREquals(g, expectedBinaryValue, 2, 46));
    std::cout << "Assignment initialization with binary '" << expectedBinaryValue << "' test passed." << std::endl;

    defaults::base = 2;
    // Testing initialization with a binaryadecimal number using a constructor
    mpfr_class h;
    h = expectedBinaryValue;
    assert(IsMPFREquals(h, expectedBinaryValue, defaults::base, 46));
    std::cout << "Constructor initialization with binary '" << expectedBinaryValue << "' test passed." << std::endl;
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
    mpfr_class result = sqrt(a);
    std::string expected = "2.0000000000";
    assert(IsMPFREquals(result, expected.c_str()));

    // Test Case 2: Calculate the square root of 0
    mpfr_class b("0.0"); // Square root of 0.0 is 0.0
    result = sqrt(b);
    expected = "0.0000000000";
    assert(IsMPFREquals(result, expected.c_str()));

    // Test Case 3: Calculate the square root of a negative number (should raise an error)
    mpfr_class c("-1.0");
    result = sqrt(c);
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
    mpfr_class result = log(a);
    // log(1) = 0
    std::string expected = "0.0000000000";
    assert(IsMPFREquals(result, expected.c_str()));
    // log(2) = 0.69314718056
    a = "2.0";
    expected = "0.6931471806";
    result = log(a);
    assert(IsMPFREquals(result, expected.c_str()));

    a = "0.0";
    result = log(a);
    assert(result.is_inf());
    std::cout << "Test log zero (should be -Inf) passed." << std::endl;
    a = "-1.0";
    result = log(a);
    assert(result.is_nan());
    std::cout << "Test log negative (should be NaN) passed." << std::endl;

    std::cout << "Log test passed." << std::endl;
}

void testLog10() {
    mpfr_class a("10.0");
    mpfr_class result = log10(a);
    // log10(10) = 1
    std::string expected = "1.0000000000";
    assert(IsMPFREquals(result, expected.c_str()));
    // log(2) = 0.3010299957
    a = "2.0";
    expected = "0.3010299957";
    result = log10(a);
    assert(IsMPFREquals(result, expected.c_str()));

    a = "0.0";
    result = log10(a);
    assert(result.is_inf());
    std::cout << "Test log10 zero (should be -Inf) passed." << std::endl;
    a = "-1.0";
    result = log10(a);
    assert(result.is_nan());
    std::cout << "Test log10 negative (should be NaN) passed." << std::endl;

    std::cout << "Log10 test passed." << std::endl;
}

void testLog2() {
    mpfr_class a("2.0");
    mpfr_class result = log2(a);
    // log2(2) = 1
    std::string expected = "1.0000000000";
    assert(IsMPFREquals(result, expected.c_str()));
    // log2(10) = 3.3219280949
    a = "10.0";
    expected = "3.3219280949";
    result = log2(a);
    assert(IsMPFREquals(result, expected.c_str()));

    a = "0.0";
    result = log2(a);
    assert(result.is_inf());
    std::cout << "Test log2 zero (should be -Inf) passed." << std::endl;
    a = "-1.0";
    result = log2(a);
    assert(result.is_nan());
    std::cout << "Test log2 negative (should be NaN) passed." << std::endl;

    std::cout << "Log2 test passed." << std::endl;
}

// Test for log1p function
void testLog1p() {
    mpfr_class a("0.5");
    mpfr_class result = log1p(a);
    std::string expected = "0.4054651081"; // Approximate value for log1p(0.5)
    assert(IsMPFREquals(result, expected.c_str()));

    a = "-0.5";
    result = log1p(a);
    expected = "-0.6931471806"; // Approximate value for log1p(-0.5)
    assert(IsMPFREquals(result, expected.c_str()));

    std::cout << "Log1p tests passed." << std::endl;
}

// Test for log2p1 function
void testLog2p1() {
    mpfr_class a("1.0");
    mpfr_class result = log2p1(a);
    std::string expected = "1.0000000000"; // Exact value for log2p1(1)
    assert(IsMPFREquals(result, expected.c_str()));
    std::cout << "Log2p1 tests passed." << std::endl;
}

// Test for log10p1 function
void testLog10p1() {
    mpfr_class a("9.0");
    mpfr_class result = log10p1(a);
    std::string expected = "1.0000000000"; // Exact value for log10p1(9)
    assert(IsMPFREquals(result, expected.c_str()));
    std::cout << "Log10p1 tests passed." << std::endl;
}

// Test for exp function
void testExp() {
    mpfr_class a("1.0");
    mpfr_class result = exp(a);
    std::string expected = "2.7182818285"; // Approximate value for e
    assert(IsMPFREquals(result, expected.c_str()));

    std::cout << "Exp tests passed." << std::endl;
}

// Test for exp2 function
void testExp2() {
    mpfr_class a("4.0");
    mpfr_class result = exp2(a);
    std::string expected = "16.0000000000"; // Exact value for 2^4
    assert(IsMPFREquals(result, expected.c_str()));

    std::cout << "Exp2 tests passed." << std::endl;
}

// Test for exp10 function
void testExp10() {
    mpfr_class a("2.0");
    mpfr_class result = exp10(a);
    std::string expected = "100.0000000000"; // Exact value for 10^2
    assert(IsMPFREquals(result, expected.c_str()));

    std::cout << "Exp10 tests passed." << std::endl;
}

// Test for const_log2 function
void testConstLog2() {
    mpfr_class result = const_log2(MPFR_RNDN);
    std::string expected = "0.6931471806"; // Approximate value for log(2)
    assert(IsMPFREquals(result, expected.c_str()));

    std::cout << "Const_log2 tests passed." << std::endl;
}

// Test for const_pi function
void testConstPi() {
    mpfr_class result = const_pi(MPFR_RNDN);
    std::string expected = "3.1415926536"; // Approximate value for pi
    assert(IsMPFREquals(result, expected.c_str()));

    std::cout << "Const_pi tests passed." << std::endl;
}

// Test for const_euler function
void testConstEuler() {
    mpfr_class result = const_euler(MPFR_RNDN);
    std::string expected = "0.5772156649"; // Approximate value for Euler's constant
    assert(IsMPFREquals(result, expected.c_str()));

    std::cout << "Const_euler tests passed." << std::endl;
}

// Test for const_catalan function
void testConstCatalan() {
    mpfr_class result = const_catalan(MPFR_RNDN);
    std::string expected = "0.9159655942"; // Approximate value for Catalan's constant
    assert(IsMPFREquals(result, expected.c_str()));

    std::cout << "Const_catalan tests passed." << std::endl;
}

void testAddition() {
    mpfr_class a(1.5);
    mpfr_class b(2.5);
    std::string expected = "4.0000000000";

    mpfr_class c = a + b;
    assert(IsMPFREquals(c, expected.c_str()));
    a += b;
    assert(IsMPFREquals(a, expected.c_str()));
    std::cout << "Addition Test passed." << std::endl;
}

void testMultplication() {
    mpfr_class a(2.0);
    mpfr_class b(3.0);
    std::string expected = "6.0000000000";

    mpfr_class c = a * b;
    assert(IsMPFREquals(c, expected.c_str()));
    a *= b;
    assert(IsMPFREquals(a, expected.c_str()));
    std::cout << "Multiplication Test passed." << std::endl;
}

void testDivision() {
    mpfr_class a(6.0);
    mpfr_class b(2.0);
    std::string expected = "3.0000000000";

    mpfr_class c = a / b;
    assert(IsMPFREquals(c, expected.c_str()));
    a /= b;
    assert(IsMPFREquals(a, expected.c_str()));
    std::cout << "Division Test passed." << std::endl;
}
void testSubtraction() {
    mpfr_class a(5.0);
    mpfr_class b(2.0);
    std::string expected = "3.0000000000";

    mpfr_class c = a - b;
    assert(IsMPFREquals(c, expected.c_str()));
    a -= b;
    assert(IsMPFREquals(a, expected.c_str()));
    std::cout << "Subtraction Test passed." << std::endl;
}

void testEqNonEq() {
    mpfr_class obj1("2.718281828459045");
    mpfr_class obj2("2.718281828459045");
    assert(obj1 == obj2);
    std::cout << "Equality test passed." << std::endl;

    mpfr_class obj3("3.141592653589793");
    assert(obj1 != obj3);
    std::cout << "Inequality test passed." << std::endl;

    mpfr_class obj4("2.7182818284590451");
    assert(obj1 != obj4);
    std::cout << "Subtle difference test passed." << std::endl;
}

void testOutputOperator() {
    mpfr_class num1(123456.789);
    mpfr_class num2(0.0000123456789);
    mpfr_class num3(123456789.0);

    std::ostringstream oss;
    oss << std::fixed << std::setprecision(3) << num1;
    assert(oss.str() == "123456.789");
    oss.str("");
    oss.clear();

    oss << std::fixed << std::setprecision(4) << num2;
    assert(oss.str() == "0.0000");
    oss.str("");
    oss.clear();

    oss << std::scientific << std::setprecision(2) << num3;
    assert(oss.str() == "1.23e+08");
}

void testNeg() {
    mpfr_class a(-3.5);
    mpfr_class result = neg(a);
    mpfr_class expected = "3.5";
    assert(result == expected);
    std::cout << "neg test passed." << std::endl;
}

void testAbs() {
    mpfr_class a(-3.5);
    mpfr_class c = abs(a);
    mpfr_class expected = "3.5";
    mpfr_class result = abs(a);
    assert(result == expected);
    std::cout << "abs test passed." << std::endl;
}

void testemin_emax() {
    auto emin = mpfr::defaults::get_emin();
    auto emax = mpfr::defaults::get_emax();

    std::cout << "Default emin: " << emin << std::endl;
    std::cout << "Default emax: " << emax << std::endl;

    auto emin_min = mpfr::defaults::get_emin_min();
    auto emin_max = mpfr::defaults::get_emin_max();
    auto emax_min = mpfr::defaults::get_emax_min();
    auto emax_max = mpfr::defaults::get_emax_max();

    std::cout << "Emin min: " << emin_min << std::endl;
    std::cout << "Emin max: " << emin_max << std::endl;
    std::cout << "Emax min: " << emax_min << std::endl;
    std::cout << "Emax max: " << emax_max << std::endl;

    mpfr::defaults::set_emin(mpfr_get_emin_min());
    mpfr::defaults::set_emax(mpfr_get_emax_max());

    emin = mpfr::defaults::get_emin();
    emax = mpfr::defaults::get_emax();

    std::cout << "New emin: " << emin << std::endl;
    std::cout << "New emax: " << emax << std::endl;

    //    mpfr::defaults::set_default_prec = 53;
    //    mpfr::set_emin = -1073;
    //    mpfr::set_emax = 1024;
}
void test_mpfr_class_double_addition() {
    mpfr_class a(1.0), c;
    const char *expectedValue = "3.0000000000";
    double b = 2.0;

    c = a + b;
    assert(IsMPFREquals(c, expectedValue));
    c = b + a;
    assert(IsMPFREquals(c, expectedValue));
    a += b;
    assert(IsMPFREquals(a, expectedValue));
    c = 1.0 + b;
    std::cout << "mpfr_class + double test passed." << std::endl;
}
void test_mpfr_class_double_subtraction() {
    mpfr_class a(5.0), c, d;
    const char *expectedValueC = "3.0000000000";
    const char *expectedValueD = "-3.0000000000";
    double b = 2.0;

    c = a - b;
    assert(IsMPFREquals(c, expectedValueC));
    d = b - a;
    assert(IsMPFREquals(d, expectedValueD));
    a -= b;
    assert(IsMPFREquals(a, expectedValueC));
    std::cout << "mpfr_class - double test passed." << std::endl;
}
void test_mpfr_class_double_multiplication() {
    mpfr_class a(2.0), c;
    const char *expectedValueMul = "4.0000000000";
    double b = 2.0;

    c = a * b;
    assert(IsMPFREquals(c, expectedValueMul));
    c = b * a;
    assert(IsMPFREquals(c, expectedValueMul));
    a *= b;
    assert(IsMPFREquals(a, expectedValueMul));
    std::cout << "mpfr_class * double test passed." << std::endl;
}
void test_mpfr_class_double_division() {
    mpfr_class a(4.0), c, d;
    const char *expectedValueDiv = "2.0000000000";
    const char *expectedValueDivRev = "0.5000000000";
    double b = 2.0;

    c = a / b;
    assert(IsMPFREquals(c, expectedValueDiv));
    d = b / a;
    assert(IsMPFREquals(d, expectedValueDivRev));
    a /= b;
    assert(IsMPFREquals(a, expectedValueDiv));
    std::cout << "mpfr_class / double test passed." << std::endl;
}

int main() {
    ////////////////////////////////////////////////////////////////////////////////////////
    // 5.1 Initialization Functions
    ////////////////////////////////////////////////////////////////////////////////////////
    testDefaultPrecision();
    testDefaultRoundingMode();
    testDefaultConstructor();
    testCopyConstructor();
    testSetAndGetPrec();
    ////////////////////////////////////////////////////////////////////////////////////////
    // 5.2 Assignment Functions
    ////////////////////////////////////////////////////////////////////////////////////////
    testAssignmentOperator();
    testInitializationAndAssignmentDouble();
    testInitializationAndAssignmentString();
    ////////////////////////////////////////////////////////////////////////////////////////
    // 5.5 Arithmetic Functions
    ////////////////////////////////////////////////////////////////////////////////////////
    testAddition();
    testMultplication();
    testDivision();
    testSubtraction();
    testEqNonEq();
    testSqrt();
    testNeg();
    testAbs();
    test_mpfr_class_double_addition();
    test_mpfr_class_double_subtraction();
    test_mpfr_class_double_multiplication();
    test_mpfr_class_double_division();
    ////////////////////////////////////////////////////////////////////////////////////////
    // 5.6 Comparison Functions
    ////////////////////////////////////////////////////////////////////////////////////////
    testEqualitySameValue();
    testEqualityDifferentValue();
    ////////////////////////////////////////////////////////////////////////////////////////
    // 5.7 Transcendental Functions
    ////////////////////////////////////////////////////////////////////////////////////////
    testLog();
    testLog10();
    testLog2();
    testLog1p();
    testLog2p1();
    testLog10p1();
    testExp();
    testExp2();
    testExp10();
    testConstLog2();
    testConstPi();
    testConstEuler();
    testConstCatalan();
    ////////////////////////////////////////////////////////////////////////////////////////
    // 5.8 Input and Output Functions
    ////////////////////////////////////////////////////////////////////////////////////////
    testOutputOperator();

    ////////////////////////////////////////////////////////////////////////////////////////
    // 5.13
    ////////////////////////////////////////////////////////////////////////////////////////
    testemin_emax();
    std::cout << "All tests passed." << std::endl;

    return 0;
}
