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

#if __cplusplus < 201703L
#error "This class only runs on C++ 17 and later"
#endif

#define MPFR_WANT_FLOAT128

#include <mpfr.h>
#include <iostream>
#include <utility>
#include <limits>

#define ___MPFR_CLASS_EXPLICIT___ explicit

namespace mpfr {

class defaults {
  public:
    static mpfr_prec_t prec;
    static mpfr_rnd_t rnd;
    static int base;
    static mpfr_exp_t emin;
    static mpfr_exp_t emax;

    ////////////////////////////////////////////////////////////////////////////////////////
    // 5.1 Initialization Functions (part II)
    ////////////////////////////////////////////////////////////////////////////////////////
    static inline mpfr_prec_t get_default_prec() { return mpfr_get_default_prec(); }
    static inline void set_default_prec(const mpfr_prec_t prec) { mpfr_set_default_prec(prec); }
    static inline mpfr_prec_t get_default_base() { return base; }
    static inline void set_default_base(const int _base) { base = _base; }
    ////////////////////////////////////////////////////////////////////////////////////////
    // 5.11 Rounding-Related Functions (part II)
    ////////////////////////////////////////////////////////////////////////////////////////
    static inline mpfr_rnd_t get_default_rounding_mode() { return mpfr_get_default_rounding_mode(); }
    static inline void set_default_rounding_mode(const mpfr_rnd_t r = MPFR_RNDN) { mpfr_set_default_rounding_mode(r); }
    ////////////////////////////////////////////////////////////////////////////////////////
    // 5.13 Exception Related Functions (part II)
    ////////////////////////////////////////////////////////////////////////////////////////
    static inline mpfr_exp_t get_emin() { return mpfr_get_emin(); }
    static inline mpfr_exp_t get_emax() { return mpfr_get_emax(); }
    static inline int set_emin(const mpfr_exp_t exp) { return mpfr_set_emin(exp); }
    static inline int set_emax(const mpfr_exp_t exp) { return mpfr_set_emax(exp); }
    static inline mpfr_exp_t get_emin_min(void) { return mpfr_get_emin_min(); }
    static inline mpfr_exp_t get_emin_max(void) { return mpfr_get_emin_max(); }
    static inline mpfr_exp_t get_emax_min(void) { return mpfr_get_emax_min(); }
    static inline mpfr_exp_t get_emax_max(void) { return mpfr_get_emax_max(); }
};

class mpfr_class {
  public:
    ////////////////////////////////////////////////////////////////////////////////////////
    // 5.1 Initialization Functions (part I)
    ////////////////////////////////////////////////////////////////////////////////////////
    mpfr_class() { mpfr_init(value); }
    ~mpfr_class() { mpfr_clear(value); }
    void set_prec(const mpfr_prec_t prec) { mpfr_set_prec(value, prec); }
    mpfr_prec_t get_prec() const { return mpfr_get_prec(value); }
    ////////////////////////////////////////////////////////////////////////////////////////
    // 5.2 Assignment Functions
    ////////////////////////////////////////////////////////////////////////////////////////
    mpfr_class(mpfr_class &&op) noexcept { mpfr_swap(value, op.value); }
    mpfr_class(const mpfr_class &op) {
        mpfr_init2(value, mpfr_get_prec(op.value));
        mpfr_set(value, op.value, defaults::rnd);
    }
    ___MPFR_CLASS_EXPLICIT___ mpfr_class(const mpfr_t &op) {
        mpfr_prec_t _prec;
        _prec = mpfr_get_prec(op);
        mpfr_init2(value, _prec);
        mpfr_set(value, op, defaults::rnd);
    }
    ___MPFR_CLASS_EXPLICIT___ mpfr_class(const unsigned int op) noexcept {
        mpfr_init(value);
        mpfr_set_ui(value, (unsigned long int)op, defaults::rnd);
    }
    ___MPFR_CLASS_EXPLICIT___ mpfr_class(const int op) noexcept {
        mpfr_init(value);
        mpfr_set_si(value, (long int)op, defaults::rnd);
    }
    ___MPFR_CLASS_EXPLICIT___ mpfr_class(const unsigned long int op) noexcept {
        mpfr_init(value);
        mpfr_set_ui(value, op, defaults::rnd);
    }
    ___MPFR_CLASS_EXPLICIT___ mpfr_class(const long int op) noexcept {
        mpfr_init(value);
        mpfr_set_si(value, op, defaults::rnd);
    }
    //    ___MPFR_CLASS_EXPLICIT___ mpfr_class(const uintmax_t op) noexcept {
    //        mpfr_init(value);
    //        mpfr_set_uj(value, op, defaults::rnd);
    //    }
    //    ___MPFR_CLASS_EXPLICIT___ mpfr_class(const intmax_t op) noexcept {
    //        mpfr_init(value);
    //        mpfr_set_sj(value, op, defaults::rnd);
    //    }
    ___MPFR_CLASS_EXPLICIT___ mpfr_class(const float op) noexcept {
        mpfr_init(value);
        mpfr_set_flt(value, op, defaults::rnd);
    }
    ___MPFR_CLASS_EXPLICIT___ mpfr_class(const double op) noexcept {
        mpfr_init(value);
        mpfr_set_d(value, op, defaults::rnd);
    }
    ___MPFR_CLASS_EXPLICIT___ mpfr_class(const long double op) noexcept {
        mpfr_init(value);
        mpfr_set_ld(value, op, defaults::rnd);
    }
    //    ___MPFR_CLASS_EXPLICIT___ mpfr_class(_Float128 op) noexcept {
    //        mpfr_init(value);
    //        mpfr_set_float128(value, op, defaults::rnd);
    //    }
    ___MPFR_CLASS_EXPLICIT___ mpfr_class(const mpz_t op) noexcept {
        mpfr_init(value);
        mpfr_set_z(value, op, defaults::rnd);
    }
    ___MPFR_CLASS_EXPLICIT___ mpfr_class(const mpq_t op) noexcept {
        mpfr_init(value);
        mpfr_set_q(value, op, defaults::rnd);
    }
    ___MPFR_CLASS_EXPLICIT___ mpfr_class(const mpf_t op) noexcept {
        mpfr_init(value);
        mpfr_set_f(value, op, defaults::rnd);
    }
    mpfr_class(const char *s, int base = defaults::base, mpfr_rnd_t rnd = defaults::rnd) {
        mpfr_init(value);
        if (mpfr_set_str(value, s, base, rnd) != 0) {
            std::cerr << "Error initializing mpfr_t from const char*: " << s << std::endl;
            throw std::runtime_error("Failed to initialize mpfr_t with given string.");
        }
    }
    mpfr_class(const std::string &s, int base = defaults::base, mpfr_rnd_t rnd = defaults::rnd) {
        mpfr_init(value);
        if (mpfr_set_str(value, s.c_str(), base, rnd) != 0) {
            std::cerr << "Error initializing mpfr_t from std::string: " << s << std::endl;
            throw std::runtime_error("Failed to initialize mpfr_t with given string.");
        }
    }
    // Initialization using assignment operator
    mpfr_class &operator=(mpfr_class op) noexcept { // Copy-and-Swap Idiom; it does both the copy assignment and the move assignment.
        mpfr_swap(value, op.value);
        return *this;
    }
    mpfr_class &operator=(double op) noexcept {
        mpfr_set_d(value, op, defaults::rnd);
        return *this;
    }
    mpfr_class &operator=(const char *s) {
        if (mpfr_set_str(value, s, defaults::base, defaults::rnd) != 0) {
            std::cerr << "Error assigning mpfr_t from char:" << std::endl;
            throw std::runtime_error("Failed to initialize mpfr_t with given string.");
        }
        return *this;
    }
    mpfr_class &operator=(const std::string &s) {
        if (mpfr_set_str(value, s.c_str(), defaults::base, defaults::rnd) != 0) {
            std::cerr << "Error assigning mpfr_t from string: " << s << std::endl;
            throw std::runtime_error("Failed to initialize mpfr_t with given string.");
        }
        return *this;
    }
    // int mpfr_set (mpfr_t rop, mpfr_t op, mpfr_rnd_t rnd)
    // int mpfr_set_ui (mpfr_t rop, unsigned long int op, mpfr_rnd_t rnd)
    // int mpfr_set_si (mpfr_t rop, long int op, mpfr_rnd_t rnd)
    //_int mpfr_set_uj (mpfr_t rop, uintmax_t op, mpfr_rnd_t rnd)
    //_int mpfr_set_sj (mpfr_t rop, intmax_t op, mpfr_rnd_t rnd)
    //_int mpfr_set_flt (mpfr_t rop, float op, mpfr_rnd_t rnd)
    // int mpfr_set_d (mpfr_t rop, double op, mpfr_rnd_t rnd)
    // int mpfr_set_ld (mpfr_t rop, long double op, mpfr_rnd_t rnd)
    // int mpfr_set_float128 (mpfr_t rop, _Float128 op, mpfr_rnd_t rnd)
    // int mpfr_set_decimal64 (mpfr_t rop, _Decimal64 op, mpfr_rnd_t rnd)
    // int mpfr_set_decimal128 (mpfr_t rop, _Decimal128 op, mpfr_rnd_t rnd)
    // int mpfr_set_z (mpfr_t rop, mpz_t op, mpfr_rnd_t rnd)
    // int mpfr_set_q (mpfr_t rop, mpq_t op, mpfr_rnd_t rnd)
    // int mpfr_set_f (mpfr_t rop, mpf_t op, mpfr_rnd_t rnd)
    // int mpfr_set_ui_2exp (mpfr_t rop, unsigned long int op, mpfr_exp_t e, mpfr_rnd_t rnd)
    // int mpfr_set_si_2exp (mpfr_t rop, long int op, mpfr_exp_t e, mpfr_rnd_t rnd)
    // int mpfr_set_uj_2exp (mpfr_t rop, uintmax_t op, intmax_t e, mpfr_rnd_t rnd)
    // int mpfr_set_sj_2exp (mpfr_t rop, intmax_t op, intmax_t e, mpfr_rnd_t rnd)
    //_int mpfr_set_z_2exp (mpfr_t rop, mpz_t op, mpfr_exp_t e, mpfr_rnd_t rnd)
    //_int mpfr_set_str (mpfr_t rop, const char *s, int base, mpfr_rnd_t rnd)
    //_int mpfr_strtofr (mpfr_t rop, const char *nptr, char **endptr, int base, mpfr_rnd_t rnd)
    // void mpfr_set_nan (mpfr_t x)
    // void mpfr_set_inf (mpfr_t x, int sign)
    // void mpfr_set_zero (mpfr_t x, int sign)
    // void mpfr_swap (mpfr_t x, mpfr_t y)
    ////////////////////////////////////////////////////////////////////////////////////////
    // 5.3 Combined Initialization and Assignment Functions
    ////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////
    // 5.4 Conversion Functions
    ////////////////////////////////////////////////////////////////////////////////////////
    // float mpfr_get_flt (mpfr_t op, mpfr_rnd_t rnd)
    // double mpfr_get_d (mpfr_t op, mpfr_rnd_t rnd)
    // long double mpfr_get_ld (mpfr_t op, mpfr_rnd_t rnd)
    //_Float128 mpfr_get_float128 (mpfr_t op, mpfr_rnd_t rnd)
    //_Decimal64 mpfr_get_decimal64 (mpfr_t op, mpfr_rnd_t rnd)
    //_Decimal128 mpfr_get_decimal128 (mpfr_t op, mpfr_rnd_t rnd)
    // long int mpfr_get_si (mpfr_t op, mpfr_rnd_t rnd)
    // unsigned long int mpfr_get_ui (mpfr_t op, mpfr_rnd_t rnd)
    // intmax_t mpfr_get_sj (mpfr_t op, mpfr_rnd_t rnd)
    // uintmax_t mpfr_get_uj (mpfr_t op, mpfr_rnd_t rnd)
    // double mpfr_get_d_2exp (long *exp, mpfr_t op, mpfr_rnd_t rnd)
    // long double mpfr_get_ld_2exp (long *exp, mpfr_t op, mpfr_rnd_t rnd)
    // int mpfr_frexp (mpfr_exp_t *exp, mpfr_t y, mpfr_t x, mpfr_rnd_t rnd)
    // mpfr_exp_t mpfr_get_z_2exp (mpz_t rop, mpfr_t op)
    // int mpfr_get_z (mpz_t rop, mpfr_t op, mpfr_rnd_t rnd)
    // void mpfr_get_q (mpq_t rop, mpfr_t op)
    // int mpfr_get_f (mpf_t rop, mpfr_t op, mpfr_rnd_t rnd)
    // size_t mpfr_get_str_ndigits (int b, mpfr_prec_t p)
    // char * mpfr_get_str (char *str, mpfr_exp_t *expptr, int base, size_t n, mpfr_t op, mpfr_rnd_t rnd)
    // void mpfr_free_str (char *str)
    // int mpfr_fits_ulong_p (mpfr_t op, mpfr_rnd_t rnd)
    // int mpfr_fits_slong_p (mpfr_t op, mpfr_rnd_t rnd)
    // int mpfr_fits_uint_p (mpfr_t op, mpfr_rnd_t rnd)
    // int mpfr_fits_sint_p (mpfr_t op, mpfr_rnd_t rnd)
    // int mpfr_fits_ushort_p (mpfr_t op, mpfr_rnd_t rnd)
    // int mpfr_fits_sshort_p (mpfr_t op, mpfr_rnd_t rnd)
    // int mpfr_fits_uintmax_p (mpfr_t op, mpfr_rnd_t rnd)
    // int mpfr_fits_intmax_p (mpfr_t op, mpfr_rnd_t rnd)
    ////////////////////////////////////////////////////////////////////////////////////////
    // 5.5 Arithmetic Functions
    ////////////////////////////////////////////////////////////////////////////////////////
    mpfr_class operator+(const mpfr_class &rhs) const {
        mpfr_class rop;
        mpfr_add(rop.value, value, rhs.value, defaults::rnd);
        return rop;
    }
    mpfr_class &operator+=(const mpfr_class &rhs) {
        mpfr_add(value, value, rhs.value, defaults::rnd);
        return *this;
    }
    mpfr_class operator*(const mpfr_class &rhs) const {
        mpfr_class rop;
        mpfr_mul(rop.value, this->value, rhs.value, defaults::rnd);
        return rop;
    }
    mpfr_class &operator*=(const mpfr_class &rhs) {
        mpfr_mul(value, value, rhs.value, defaults::rnd);
        return *this;
    }
    mpfr_class operator-(const mpfr_class &rhs) const {
        mpfr_class rop;
        mpfr_sub(rop.value, this->value, rhs.value, defaults::rnd);
        return rop;
    }
    mpfr_class &operator-=(const mpfr_class &rhs) {
        mpfr_sub(value, value, rhs.value, defaults::rnd);
        return *this;
    }
    mpfr_class operator/(const mpfr_class &rhs) const {
        mpfr_class rop;
        mpfr_div(rop.value, this->value, rhs.value, defaults::rnd);
        return rop;
    }
    mpfr_class &operator/=(const mpfr_class &rhs) {
        mpfr_div(value, value, rhs.value, defaults::rnd);
        return *this;
    }
    mpfr_class &operator+=(double rhs) {
        mpfr_add_d(this->value, this->value, rhs, defaults::rnd);
        return *this;
    }
    mpfr_class &operator-=(double rhs) {
        mpfr_sub_d(this->value, this->value, rhs, defaults::rnd);
        return *this;
    }
    mpfr_class &operator*=(double rhs) {
        mpfr_mul_d(this->value, this->value, rhs, defaults::rnd);
        return *this;
    }
    mpfr_class &operator/=(double rhs) {
        mpfr_div_d(this->value, this->value, rhs, defaults::rnd);
        return *this;
    }
    friend mpfr_class operator+(const mpfr_class &lhs, const double rhs);
    friend mpfr_class operator+(const double lhs, const mpfr_class &rhs);
    friend mpfr_class operator-(const mpfr_class &lhs, const double rhs);
    friend mpfr_class operator-(const double lhs, const mpfr_class &rhs);
    friend mpfr_class operator*(const mpfr_class &lhs, const double rhs);
    friend mpfr_class operator*(const double lhs, const mpfr_class &rhs);
    friend mpfr_class operator/(const mpfr_class &lhs, double rhs);
    friend mpfr_class operator/(const double lhs, const mpfr_class &rhs);

    friend mpfr_class sqrt(const mpfr_class &a, mpfr_rnd_t rnd);
    friend mpfr_class neg(const mpfr_class &a, mpfr_rnd_t rnd);
    friend mpfr_class abs(const mpfr_class &a, mpfr_rnd_t rnd);
    friend mpfr_class mul_2ui(const mpfr_class &op1, unsigned long int op2, mpfr_rnd_t rnd);
    friend mpfr_class mul_2si(const mpfr_class &op1, long int op2, mpfr_rnd_t rnd);
    friend mpfr_class div_2ui(const mpfr_class &op1, unsigned long int op2, mpfr_rnd_t rnd);
    friend mpfr_class div_2si(const mpfr_class &op1, long int op2, mpfr_rnd_t rnd);
    // int mpfr_add (mpfr_t rop, mpfr_t op1, mpfr_t op2, mpfr_rnd_t rnd)
    // int mpfr_add_ui (mpfr_t rop, mpfr_t op1, unsigned long int op2, mpfr_rnd_t rnd)
    // int mpfr_add_si (mpfr_t rop, mpfr_t op1, long int op2, mpfr_rnd_t rnd)
    // int mpfr_add_d (mpfr_t rop, mpfr_t op1, double op2, mpfr_rnd_t rnd)
    // int mpfr_add_z (mpfr_t rop, mpfr_t op1, mpz_t op2, mpfr_rnd_t rnd)
    // int mpfr_add_q (mpfr_t rop, mpfr_t op1, mpq_t op2, mpfr_rnd_t rnd)
    // int mpfr_sub (mpfr_t rop, mpfr_t op1, mpfr_t op2, mpfr_rnd_t rnd)
    // int mpfr_ui_sub (mpfr_t rop, unsigned long int op1, mpfr_t op2, mpfr_rnd_t rnd)
    // int mpfr_sub_ui (mpfr_t rop, mpfr_t op1, unsigned long int op2, mpfr_rnd_t rnd)
    // int mpfr_si_sub (mpfr_t rop, long int op1, mpfr_t op2, mpfr_rnd_t rnd)
    // int mpfr_sub_si (mpfr_t rop, mpfr_t op1, long int op2, mpfr_rnd_t rnd)
    // int mpfr_d_sub (mpfr_t rop, double op1, mpfr_t op2, mpfr_rnd_t rnd)
    // int mpfr_sub_d (mpfr_t rop, mpfr_t op1, double op2, mpfr_rnd_t rnd)
    // int mpfr_z_sub (mpfr_t rop, mpz_t op1, mpfr_t op2, mpfr_rnd_t rnd)
    // int mpfr_sub_z (mpfr_t rop, mpfr_t op1, mpz_t op2, mpfr_rnd_t rnd)
    // int mpfr_sub_q (mpfr_t rop, mpfr_t op1, mpq_t op2, mpfr_rnd_t rnd)
    // int mpfr_mul (mpfr_t rop, mpfr_t op1, mpfr_t op2, mpfr_rnd_t rnd)
    // int mpfr_mul_ui (mpfr_t rop, mpfr_t op1, unsigned long int op2, mpfr_rnd_t rnd)
    // int mpfr_mul_si (mpfr_t rop, mpfr_t op1, long int op2, mpfr_rnd_t rnd)
    // int mpfr_mul_d (mpfr_t rop, mpfr_t op1, double op2, mpfr_rnd_t rnd)
    // int mpfr_mul_z (mpfr_t rop, mpfr_t op1, mpz_t op2, mpfr_rnd_t rnd)
    // int mpfr_mul_q (mpfr_t rop, mpfr_t op1, mpq_t op2, mpfr_rnd_t rnd)
    // int mpfr_sqr (mpfr_t rop, mpfr_t op, mpfr_rnd_t rnd)
    // int mpfr_div (mpfr_t rop, mpfr_t op1, mpfr_t op2, mpfr_rnd_t rnd)
    // int mpfr_ui_div (mpfr_t rop, unsigned long int op1, mpfr_t op2, mpfr_rnd_t rnd)
    // int mpfr_div_ui (mpfr_t rop, mpfr_t op1, unsigned long int op2, mpfr_rnd_t rnd)
    // int mpfr_si_div (mpfr_t rop, long int op1, mpfr_t op2, mpfr_rnd_t rnd)
    // int mpfr_div_si (mpfr_t rop, mpfr_t op1, long int op2, mpfr_rnd_t rnd)
    // int mpfr_d_div (mpfr_t rop, double op1, mpfr_t op2, mpfr_rnd_t rnd)
    // int mpfr_div_d (mpfr_t rop, mpfr_t op1, double op2, mpfr_rnd_t rnd)
    // int mpfr_div_z (mpfr_t rop, mpfr_t op1, mpz_t op2, mpfr_rnd_t rnd)
    // int mpfr_div_q (mpfr_t rop, mpfr_t op1, mpq_t op2, mpfr_rnd_t rnd)
    // int mpfr_sqrt (mpfr_t rop, mpfr_t op, mpfr_rnd_t rnd)
    // int mpfr_sqrt_ui (mpfr_t rop, unsigned long int op, mpfr_rnd_t rnd)
    // int mpfr_rec_sqrt (mpfr_t rop, mpfr_t op, mpfr_rnd_t rnd)
    // int mpfr_cbrt (mpfr_t rop, mpfr_t op, mpfr_rnd_t rnd)
    // int mpfr_rootn_ui (mpfr_t rop, mpfr_t op, unsigned long int n, mpfr_rnd_t rnd)
    // int mpfr_rootn_si (mpfr_t rop, mpfr_t op, long int n, mpfr_rnd_t rnd)
    // int mpfr_root (mpfr_t rop, mpfr_t op, unsigned long int n, mpfr_rnd_t rnd)
    // int mpfr_neg (mpfr_t rop, mpfr_t op, mpfr_rnd_t rnd)
    // int mpfr_abs (mpfr_t rop, mpfr_t op, mpfr_rnd_t rnd)
    // int mpfr_dim (mpfr_t rop, mpfr_t op1, mpfr_t op2, mpfr_rnd_t rnd)
    // int mpfr_mul_2ui (mpfr_t rop, mpfr_t op1, unsigned long int op2, mpfr_rnd_t rnd)
    // int mpfr_mul_2si (mpfr_t rop, mpfr_t op1, long int op2, mpfr_rnd_t rnd)
    // int mpfr_div_2ui (mpfr_t rop, mpfr_t op1, unsigned long int op2, mpfr_rnd_t rnd)
    // int mpfr_div_2si (mpfr_t rop, mpfr_t op1, long int op2, mpfr_rnd_t rnd)
    // int mpfr_fac_ui (mpfr_t rop, unsigned long int op, mpfr_rnd_t rnd)
    // int mpfr_fma (mpfr_t rop, mpfr_t op1, mpfr_t op2, mpfr_t op3, mpfr_rnd_t rnd)
    // int mpfr_fms (mpfr_t rop, mpfr_t op1, mpfr_t op2, mpfr_t op3, mpfr_rnd_t rnd)
    // int mpfr_fmma (mpfr_t rop, mpfr_t op1, mpfr_t op2, mpfr_t op3, mpfr_t op4, mpfr_rnd_t rnd)
    // int mpfr_fmms (mpfr_t rop, mpfr_t op1, mpfr_t op2, mpfr_t op3, mpfr_t op4, mpfr_rnd_t rnd)
    // int mpfr_hypot (mpfr_t rop, mpfr_t x, mpfr_t y, mpfr_rnd_t rnd)
    // int mpfr_sum (mpfr_t rop, const mpfr_ptr tab[], unsigned long int n, mpfr_rnd_t rnd)
    // int mpfr_dot (mpfr_t rop, const mpfr_ptr a[], const mpfr_ptr b[], unsigned long int n, mpfr_rnd_t rnd)
    ////////////////////////////////////////////////////////////////////////////////////////
    // 5.6 Comparison Functions
    ////////////////////////////////////////////////////////////////////////////////////////
    friend inline bool operator==(const mpfr_class &op1, const mpfr_class &op2) { return mpfr_equal_p(op1.value, op2.value) != 0; }
    friend inline bool operator!=(const mpfr_class &op1, const mpfr_class &op2) { return mpfr_lessgreater_p(op1.value, op2.value) != 0; }
    friend inline bool operator<(const mpfr_class &op1, const mpfr_class &op2) { return mpfr_less_p(op1.value, op2.value) != 0; }
    friend inline bool operator>(const mpfr_class &op1, const mpfr_class &op2) { return mpfr_greater_p(op1.value, op2.value) != 0; }
    friend inline bool operator<=(const mpfr_class &op1, const mpfr_class &op2) { return mpfr_lessequal_p(op1.value, op2.value) != 0; }
    friend inline bool operator>=(const mpfr_class &op1, const mpfr_class &op2) { return mpfr_greaterequal_p(op1.value, op2.value) != 0; }
    bool is_nan() const { return mpfr_nan_p(value) != 0; }
    bool is_inf() const { return mpfr_inf_p(value) != 0; }
    // int mpfr_cmp (mpfr_t op1, mpfr_t op2)
    // int mpfr_cmp_ui (mpfr_t op1, unsigned long int op2)
    // int mpfr_cmp_si (mpfr_t op1, long int op2)
    // int mpfr_cmp_d (mpfr_t op1, double op2)
    // int mpfr_cmp_ld (mpfr_t op1, long double op2)
    // int mpfr_cmp_z (mpfr_t op1, mpz_t op2)
    // int mpfr_cmp_q (mpfr_t op1, mpq_t op2)
    // int mpfr_cmp_f (mpfr_t op1, mpf_t op2)
    // int mpfr_cmp_ui_2exp (mpfr_t op1, unsigned long int op2, mpfr_exp_t e)
    // int mpfr_cmp_si_2exp (mpfr_t op1, long int op2, mpfr_exp_t e)
    // int mpfr_cmpabs (mpfr_t op1, mpfr_t op2)
    // int mpfr_cmpabs_ui (mpfr_t op1, unsigned long int op2)
    // int mpfr_nan_p (mpfr_t op)
    // int mpfr_inf_p (mpfr_t op)
    // int mpfr_number_p (mpfr_t op)
    // int mpfr_zero_p (mpfr_t op)
    // int mpfr_regular_p (mpfr_t op)
    // int mpfr_greater_p (mpfr_t op1, mpfr_t op2)
    // int mpfr_greaterequal_p (mpfr_t op1, mpfr_t op2)
    // int mpfr_less_p (mpfr_t op1, mpfr_t op2)
    // int mpfr_lessequal_p (mpfr_t op1, mpfr_t op2)
    // int mpfr_equal_p (mpfr_t op1, mpfr_t op2)
    // int mpfr_lessgreater_p (mpfr_t op1, mpfr_t op2)
    // int mpfr_unordered_p (mpfr_t op1, mpfr_t op2)
    // int mpfr_total_order_p (mpfr_t x, mpfr_t y)
    ////////////////////////////////////////////////////////////////////////////////////////
    // 5.7 Transcendental Functions
    ////////////////////////////////////////////////////////////////////////////////////////
    friend mpfr_class log(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class log_ui(unsigned long int op, mpfr_rnd_t rnd);
    friend mpfr_class log2(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class log10(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class log1p(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class log2p1(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class log10p1(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class exp(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class exp2(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class exp10(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class expm1(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class exp2m1(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class exp10m1(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class pow(const mpfr_class &op1, const mpfr_class &op2, mpfr_rnd_t rnd);
    friend mpfr_class powr(const mpfr_class &op1, const mpfr_class &op2, mpfr_rnd_t rnd);
    friend mpfr_class pow_ui(const mpfr_class &op1, unsigned long int op2, mpfr_rnd_t rnd);
    friend mpfr_class pow_si(const mpfr_class &op1, long int op2, mpfr_rnd_t rnd);
    friend mpfr_class pow_uj(const mpfr_class &op1, uintmax_t op2, mpfr_rnd_t rnd);
    friend mpfr_class pow_sj(const mpfr_class &op1, intmax_t op2, mpfr_rnd_t rnd);
    friend mpfr_class pown(const mpfr_class &op1, intmax_t n, mpfr_rnd_t rnd);
    friend mpfr_class pow_z(const mpfr_class &op1, const mpz_t op2, mpfr_rnd_t rnd);
    friend mpfr_class ui_pow_ui(unsigned long int op1, unsigned long int op2, mpfr_rnd_t rnd);
    friend mpfr_class ui_pow(unsigned long int op1, const mpfr_class &op2, mpfr_rnd_t rnd);
    friend mpfr_class cos(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class sin(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class tan(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class cosu(const mpfr_class &op, unsigned long int u, mpfr_rnd_t rnd);
    friend mpfr_class sinu(const mpfr_class &op, unsigned long int u, mpfr_rnd_t rnd);
    friend mpfr_class tanu(const mpfr_class &op, unsigned long int u, mpfr_rnd_t rnd);
    friend mpfr_class cospi(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class sinpi(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class tanpi(const mpfr_class &op, mpfr_rnd_t rnd);
    friend void sin_cos(mpfr_class &sop, mpfr_class &cop, const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class sec(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class csc(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class cot(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class acos(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class asin(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class acosu(const mpfr_class &op, unsigned long int u, mpfr_rnd_t rnd);
    friend mpfr_class asinu(const mpfr_class &op, unsigned long int u, mpfr_rnd_t rnd);
    friend mpfr_class atanu(const mpfr_class &op, unsigned long int u, mpfr_rnd_t rnd);
    friend mpfr_class acospi(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class asinpi(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class atanpi(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class atan2(const mpfr_class &y, const mpfr_class &x, mpfr_rnd_t rnd);
    friend mpfr_class atan2u(const mpfr_class &y, const mpfr_class &x, unsigned long int u, mpfr_rnd_t rnd);
    friend mpfr_class atan2pi(const mpfr_class &y, const mpfr_class &x, mpfr_rnd_t rnd);
    friend mpfr_class cosh(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class sinh(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class tanh(const mpfr_class &op, mpfr_rnd_t rnd);
    friend void sinh_cosh(mpfr_class &sop, mpfr_class &cop, const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class sech(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class csch(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class coth(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class acosh(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class asinh(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class atanh(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class eint(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class li2(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class gamma(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class gamma_inc(const mpfr_class &op, const mpfr_class &op2, mpfr_rnd_t rnd);
    friend mpfr_class lngamma(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class lgamma(const mpfr_class &op, int &signp, mpfr_rnd_t rnd);
    friend mpfr_class digamma(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class beta(const mpfr_class &op1, const mpfr_class &op2, mpfr_rnd_t rnd);
    friend mpfr_class zeta(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class zeta_ui(unsigned long int op, mpfr_rnd_t rnd);
    friend mpfr_class erf(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class erfc(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class j0(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class j1(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class jn(long int n, const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class y0(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class y1(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class yn(long int n, const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class agm(const mpfr_class &op1, const mpfr_class &op2, mpfr_rnd_t rnd);
    friend mpfr_class ai(const mpfr_class &x, mpfr_rnd_t rnd);
    friend mpfr_class const_log2(mpfr_rnd_t rnd);
    friend mpfr_class const_pi(mpfr_rnd_t rnd);
    friend mpfr_class const_euler(mpfr_rnd_t rnd);
    friend mpfr_class const_catalan(mpfr_rnd_t rnd);
    ////////////////////////////////////////////////////////////////////////////////////////
    // 5.8 Input and Output Functions
    ////////////////////////////////////////////////////////////////////////////////////////
    friend std::ostream &operator<<(std::ostream &os, const mpfr_class &m);
    ////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////
    // 5.9 Formatted Output Functions
    ////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////
    // 5.10 Integer and Remainder Related Functions
    ////////////////////////////////////////////////////////////////////////////////////////
    // int mpfr_ceil (mpfr_t rop, mpfr_t op)
    // int mpfr_floor (mpfr_t rop, mpfr_t op)
    // int mpfr_round (mpfr_t rop, mpfr_t op)
    // int mpfr_roundeven (mpfr_t rop, mpfr_t op)
    // int mpfr_trunc (mpfr_t rop, mpfr_t op)
    // int mpfr_rint_ceil (mpfr_t rop, mpfr_t op, mpfr_rnd_t rnd)
    // int mpfr_rint_floor (mpfr_t rop, mpfr_t op, mpfr_rnd_t rnd)
    // int mpfr_rint_round (mpfr_t rop, mpfr_t op, mpfr_rnd_t rnd)
    // int mpfr_rint_roundeven (mpfr_t rop, mpfr_t op, mpfr_rnd_t rnd)
    // int mpfr_rint_trunc (mpfr_t rop, mpfr_t op, mpfr_rnd_t rnd)
    // int mpfr_frac (mpfr_t rop, mpfr_t op, mpfr_rnd_t rnd)
    // int mpfr_modf (mpfr_t iop, mpfr_t fop, mpfr_t op, mpfr_rnd_t rnd)
    // int mpfr_fmod (mpfr_t r, mpfr_t x, mpfr_t y, mpfr_rnd_t rnd)
    // int mpfr_fmod_ui (mpfr_t r, mpfr_t x, unsigned long int y, mpfr_rnd_t rnd)
    // int mpfr_fmodquo (mpfr_t r, long int* q, mpfr_t x, mpfr_t y, mpfr_rnd_t rnd)
    // int mpfr_remainder (mpfr_t r, mpfr_t x, mpfr_t y, mpfr_rnd_t rnd)
    // int mpfr_remquo (mpfr_t r, long int* q, mpfr_t x, mpfr_t y, mpfr_rnd_t rnd)
    // int mpfr_integer_p (mpfr_t op)
    ////////////////////////////////////////////////////////////////////////////////////////
    // 5.11 Integer and Remainder Related Functions
    ////////////////////////////////////////////////////////////////////////////////////////
    // int mpfr_prec_round (mpfr_t x, mpfr_prec_t prec, mpfr_rnd_t rnd)
    // int mpfr_can_round (mpfr_t b, mpfr_exp_t err, mpfr_rnd_t rnd1, mpfr_rnd_t rnd2, mpfr_prec_t prec)
    // mpfr_prec_t mpfr_min_prec (mpfr_t x)
    // const char * mpfr_print_rnd_mode (mpfr_rnd_t rnd)
    ////////////////////////////////////////////////////////////////////////////////////////
    // 5.12 Miscellaneous Functions
    ////////////////////////////////////////////////////////////////////////////////////////
    // void mpfr_nexttoward (mpfr_t x, mpfr_t y)
    // void mpfr_nextabove (mpfr_t x)
    // void mpfr_nextbelow (mpfr_t x)
    // int mpfr_min (mpfr_t rop, mpfr_t op1, mpfr_t op2, mpfr_rnd_t rnd)
    // int mpfr_max (mpfr_t rop, mpfr_t op1, mpfr_t op2, mpfr_rnd_t rnd)
    // int mpfr_urandomb (mpfr_t rop, gmp_randstate_t state)
    // int mpfr_urandom (mpfr_t rop, gmp_randstate_t state, mpfr_rnd_t rnd)
    // int mpfr_nrandom (mpfr_t rop1, gmp_randstate_t state, mpfr_rnd_t rnd)
    // int mpfr_grandom (mpfr_t rop1, mpfr_t rop2, gmp_randstate_t state, mpfr_rnd_t rnd)
    // int mpfr_erandom (mpfr_t rop1, gmp_randstate_t state, mpfr_rnd_t rnd)
    // mpfr_exp_t mpfr_get_exp (mpfr_t x)
    // int mpfr_set_exp (mpfr_t x, mpfr_exp_t e)
    // int mpfr_signbit (mpfr_t op)
    // int mpfr_setsign (mpfr_t rop, mpfr_t op, int s, mpfr_rnd_t rnd)
    // int mpfr_copysign (mpfr_t rop, mpfr_t op1, mpfr_t op2, mpfr_rnd_t rnd)
    // const char * mpfr_get_version (void)
    // const char * mpfr_get_patches (void)
    // int mpfr_buildopt_tls_p (void)
    // int mpfr_buildopt_float128_p (void)
    // int mpfr_buildopt_decimal_p (void)
    // int mpfr_buildopt_gmpinternals_p (void)
    // int mpfr_buildopt_sharedcache_p (void)
    // const char * mpfr_buildopt_tune_case (void)
    mpfr_srcptr get_mpfr_t() const { return value; }

  private:
    mpfr_t value;
};

std::ostream &operator<<(std::ostream &os, const mpfr_class &m) {
    std::streamsize prec = os.precision();
    std::ios_base::fmtflags flags = os.flags();

    char *str = nullptr;
    if (flags & std::ios::scientific) {
        mpfr_asprintf(&str, "%.*Re", static_cast<int>(prec), m.value);
    } else if (flags & std::ios::fixed) {
        mpfr_asprintf(&str, "%.*Rf", static_cast<int>(prec), m.value);
    } else {
        mpfr_asprintf(&str, "%.*Rg", static_cast<int>(prec), m.value);
    }
    os << str;
    mpfr_free_str(str);

    return os;
}
inline mpfr_class operator+(const mpfr_class &lhs, const double rhs) {
    mpfr_class result(lhs);
    result += rhs;
    return result;
}
inline mpfr_class operator+(const double lhs, const mpfr_class &rhs) {
    mpfr_class result(rhs);
    result += lhs;
    return result;
}
inline mpfr_class operator-(const mpfr_class &lhs, const double rhs) {
    mpfr_class result(lhs);
    result -= rhs;
    return result;
}
inline mpfr_class operator-(const double lhs, const mpfr_class &rhs) {
    mpfr_class result;
    mpfr_d_sub(result.value, lhs, rhs.value, defaults::rnd);
    return result;
}
inline mpfr_class operator*(const mpfr_class &lhs, const double rhs) {
    mpfr_class result(lhs);
    result *= rhs;
    return result;
}
inline mpfr_class operator*(const double lhs, const mpfr_class &rhs) {
    mpfr_class result(rhs);
    result *= lhs;
    return result;
}
inline mpfr_class operator/(const mpfr_class &lhs, const double rhs) {
    mpfr_class result(lhs);
    result /= rhs;
    return result;
}
inline mpfr_class operator/(const double lhs, const mpfr_class &rhs) {
    mpfr_class result;
    mpfr_d_div(result.value, lhs, rhs.value, defaults::rnd);
    return result;
}
inline mpfr_class sqrt(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_sqrt(rop.value, op.get_mpfr_t(), rnd);
    return rop;
}
inline mpfr_class neg(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_neg(rop.value, op.get_mpfr_t(), rnd);
    return rop;
}
inline mpfr_class abs(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_abs(rop.value, op.get_mpfr_t(), rnd);
    return rop;
}
inline mpfr_class mul_2ui(const mpfr_class &op1, unsigned long int op2, mpfr_rnd_t rnd) {
    mpfr_class rop;
    mpfr_mul_2ui(rop.value, op1.value, op2, rnd);
    return rop;
}
inline mpfr_class mul_2si(const mpfr_class &op1, long int op2, mpfr_rnd_t rnd) {
    mpfr_class rop;
    mpfr_mul_2si(rop.value, op1.value, op2, rnd);
    return rop;
}
inline mpfr_class div_2ui(const mpfr_class &op1, unsigned long int op2, mpfr_rnd_t rnd) {
    mpfr_class rop;
    mpfr_div_2ui(rop.value, op1.value, op2, rnd);
    return rop;
}
inline mpfr_class div_2si(const mpfr_class &op1, long int op2, mpfr_rnd_t rnd) {
    mpfr_class rop;
    mpfr_div_2si(rop.value, op1.value, op2, rnd);
    return rop;
}
inline mpfr_class log(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_log(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class log_ui(unsigned long int op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_log_ui(rop.value, op, rnd);
    return rop;
}
inline mpfr_class log2(const mpfr_class &a, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_log2(rop.value, a.value, rnd);
    return rop;
}
inline mpfr_class log10(const mpfr_class &a, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_log10(rop.value, a.value, rnd);
    return rop;
}
inline mpfr_class log1p(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_log1p(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class log2p1(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_log2p1(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class log10p1(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_log10p1(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class exp(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_exp(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class exp2(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_exp2(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class exp10(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_exp10(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class expm1(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_expm1(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class exp2m1(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_exp2m1(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class exp10m1(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_exp10m1(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class pow(const mpfr_class &op1, const mpfr_class &op2, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_pow(rop.value, op1.value, op2.value, rnd);
    return rop;
}
inline mpfr_class powr(const mpfr_class &op1, const mpfr_class &op2, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_powr(rop.value, op1.value, op2.value, rnd);
    return rop;
}
inline mpfr_class pow_ui(const mpfr_class &op1, unsigned long int op2, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_pow_ui(rop.value, op1.value, op2, rnd);
    return rop;
}
inline mpfr_class pow_si(const mpfr_class &op1, long int op2, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_pow_si(rop.value, op1.value, op2, rnd);
    return rop;
}
/*
inline mpfr_class pow_uj(const mpfr_class &op1, uintmax_t op2, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_pow_uj(rop.value, op1.value, op2, rnd);
    return rop;
}
inline mpfr_class pow_sj(const mpfr_class &op1, intmax_t op2, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_pow_sj(rop.value, op1.value, op2, rnd);
    return rop;
}
inline mpfr_class pown(const mpfr_class &op1, intmax_t n, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_pown(rop.value, op1.value, n, rnd);
    return rop;
}
*/
inline mpfr_class pow_z(const mpfr_class &op1, const mpz_t op2, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_pow_z(rop.value, op1.value, op2, rnd);
    return rop;
}
inline mpfr_class ui_pow_ui(unsigned long int op1, unsigned long int op2, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_ui_pow_ui(rop.value, op1, op2, rnd);
    return rop;
}
inline mpfr_class ui_pow(unsigned long int op1, const mpfr_class &op2, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_ui_pow(rop.value, op1, op2.value, rnd);
    return rop;
}
inline mpfr_class cos(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_cos(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class sin(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_sin(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class tan(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_tan(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class cosu(const mpfr_class &op, unsigned long int u, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_cosu(rop.value, op.value, u, rnd);
    return rop;
}
inline mpfr_class sinu(const mpfr_class &op, unsigned long int u, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_sinu(rop.value, op.value, u, rnd);
    return rop;
}
inline mpfr_class tanu(const mpfr_class &op, unsigned long int u, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_tanu(rop.value, op.value, u, rnd);
    return rop;
}
inline mpfr_class cospi(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_cospi(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class sinpi(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_sinpi(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class tanpi(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_tanpi(rop.value, op.value, rnd);
    return rop;
}
void sin_cos(mpfr_class &sop, mpfr_class &cop, const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) { mpfr_sin_cos(sop.value, cop.value, op.value, rnd); }
inline mpfr_class sec(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_sec(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class csc(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_csc(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class cot(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_cot(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class acos(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_acos(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class asin(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_asin(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class acosu(const mpfr_class &op, unsigned long int u, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_acosu(rop.value, op.value, u, rnd);
    return rop;
}
inline mpfr_class asinu(const mpfr_class &op, unsigned long int u, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_asinu(rop.value, op.value, u, rnd);
    return rop;
}
inline mpfr_class atanu(const mpfr_class &op, unsigned long int u, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_atanu(rop.value, op.value, u, rnd);
    return rop;
}
inline mpfr_class acospi(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_acospi(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class asinpi(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_asinpi(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class atanpi(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_atanpi(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class atan2(const mpfr_class &y, const mpfr_class &x, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_atan2(rop.value, y.value, x.value, rnd);
    return rop;
}
inline mpfr_class atan2u(const mpfr_class &y, const mpfr_class &x, unsigned long int u, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_atan2u(rop.value, y.value, x.value, u, rnd);
    return rop;
}
inline mpfr_class atan2pi(const mpfr_class &y, const mpfr_class &x, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_atan2pi(rop.value, y.value, x.value, rnd);
    return rop;
}
inline mpfr_class cosh(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_cosh(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class sinh(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_sinh(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class tanh(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_tanh(rop.value, op.value, rnd);
    return rop;
}
void sinh_cosh(mpfr_class &sop, mpfr_class &cop, const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) { mpfr_sinh_cosh(sop.value, cop.value, op.value, rnd); }
inline mpfr_class sech(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_sech(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class csch(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_csch(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class coth(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_coth(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class acosh(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_acosh(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class asinh(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_asinh(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class atanh(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_atanh(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class eint(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_eint(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class li2(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_li2(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class beta(const mpfr_class &op1, const mpfr_class &op2, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_beta(rop.value, op1.value, op2.value, rnd);
    return rop;
}
inline mpfr_class gamma(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_gamma(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class gamma_inc(const mpfr_class &op, const mpfr_class &op2, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_gamma_inc(rop.value, op.value, op2.value, rnd);
    return rop;
}
inline mpfr_class lngamma(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_lngamma(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class lgamma(const mpfr_class &op, int &signp, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_lgamma(rop.value, &signp, op.value, rnd);
    return rop;
}
inline mpfr_class digamma(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_digamma(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class zeta(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_zeta(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class zeta_ui(unsigned long int op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_zeta_ui(rop.value, op, rnd);
    return rop;
}
inline mpfr_class erf(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_erf(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class erfc(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_erfc(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class j0(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_j0(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class j1(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_j1(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class jn(long int n, const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_jn(rop.value, n, op.value, rnd);
    return rop;
}
inline mpfr_class y0(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_y0(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class y1(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_y1(rop.value, op.value, rnd);
    return rop;
}
inline mpfr_class yn(long int n, const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_yn(rop.value, n, op.value, rnd);
    return rop;
}
inline mpfr_class agm(const mpfr_class &op1, const mpfr_class &op2, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_agm(rop.value, op1.value, op2.value, rnd);
    return rop;
}
inline mpfr_class ai(const mpfr_class &x, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_ai(rop.value, x.value, rnd);
    return rop;
}
inline mpfr_class const_log2(mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_const_log2(rop.value, rnd);
    return rop;
}
inline mpfr_class const_pi(mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_const_pi(rop.value, rnd);
    return rop;
}
inline mpfr_class const_euler(mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_const_euler(rop.value, rnd);
    return rop;
}
inline mpfr_class const_catalan(mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class rop;
    mpfr_const_catalan(rop.value, rnd);
    return rop;
}

} // namespace mpfr

namespace std {

template <> class numeric_limits<mpfr::mpfr_class> {
  public:
    static constexpr bool is_specialized = true;

    static mpfr::mpfr_class min() noexcept {
        mpfr::mpfr_class rop;
        //        mpfr_prec_t prec = mpfr::get_default_prec(); // Get default precision or use the precision of the current context
        //        mpfr_exp_t _min_exp = mpfr::get_emin();
        //        mpfr_mul_2exp(rop, rop, _min_exp, MPFR_RNDN); // Scale 1 by 2^min_exp
        return rop;
    }

    static mpfr::mpfr_class max() noexcept {
        // Return the largest finite value, depending on the precision you've set in mpfr_class
        mpfr::mpfr_class rop(0.0);
        return rop;
    }

    static constexpr bool is_signed = true;
    static constexpr bool is_integer = false;
    static constexpr bool is_exact = false;
    static constexpr int radix = 2; // MPFR is binary-based

    static mpfr::mpfr_class epsilon() noexcept {
        mpfr::mpfr_class rop(0.0);
        return rop;
    }

    static mpfr::mpfr_class round_error() noexcept {
        mpfr::mpfr_class rop(0.0);
        return rop;
    }
#ifdef MAHO
    static constexpr int min_exponent = /* appropriate value based on MPFR */;
    static constexpr int min_exponent10 = /* appropriate value based on MPFR */;
    static constexpr int max_exponent = /* appropriate value based on MPFR */;
    static constexpr int max_exponent10 = /* appropriate value based on MPFR */;
#endif
    static constexpr bool has_infinity = true;
    static constexpr bool has_quiet_NaN = true;
    static constexpr bool has_signaling_NaN = true;
    static constexpr float_denorm_style has_denorm = denorm_absent;
    static constexpr bool has_denorm_loss = false;

    static mpfr::mpfr_class infinity() noexcept {
        mpfr::mpfr_class rop(0.0);
        return rop;
    }

    static mpfr::mpfr_class quiet_NaN() noexcept {
        mpfr::mpfr_class rop(0.0);
        return rop;
    }

    static mpfr::mpfr_class signaling_NaN() noexcept {
        mpfr::mpfr_class rop(0.0);
        return rop;
    }

    static mpfr::mpfr_class denorm_min() noexcept {
        mpfr::mpfr_class rop(0.0);
        return rop;
    }

    static constexpr bool is_iec559 = false;  // MPFR does not conform to IEEE 754 entirely
    static constexpr bool is_bounded = false; // Arbitrary precision means not truly bounded
    static constexpr bool is_modulo = false;
#ifdef MAHO
    static constexpr bool traps = /* depends on mpfr_class's error handling */;
#endif
    static constexpr bool tinyness_before = false;
    static constexpr float_round_style round_style = round_to_nearest; // or other rounding style supported by MPFR
};

} // namespace std

mpfr_prec_t mpfr::defaults::prec;
mpfr_rnd_t mpfr::defaults::rnd;
int mpfr::defaults::base;

class mpfr_class_initializer {
  public:
    mpfr_class_initializer() {
        mpfr::defaults::set_default_prec(512);
        mpfr::defaults::set_default_rounding_mode(MPFR_RNDN);
        mpfr::defaults::set_default_base(10);
    }
};

mpfr_class_initializer global_mpfr_class_initializer;
