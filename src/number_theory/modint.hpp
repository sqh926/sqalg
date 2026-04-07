#ifndef SQALG_NUMBER_THEORY_MODINT_HPP
#define SQALG_NUMBER_THEORY_MODINT_HPP

#include "src/util/common.hpp"
#include <istream>
#include <ostream>


namespace sqalg {
    template<i32 MOD>
    struct static_modint {
	i64 x;
	static constexpr i64 modmod8 = 8ull * MOD * MOD;

	static i32 mod() { return MOD; }

	static_modint() = default;
	constexpr static_modint(i64 v) : x(v % MOD + (v >= 0 ? 0 : MOD)) {}
	constexpr static_modint operator+(const static_modint& rhs) { return static_modint(*this) += rhs; }
	constexpr static_modint operator-(const static_modint& rhs) { return static_modint(*this) -= rhs; }
	constexpr static_modint operator*(const static_modint& rhs) { return static_modint(*this) *= rhs; }
	constexpr static_modint operator/(const static_modint& rhs) { return static_modint(*this) /= rhs; }
	constexpr static_modint operator+=(const static_modint& rhs) { x += rhs.x; if (x >= MOD) x -= MOD; return *this; }
	constexpr static_modint operator-=(const static_modint& rhs) { x -= rhs.x; if (x < 0) x += MOD; return *this; }
	constexpr static_modint operator*=(const static_modint& rhs) { (x *= rhs.x) %= MOD; return *this; }
	constexpr static_modint operator/=(const static_modint& rhs) { return *this *= pow(rhs, -1); }
	template<typename T> constexpr explicit operator T() const { return x; }
	constexpr static static_modint pow(static_modint a, i64 p) {
	    // this trick works only for prime mods 
	    p = p % (MOD - 1) + (p >= 0 ? 0 : MOD - 1);
	    static_modint res = 1;
	    while (p) { if (p & 1) res *= a; a *= a; p >>= 1; }
	    return res;
	}

	// dont use those unless you know what youre doing
	void add_unsafe(u64 v) { x += v; }
	void pseudonormalize() { x = std::min(x, x - modmod8); }
	void normalize() {
	    if (x >= MOD) x %= MOD;
	}
	constexpr void from_stream(std::istream& st) { st >> x; }
	constexpr void to_stream(std::ostream& st) const { st << x; } 
    };
    template<i32 MOD, class T> constexpr static_modint<MOD> operator+(T a, static_modint<MOD> b) { return (static_modint<MOD>)a + b; }
    template<i32 MOD, class T> constexpr static_modint<MOD> operator-(T a, static_modint<MOD> b) { return (static_modint<MOD>)a - b; }
    template<i32 MOD, class T> constexpr static_modint<MOD> operator*(T a, static_modint<MOD> b) { return (static_modint<MOD>)a * b; }
    template<i32 MOD, class T> constexpr static_modint<MOD> operator/(T a, static_modint<MOD> b) { return (static_modint<MOD>)a / b; }
    template<i32 MOD> constexpr std::istream& operator>>(std::istream& st, static_modint<MOD>& a) { a.from_stream(st); return st; }
    template<i32 MOD> constexpr std::ostream& operator<<(std::ostream& st, const static_modint<MOD>& a) { a.to_stream(st); return st; }


    struct dynamic_modint {
	i64 x;
	inline static i32 MOD = 0;
	inline static i64 modmod8 = 0;

	static void set_mod(i32 mod) {
	    MOD = mod;
	    modmod8 = 8ull * MOD * MOD;
	}
	static i32 mod() { return MOD; }

	dynamic_modint() = default;
	constexpr dynamic_modint(i64 v) : x(v % MOD + (v >= 0 ? 0 : MOD)) {}
	constexpr dynamic_modint operator+(const dynamic_modint& rhs) { return dynamic_modint(*this) += rhs; }
	constexpr dynamic_modint operator-(const dynamic_modint& rhs) { return dynamic_modint(*this) -= rhs; }
	constexpr dynamic_modint operator*(const dynamic_modint& rhs) { return dynamic_modint(*this) *= rhs; }
	constexpr dynamic_modint operator/(const dynamic_modint& rhs) { return dynamic_modint(*this) /= rhs; }
	constexpr dynamic_modint operator+=(const dynamic_modint& rhs) { x += rhs.x; if (x >= MOD) x -= MOD; return *this; }
	constexpr dynamic_modint operator-=(const dynamic_modint& rhs) { x -= rhs.x; if (x < 0) x += MOD; return *this; }
	constexpr dynamic_modint operator*=(const dynamic_modint& rhs) { (x *= rhs.x) %= MOD; return *this; }
	constexpr dynamic_modint operator/=(const dynamic_modint& rhs) { return *this *= pow(rhs, -1); }
	template<typename T> constexpr explicit operator T() const { return x; }
	constexpr static dynamic_modint pow(dynamic_modint a, i64 p) {
	    // this trick works only for prime mods 
	    p = p % (MOD - 1) + (p >= 0 ? 0 : MOD - 1);
	    dynamic_modint res = 1;
	    while (p) { if (p & 1) res *= a; a *= a; p >>= 1; }
	    return res;
	}

	// dont use those unless you know what youre doing
	void add_unsafe(u64 v) { x += v; }
	void pseudonormalize() { x = std::min(x, x - modmod8); }
	void normalize() {
	    if (x >= MOD) x %= MOD;
	}
	constexpr void from_stream(std::istream& st) { st >> x; }
	constexpr void to_stream(std::ostream& st) const { st << x; }             
    };
    template<class T> constexpr dynamic_modint operator+(T a, dynamic_modint b) { return (dynamic_modint)a + b; }
    template<class T> constexpr dynamic_modint operator-(T a, dynamic_modint b) { return (dynamic_modint)a - b; }
    template<class T> constexpr dynamic_modint operator*(T a, dynamic_modint b) { return (dynamic_modint)a * b; }
    template<class T> constexpr dynamic_modint operator/(T a, dynamic_modint b) { return (dynamic_modint)a / b; }
    constexpr std::istream& operator>>(std::istream& st, dynamic_modint& a) { a.from_stream(st); return st; }
    constexpr std::ostream& operator<<(std::ostream& st, const dynamic_modint& a) { a.to_stream(st); return st; }



    using modint998244353 = static_modint<998244353>;
    using modint1000000007 = static_modint<1000000007>;

} // namespace sqalg
#endif // SQALG_NUMBER_THEORY_STATIC_MODINT_HPP
