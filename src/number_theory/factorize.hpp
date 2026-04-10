#ifndef SQALG_NUMBER_THEORY_FACTORIZE_HPP
#define SQALG_NUMBER_THEORY_FACTORIZE_HPP

#include "src/util/common.hpp"
#include <vector>

namespace sqalg {

    u64 get_divisor(u64 n) {
	u64 t = rng();
	auto f = [&](u64 x) {
	    return (mulmod64(x, x, n) + t) % n;
	};
	u64 x = 0, y = 0, g = 1;
	while (g == 1) {
	    for (int i = 0; i < 64; i++) {
		x = f(x);
		y = f(f(y));
		if (x == y) [[unlikely]] {
		    t = rng();
		    x = y = 0;
		}
		else {
		    u64 t = mulmod64(g, abs(1ll * x - y), n);
		    g = t == 0 ? g : t;
		}
	    }
	    g = std::gcd(g, n);
	}
	return g;
    }

    std::vector<std::pair<u64, i16>> factorize(u64 n) {
	if (is_prime(n)) return { {n, 1} };
	else if (n > 1) {
	    std::vector<std::pair<u64,i16>> res;
	    auto g = get_divisor(n);
	    auto f1 = factorize(g);
	    auto f2 = factorize(n / g);
	    i32 i1 = 0, i2 = 0;
	    sort(f1.begin(), f1.end()), sort(f2.begin(), f2.end());
	    while(i1 < f1.size() && i2 < f2.size()) {
		if (f1[i1].first < f2[i2].first) res.emplace_back(f1[i1++]);
		else if (f1[i1].first > f2[i2].first) res.emplace_back(f2[i2++]);
		else {
		    res.emplace_back(f1[i1].first, f1[i1].second + f2[i2].second), i1++, i2++;
		}
	    }
	    while(i1 < f1.size()) res.emplace_back(f1[i1++]);
	    while(i2 < f2.size()) res.emplace_back(f2[i2++]);
	    return res;
	}
    }
    
    
    
} // namespace sqalg


#endif // SQALG_NUMBER_THEORY_FACTORIZE_HPP
