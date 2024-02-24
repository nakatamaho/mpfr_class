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

#define ___MPFR_CLASS_EXPLICIT___ explicit

namespace mpfr {

class defaults {
  public:
    static mpfr_prec_t prec;
    static mpfr_rnd_t rnd;
    static int base;

    ////////////////////////////////////////////////////////////////////////////////////////
    // 5.1 Initialization Functions (part II)
    ////////////////////////////////////////////////////////////////////////////////////////
    static inline mpfr_prec_t get_default_prec() { return mpfr_get_default_prec(); }
    static void set_default_prec(mpfr_prec_t prec) { mpfr_set_default_prec(prec); }
    static inline mpfr_rnd_t get_default_rounding_mode() { return mpfr_get_default_rounding_mode(); }
    static void set_default_rounding_mode(mpfr_rnd_t r = MPFR_RNDN) { mpfr_set_default_rounding_mode(r); }
    static inline mpfr_prec_t get_default_base() { return base; }
    static void set_default_base(int _base) { base = _base; }
};

class mpfr_class {
  public:
    ////////////////////////////////////////////////////////////////////////////////////////
    // 5.1 Initialization Functions (part I)
    ////////////////////////////////////////////////////////////////////////////////////////
    mpfr_class() { mpfr_init(value); }
    ~mpfr_class() { mpfr_clear(value); }
    void set_prec(mpfr_prec_t prec) { mpfr_set_prec(value, prec); }
    mpfr_prec_t get_prec() const { return mpfr_get_prec(value); }

    ////////////////////////////////////////////////////////////////////////////////////////
    // 5.2 Assignment Functions
    ////////////////////////////////////////////////////////////////////////////////////////
    mpfr_class(const mpfr_class &other) {
        mpfr_init2(value, mpfr_get_prec(other.value));
        mpfr_set(value, other.value, defaults::rnd);
    }
    // Initialization using a constructor
    // move constructor
    mpfr_class(mpfr_class &&other) noexcept { mpfr_swap(value, other.value); }
    ___MPFR_CLASS_EXPLICIT___ mpfr_class(int si) noexcept {
        mpfr_init(value);
        mpfr_set_si(value, si, defaults::rnd);
    }
    ___MPFR_CLASS_EXPLICIT___ mpfr_class(float op) noexcept {
        mpfr_init(value);
        mpfr_set_flt(value, op, defaults::rnd);
    }
    ___MPFR_CLASS_EXPLICIT___ mpfr_class(double d) noexcept {
        mpfr_init(value);
        mpfr_set_d(value, d, defaults::rnd);
    }
    ___MPFR_CLASS_EXPLICIT___ mpfr_class(long double op) noexcept {
        mpfr_init(value);
        mpfr_set_ld(value, op, defaults::rnd);
    }
    ___MPFR_CLASS_EXPLICIT___ mpfr_class(_Float128 op) noexcept {
        mpfr_init(value);
        mpfr_set_float128(value, op, defaults::rnd);
    }
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
    ////////////////////////////////////////////////////////////////////////////////////////
    // 5.3 Combined Initialization and Assignment Functions
    ////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////
    // 5.4 Conversion Functions
    ////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////
    // 5.5 Arithmetic Functions
    ////////////////////////////////////////////////////////////////////////////////////////
    mpfr_class operator+(const mpfr_class &rhs) const {
        mpfr_class result;
        mpfr_add(result.value, value, rhs.value, defaults::rnd);
        return result;
    }
    mpfr_class &operator+=(const mpfr_class &rhs) {
        mpfr_add(value, value, rhs.value, defaults::rnd);
        return *this;
    }
    mpfr_class operator*(const mpfr_class &rhs) const {
        mpfr_class result;
        mpfr_mul(result.value, this->value, rhs.value, defaults::rnd);
        return result;
    }
    mpfr_class &operator*=(const mpfr_class &rhs) {
        mpfr_mul(value, value, rhs.value, defaults::rnd);
        return *this;
    }
    mpfr_class operator-(const mpfr_class &rhs) const {
        mpfr_class result;
        mpfr_sub(result.value, this->value, rhs.value, defaults::rnd);
        return result;
    }
    mpfr_class &operator-=(const mpfr_class &rhs) {
        mpfr_sub(value, value, rhs.value, defaults::rnd);
        return *this;
    }
    mpfr_class operator/(const mpfr_class &rhs) const {
        mpfr_class result;
        mpfr_div(result.value, this->value, rhs.value, defaults::rnd);
        return result;
    }
    mpfr_class &operator/=(const mpfr_class &rhs) {
        mpfr_div(value, value, rhs.value, defaults::rnd);
        return *this;
    }
    friend mpfr_class sqrt(const mpfr_class &a, mpfr_rnd_t rnd);
    friend mpfr_class neg(const mpfr_class &a, mpfr_rnd_t rnd);
    friend mpfr_class abs(const mpfr_class &a, mpfr_rnd_t rnd);

    ////////////////////////////////////////////////////////////////////////////////////////
    // 5.6 Comparison Functions
    ////////////////////////////////////////////////////////////////////////////////////////
    friend inline bool operator==(const mpfr_class &lhs, const mpfr_class &rhs) { return mpfr_equal_p(lhs.value, rhs.value) != 0; }
    friend inline bool operator!=(const mpfr_class &lhs, const mpfr_class &rhs) { return mpfr_lessgreater_p(lhs.value, rhs.value) != 0; }
    friend inline bool operator<(const mpfr_class &lhs, const mpfr_class &rhs) { return mpfr_less_p(lhs.value, rhs.value) != 0; }
    friend inline bool operator>(const mpfr_class &lhs, const mpfr_class &rhs) { return mpfr_greater_p(lhs.value, rhs.value) != 0; }
    friend inline bool operator<=(const mpfr_class &lhs, const mpfr_class &rhs) { return mpfr_lessequal_p(lhs.value, rhs.value) != 0; }
    friend inline bool operator>=(const mpfr_class &lhs, const mpfr_class &rhs) { return mpfr_greaterequal_p(lhs.value, rhs.value) != 0; }

    ////////////////////////////////////////////////////////////////////////////////////////
    // 5.7 Transcendental Functions
    ////////////////////////////////////////////////////////////////////////////////////////
    friend mpfr_class log(const mpfr_class &a, mpfr_rnd_t rnd);
    friend mpfr_class log_ui(unsigned long int op, mpfr_rnd_t rnd);
    friend mpfr_class log2(const mpfr_class &a, mpfr_rnd_t rnd);
    friend mpfr_class log10(const mpfr_class &a, mpfr_rnd_t rnd);
    friend mpfr_class log1p(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class log2p1(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class log10p1(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class exp(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class exp2(const mpfr_class &op, mpfr_rnd_t rnd);
    friend mpfr_class exp10(const mpfr_class &op, mpfr_rnd_t rnd);
    ///...///
    friend mpfr_class const_log2(mpfr_rnd_t rnd);
    friend mpfr_class const_pi(mpfr_rnd_t rnd);
    friend mpfr_class const_euler(mpfr_rnd_t rnd);
    friend mpfr_class const_catalan(mpfr_rnd_t rnd);

    ////////////////////////////////////////////////////////////////////////////////////////
    // 5.8 Input and Output Functions
    ////////////////////////////////////////////////////////////////////////////////////////
    friend std::ostream &operator<<(std::ostream &os, const mpfr_class &m);
    ////////////////////////////////////////////////////////////////////////////////////////
    bool is_nan() const { return mpfr_nan_p(value) != 0; }
    bool is_inf() const { return mpfr_inf_p(value) != 0; }

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

inline mpfr_class sqrt(const mpfr_class &a, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class result;
    mpfr_sqrt(result.value, a.get_mpfr_t(), rnd);
    return result;
}

mpfr_class neg(const mpfr_class &a, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class result;
    mpfr_neg(result.value, a.get_mpfr_t(), rnd);
    return result;
  }

mpfr_class abs(const mpfr_class &a, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class result;
    mpfr_abs(result.value, a.get_mpfr_t(), rnd);
    return result;
}

inline mpfr_class log(const mpfr_class &a, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class result;
    mpfr_log(result.value, a.value, rnd);
    return result;
}

inline mpfr_class log_ui(unsigned long int op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class result;
    mpfr_log_ui(result.value, op, rnd);
    return result;
}

inline mpfr_class log2(const mpfr_class &a, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class result;
    mpfr_log2(result.value, a.value, rnd);
    return result;
}

inline mpfr_class log10(const mpfr_class &a, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class result;
    mpfr_log10(result.value, a.value, rnd);
    return result;
}
inline mpfr_class log1p(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class result;
    mpfr_log1p(result.value, op.value, rnd);
    return result;
}

inline mpfr_class log2p1(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class result;
    mpfr_log2p1(result.value, op.value, rnd);
    return result;
}

inline mpfr_class log10p1(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class result;
    mpfr_log10p1(result.value, op.value, rnd);
    return result;
}

inline mpfr_class exp(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class result;
    mpfr_exp(result.value, op.value, rnd);
    return result;
}

inline mpfr_class exp2(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class result;
    mpfr_exp2(result.value, op.value, rnd);
    return result;
}

inline mpfr_class exp10(const mpfr_class &op, mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class result;
    mpfr_exp10(result.value, op.value, rnd);
    return result;
}

///...///

inline mpfr_class const_log2(mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class result;
    mpfr_const_log2(result.value, rnd);
    return result;
}

inline mpfr_class const_pi(mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class result;
    mpfr_const_pi(result.value, rnd);
    return result;
}

inline mpfr_class const_euler(mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class result;
    mpfr_const_euler(result.value, rnd);
    return result;
}

inline mpfr_class const_catalan(mpfr_rnd_t rnd = defaults::rnd) {
    mpfr_class result;
    mpfr_const_catalan(result.value, rnd);
    return result;
}

} // namespace mpfr

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
