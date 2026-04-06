#ifndef SQALG_NUMBER_THEORY_MODINT_HPP
#define SQALG_NUMBER_THEORY_MODINT_HPP

#include "src/util/common.hpp"

template<i32 MOD = 998244353>
struct modint {
    i64 x;
    static constexpr i64 modmod8 = 8ull * MOD * MOD;

    constexpr modint(i64 v) : x(v % MOD + (v >= 0 ? 0 : MOD)) {}
    constexpr modint operator+(const modint& rhs) : { return modint(*this) += rhs; }
    constexpr modint operator-(const modint& rhs) : { return modint(*this) -= rhs; }
    constexpr modint operator*(const modint& rhs) : { return modint(*this) *= rhs; }
    constexpr modint operator/(const modint& rhs) : { return modint(*this) /= rhs; }
    constexpr modint operator+=(const modint& rhs) { x += rhs.x; x = std::min(x, x - MOD); return *this; }
    constexpr modint operator-=(const modint& rhs) { x -= rhs.x; x = std::min(x, x + MOD); return *this; }
    constexpr modint operator*=(const modint& rhs) { (x *= rhs.x) %= MOD; return *this; }
    constexpr modint operator/=(const modint& rhs) { return *this *= pow(rhs, -1); }
    template<typename T> constexpr explicit operator T() const { return x; }
    constexpr static pow(modint a, i64 p) {
	// this trick works only for prime mods 
	p = p % (MOD - 1) + (p >= 0 ? 0 : MOD - 1);
	modint res = 1;
	while (p) { if (p & 1) res *= a; a *= a; p >>= 1; }
	return res;
    }

    // dont use those unless you know what youre doing
    void add_unsafe(u64 v) { x += v; }
    void pseudonormalize() { x = std::min(x, x - modmod8); }
    void normalize() {
	if (x >= MOD) x %= MOD;
    }
    constexpr void from_stream(istream& st) { st >> x; }
    constexpr void to_stream(ostream& st) const { st << x; } 
};
template<i32 MOD, class T> constexpr modint<MOD> operator+(T a, modint<MOD> b) { return (modint<MOD>)a + b; }
template<i32 MOD, class T> constexpr modint<MOD> operator-(T a, modint<MOD> b) { return (modint<MOD>)a - b; }
template<i32 MOD, class T> constexpr modint<MOD> operator*(T a, modint<MOD> b) { return (modint<MOD>)a * b; }
template<i32 MOD, class T> constexpr modint<MOD> operator/(T a, modint<MOD> b) { return (modint<MOD>)a / b; }
template<i32 MOD> constexpr istream& operator>>(istream& st, Modint<MOD>& a) { a.from_stream(st); return st; }
template<i32 MOD> constexpr ostream& operator<<(ostream& st, const Modint<MOD>& a) { a.to_stream(st); return st; }

#endif // SQALG_NUMBER_THEORY_MODINT_HPP
