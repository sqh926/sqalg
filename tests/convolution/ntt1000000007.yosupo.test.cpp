// @brief Convolution (1000000007)
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#include <iostream>
#include "src/number_theory/modint.hpp"
#include "src/convolution/ntt.hpp"
// #include "blazingio/blazingio.min.hpp"

using namespace std;
using namespace sqalg;

constexpr i32 M = 1e9 + 7;
constexpr i32 M1 = 998244353;
constexpr i32 M2 = 985661441;
constexpr i32 M3 = 754974721;
constexpr i32 g1 = 3;
constexpr i32 g2 = 3;
constexpr i32 g3 = 11;

using mint = static_modint<M>;

i32 main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 n, m; cin >> n >> m;
    vector<i32> a(n), b(m);
    for (i32 i = 0; i < n; i++) cin >> a[i];
    for (i32 i = 0; i < m; i++) cin >> b[i];
    // given r0, r1, r2 modulo p0, p1, p2
    // find x mod n
    // x = a0 + a1 * p0 + a2 * p0 * p1 (solution to crt)
    // a0 = r0 mod p0
    // a1 = (r1 - a0) * p0^-1 mod p1
    // a2 = ((r2 - a0) * p0^-1 - a1) * p1^-1 mod p2
    // x mod n = (a0 + a1 * p0 + a2 * p0 * p1) mod n  
    vector<i32> res[3];
    res[0] = conv_ntt<static_modint<M1>>(a, b, g1);
    res[1] = conv_ntt<static_modint<M2>>(a, b, g2);
    res[2] = conv_ntt<static_modint<M3>>(a, b, g3);
    i64 ip1 = bpow32(M1, M2 - 2, M2);
    i64 ip2 = bpow32(M1, M3 - 2, M3);
    i64 ip3 = bpow32(M2, M3 - 2, M3);
    for (int i = 0; i < n + m - 1; i++) {
	i64 r0 = res[0][i], r1 = res[1][i], r2 = res[2][i];
	i64 a0 = r0;
	i64 a1 = ((r1 - a0) % M2 + M2) % M2 * ip1 % M2;
	i64 a2 = (((r2 - a0) % M3 + M3) % M3 * ip2 % M3 - a1 % M3 + M3) % M3 * ip3 % M3;
	i32 ans = (a0 + a1 * M1 % M + a2 * M1 % M * M2 % M) % M;
	cout << ans << " ";
    }
}
