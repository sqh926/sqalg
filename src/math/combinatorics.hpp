#ifndef SQALG_MATH_COMBINATORICS_HPP
#define SQALG_MATH_COMBINATORICS_HPP

#include "src/util/common.hpp"
#include <vector>

namespace sqalg {

    template<typename modint>
    modint fact(i32 n) {
	static std::vector<modint> f(maxn);
	static bool initiated = false;
	if (!initiated) {
	    f[0] = modint(1);
	    for (i32 i = 1; i < maxn; i++)
		f[i] = f[i - 1] * modint(i);
	    initiated = true;
	}
	return f[n];    
    }

    template<typename modint>
    modint ifact(i32 n) {
	static std::vector<modint> f(maxn);
	static bool initiated = false;
	if (!initiated) {
	    i32 lst = (i32)std::min(modint::mod(), maxn) - 1;
	    f[lst] = modint(1) / fact<modint>(lst);
	    for (i32 i = lst - 1; i >= 0; i--)
		f[i] = f[i + 1] * modint(i + 1);
	    initiated = true;
	}
	return f[n];
    }

    template<typename modint>
    modint C(i32 n, i32 k) {
	if (n < 0 || k < 0 || n - k < 0) return modint(0);
	return fact<modint>(n) * ifact<modint>(k) * ifact<modint>(n - k);    
    }
} // namespace sqalg

#endif // SQALG_MATH_COMBINATORICS_HPP
