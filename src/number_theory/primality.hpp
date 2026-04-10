#ifndef SQALG_NUMBER_THEORY_PRIMALITY_HPP
#define SQALG_NUMBER_THEORY_PRIMALITY_HPP

#include "src/util/common.hpp"

namespace sqalg {
    bool is_prime(u64 n) {
	if (n == 1 || n % 2 == 0) return n == 2;
	// n - 1 = d * 2^s
	i16 s = std::countr_zero(n - 1);
	u64 d = (n - 1) >> s;

	auto test = [&](u64 a) -> bool {
	    u64 x = bpow64(a, d, n);
	    if (x == 1) return false;
	    for (int i = 0; i < s; i++) {
		if (x == n - 1) return false;
		x = mulmod64(x, x, n);
	    }
	    return true;
	};

	i32 bases[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
	for (auto a : bases) {
	    if (a % n == 0) continue;
	    if (test(a)) return false;
	}
	return true;	
    }
    
} // namespace sqalg

#endif // SQALG_NUMBER_THEORY_PRIMALITY_HPP
