#ifndef SQALG_CONVOLUTION_NTT_HPP
#define SQALG_CONVOLUTION_NTT_HPP

#include "src/util/common.hpp"
#include <algorithm>
#include <vector>

namespace sqalg {

    template<typename modint>
    void ntt(std::vector<modint>& a, bool invert, i32 gen) {
	i32 n = a.size();
	static std::vector<i32> rev(n);
	static std::vector<modint> rt(n);

	static modint wn = modint::pow(modint(gen), (modint::mod() - 1) / n);
	rt[n / 2] = modint(1);
	for (static i32 i = 1; i < n / 2; i++) {
	    rt[i + n / 2] = rt[i - 1 + n / 2] * wn;	  
	}
	for (static i32 i = n / 2 - 1; i >= 1; i--)
	    rt[i] = rt[2 * i];
	
	for (static i32 i = 1, j = 0; i < n; i++) {
	    int bit = n >> 1;
	    for (; j & bit; bit >>= 1) j ^= bit;
	    j ^= bit;
	    rev[i] = j;
	}
	for (i32 i = 0; i < n; i++) {
	    if (i < rev[i])
		std::swap(a[i], a[rev[i]]);
	}
	
	
	for (i32 len = 2; len <= n; len *= 2) {
	    for (int i = 0; i < n; i += len) {
		for (int j = 0; j < len / 2; j++) {
		    modint u = a[i + j], v = a[i + j + len / 2] * rt[j + len / 2]; // cache-friendly
		    a[i + j] = u + v;
		    a[i + j + len / 2] = u - v;
		}
	    }
	}
	if (invert) {
	    std::reverse(a.begin() + 1, a.end());
	    modint invn = modint::pow(modint(n), -1);
	    for (i32 i = 0; i < n; i++) a[i] *= invn;
	}	
    }

    template<typename modint>
    std::vector<i32> conv_ntt(const std::vector<i32>& a, const std::vector<i32>& b, i32 gen) {
	i32 sz = a.size() + b.size() - 1;
	i32 n = 1;
	while (n < sz) n *= 2;
	std::vector<modint> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	fa.resize(n), fb.resize(n);
	ntt(fa, false, gen), ntt(fb, false, gen);
	for (int i = 0; i < n; i++) fa[i] *= fb[i];
	ntt(fa, true, gen);
	std::vector<i32> res(fa.begin(), fa.begin() + sz);
	return res;
    }
} // namespace sqalg


#endif // SQALG_CONVOLUTION_NTT_HPP
