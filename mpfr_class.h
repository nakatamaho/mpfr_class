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

#include <mpfr.h>
#include <iostream>
#include <utility>

namespace mpfrcxx {

class defaults {
  public:
    static mpfr_prec_t prec;
    static mpfr_rnd_t rnd;
    static int base;

    static inline mpfr_prec_t get_default_prec() { return mpfr_get_default_prec(); }
    static void set_default_prec(mpfr_prec_t prec) { mpfr_set_default_prec(prec); }
    static inline mpfr_rnd_t get_default_rounding_mode() { return mpfr_get_default_rounding_mode(); }
    static void set_default_rounding_mode(mpfr_rnd_t r = MPFR_RNDN) { mpfr_set_default_rounding_mode(r); }
    static inline mpfr_prec_t get_default_base() { return base; }
    static void set_default_base(int _base) { base = _base; }
};

class mpfr_class {
  public:
    mpfr_class() { mpfr_init(value); }
    mpfr_class(const mpfr_class &other) {
        mpfr_init2(value, mpfr_get_prec(other.value));
        mpfr_set(value, other.value, defaults::rnd);
    }
    // Initialization using a constructor
    // move constructor
    mpfr_class(mpfr_class &&other) noexcept { mpfr_swap(value, other.value); }
    mpfr_class(double d) noexcept {
        mpfr_init(value);
        mpfr_set_d(value, d, defaults::rnd);
    }
    mpfr_class(unsigned long int ui) {
        mpfr_init(value);
        mpfr_set_ui(value, ui, defaults::rnd);
    }
    mpfr_class(const char *str, int base = defaults::base, mpfr_rnd_t rnd = defaults::rnd) {
        mpfr_init(value);
        if (mpfr_set_str(value, str, base, rnd) != 0) {
            std::cerr << "Error initializing mpfr_t from const char*: " << str << std::endl;
            throw std::runtime_error("Failed to initialize mpfr_t with given string.");
        }
    }
    mpfr_class(const std::string &str, int base = defaults::base, mpfr_rnd_t rnd = defaults::rnd) {
        mpfr_init(value);
        if (mpfr_set_str(value, str.c_str(), base, rnd) != 0) {
            std::cerr << "Error initializing mpfr_t from std::string: " << str << std::endl;
            throw std::runtime_error("Failed to initialize mpfr_t with given string.");
        }
    }

    // Initialization using assignment operator
    // Copy-and-Swap Idiom; it does both the copy assignment operator and the move assignment operator.
    mpfr_class &operator=(mpfr_class other) noexcept {
        mpfr_swap(value, other.value);
        return *this;
    }
    mpfr_class &operator=(double d) noexcept {
        mpfr_set_d(value, d, defaults::rnd);
        return *this;
    }
    mpfr_class &operator=(const char *str) {
        if (mpfr_set_str(value, str, defaults::base, defaults::rnd) != 0) {
            std::cerr << "Error assigning mpfr_t from char:" << std::endl;
            throw std::runtime_error("Failed to initialize mpfr_t with given string.");
        }
        return *this;
    }
    mpfr_class &operator=(const std::string &str) {
        if (mpfr_set_str(value, str.c_str(), defaults::base, defaults::rnd) != 0) {
            std::cerr << "Error assigning mpfr_t from string: " << str << std::endl;
            throw std::runtime_error("Failed to initialize mpfr_t with given string.");
        }
        return *this;
    }

    friend inline bool operator==(const mpfr_class &lhs, const mpfr_class &rhs) { return mpfr_cmp(lhs.value, rhs.value) == 0; }

    ////////////////////////////////////////////////////////////////////////////////////////
    // initialization
    ////////////////////////////////////////////////////////////////////////////////////////
    void set_prec(mpfr_prec_t prec) { mpfr_set_prec(value, prec); }
    mpfr_prec_t get_prec() const { return mpfr_get_prec(value); }

    ////////////////////////////////////////////////////////////////////////////////////////
    // arithmetic
    ////////////////////////////////////////////////////////////////////////////////////////
    mpfr_class operator+(const mpfr_class &other) const {
        mpfr_class result;
        mpfr_add(result.value, value, other.value, defaults::rnd);
        return result;
    }
    mpfr_class &operator+=(const mpfr_class &other) {
        mpfr_add(value, value, other.value, defaults::rnd);
        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////////////////
    // Algebraic and transcendental functions
    ////////////////////////////////////////////////////////////////////////////////////////
    static mpfr_class sqrt(const mpfr_class &a) {
        mpfr_class result;
        mpfr_sqrt(result.value, a.value, defaults::rnd);
        return result;
    }
    static mpfr_class log(const mpfr_class &a) {
        mpfr_class result;
        mpfr_log(result.value, a.value, defaults::rnd);
        return result;
    }
    static mpfr_class log10(const mpfr_class &a) {
        mpfr_class result;
        mpfr_log10(result.value, a.value, defaults::rnd);
        return result;
    }
    static mpfr_class log2(const mpfr_class &a) {
        mpfr_class result;
        mpfr_log2(result.value, a.value, defaults::rnd);
        return result;
    }
    ////////////////////////////////////////////////////////////////////////////////////////
    bool is_nan() const { return mpfr_nan_p(value) != 0; }
    bool is_inf() const { return mpfr_inf_p(value) != 0; }

    mpfr_t *get_mpfr_t() { return &value; }

    ~mpfr_class() { mpfr_clear(value); }

  private:
    mpfr_t value;
};

} // namespace mpfrcxx

mpfr_prec_t mpfrcxx::defaults::prec;
mpfr_rnd_t mpfrcxx::defaults::rnd;
int mpfrcxx::defaults::base;

class Initializer {
  public:
    Initializer() {
        mpfrcxx::defaults::set_default_prec(512);
        mpfrcxx::defaults::set_default_rounding_mode(MPFR_RNDN);
        mpfrcxx::defaults::set_default_base(10);
    }
};

Initializer globalInitializer;
