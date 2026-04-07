// @brief Binomial Coefficient (Prime Mod)
#define PROBLEM "https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod"
#define SQALG_MAXN 10000001
#include <iostream>
#include "src/number_theory/modint.hpp"
#include "src/math/combinatorics.hpp"
#include "blazingio/blazingio.min.hpp"

using namespace std;
using namespace sqalg;


i32 main() {
    i32 q, m;
    cin >> q >> m;
    dynamic_modint::set_mod(m);
    while (q-->0) {
	i32 n, k;
	cin >> n >> k;
	cout << C<dynamic_modint>(n, k) << "\n";
    }
}
