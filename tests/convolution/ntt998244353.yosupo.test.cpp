// @brief Convolution (998244353)
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include <iostream>
#include "src/number_theory/modint.hpp"
#include "src/convolution/ntt.hpp"
// #include "blazingio/blazingio.min.hpp"


using namespace std;
using namespace sqalg;

using mint = modint998244353;
constexpr i32 gen = 3;

i32 main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 n, m; cin >> n >> m;
    vector<i32> a(n), b(m);
    for (i32 i = 0; i < n; i++) cin >> a[i];
    for (i32 i = 0; i < m; i++) cin >> b[i];

    auto c = conv_ntt<mint>(a, b, gen);
    for (auto x : c) cout << x << " ";
}
