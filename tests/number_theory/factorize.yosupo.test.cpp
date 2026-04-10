// @brief Factorize
#define PROBLEM "https://judge.yosupo.jp/problem/factorize"

#include <iostream>
#include "src/number_theory/factorize.hpp"
#include "blazingio/blazingio.min.hpp"

using namespace std;
using namespace sqalg;

i32 main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    u64 n; cin >> n;
    auto factors = factorize(n);
    i32 size = 0;
    for (int i = 0; i < factors.size(); i++) size += factors[i].second;
    cout << size << "\n";
    for (const auto& [p, e] : factors) {
        for(int i = 0; i < e; i++) {
            cout << p << " ";
        }
    }
    cout << "\n";
}
