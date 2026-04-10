#ifndef SQALG_NUMBER_THEORY_FACTORIZE_HPP
#define SQALG_NUMBER_THEORY_FACTORIZE_HPP

#include "src/util/common.hpp"
#include "src/random/rng.hpp"
#include "src/number_theory/primality.hpp"
#include <vector>
#include <algorithm>
#include <numeric>

namespace sqalg {

    u64 get_divisor(u64 n) {
	auto f = [&](u64 x, u64 c) {
	    return ((u128)x * x + c) % n;
	};
	const int batch = 128;
	while (true) {
	    u64 a = rng();
	    u64 b = a;
	    u64 c = rng();
	    u64 pa, pb, g = 1;

	    while (g == 1) {
		pa = a, pb = b;
		u64 q = 1;
		for (i32 i = 0; i < batch; i++) {
		    a = f(a, c);
		    b = f(f(b, c), c);
		    u64 diff = a > b ? a - b : b - a;
		    q = (u128)q * diff % n;
		}
		g = gcd(q, n);
	    }

	    if (g == n) {
		d = 1;
		while (d == 1) {
		    pa = f(pa, c);
		    pb = f(f(pb, c), c);
		    u64 diff = pa > pb ? pa - pb : pb - pa;
		    g = gcd(diff, n);
		}
	    }
	    if (g != n) return g;
	}
	    
	
    }

    std::vector<std::pair<u64, i16>> factorize(u64 n) {
	if (n <= 1) return {};
	if (is_prime(n)) return { {n, 1} };

	if (n % 2 == 0) {
	    int exp = 0;
	    while (n % 2 == 0) n >>= 1, exp++;
	    std::vector<std::pair<u64,i16>> res = {{2, exp}};
	    auto remaining = factorize(n);
	    res.insert(res.end(), remaining.begin(), remaining.end());
	    return res;	    	    
	}
	
	auto g = get_divisor(n);
	auto f1 = factorize(g);
	auto f2 = factorize(n / g);
	std::vector<std::pair<u64,i16>> res;
	size_t i1 = 0, i2 = 0;
	std::sort(f1.begin(), f1.end()), std::sort(f2.begin(), f2.end());
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
    
    
    
} // namespace sqalg


#endif // SQALG_NUMBER_THEORY_FACTORIZE_HPP
