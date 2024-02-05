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

    static inline mpfr_prec_t get_default_prec() { return mpfr_get_default_prec(); }
    static void set_default_prec(mpfr_prec_t prec) { mpfr_set_default_prec(prec); }
    static inline mpfr_rnd_t get_default_rounding_mode() { return mpfr_get_default_rounding_mode(); }
    static void set_default_rounding_mode(mpfr_rnd_t r = MPFR_RNDN) { mpfr_set_default_rounding_mode(r); }
};

class mpfr_class {
  public:
    mpfr_class() { mpfr_init(value); }
    mpfr_class(double _d) {
        mpfr_init(value);
        mpfr_set_d(value, _d, defaults::rnd);
    }

    mpfr_class(const mpfr_class &other) {
        mpfr_init2(value, mpfr_get_prec(other.value));
        mpfr_set(value, other.value, MPFR_RNDN);
    }

    mpfr_class(mpfr_class &&other) noexcept {
        mpfr_swap(value, other.value);
        std::cout << "Move Assignment called A\n";
    }

    mpfr_class &operator=(mpfr_class other) noexcept {
        mpfr_swap(value, other.value);
        std::cout << "Move Assignment called B\n";
        return *this;
    }

    ~mpfr_class() { mpfr_clear(value); }

    mpfr_class operator+(const mpfr_class &other) const {
        mpfr_class result;
        mpfr_add(result.value, value, other.value, MPFR_RNDN);
        return result;
    }

    mpfr_class &operator+=(const mpfr_class &other) {
        mpfr_add(value, value, other.value, MPFR_RNDN);
        return *this;
    }
    mpfr_t *get_mpfr_t() { return &value; }

  private:
    mpfr_t value;
};
} // namespace mpfrcxx

mpfr_prec_t mpfrcxx::defaults::prec;
mpfr_rnd_t mpfrcxx::defaults::rnd;

class Initializer {
  public:
    Initializer() {
        mpfrcxx::defaults::set_default_prec(512);
        mpfrcxx::defaults::set_default_rounding_mode(MPFR_RNDN);
    }
};

Initializer globalInitializer;
