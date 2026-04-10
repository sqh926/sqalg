// @brief Primality Test
#define PROBLEM "https://judge.yosupo.jp/problem/primality_test"

#include <iostream>
#include "src/number_theory/primality.hpp"
#include "blazingio/blazingio.min.hpp"
using namespace std;
using namespace sqalg;

i32 main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 q; cin >> q;
    while (q--) {
	u64 n; cin >> n;
	cout << (sqalg::is_prime(n) ? "Yes" : "No") << "\n";
    }
}
