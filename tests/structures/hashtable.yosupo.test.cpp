// @brief Associative Array
#define PROBLEM "https://judge.yosupo.jp/problem/associative_array"

#include <iostream>
#include "src/util/common.hpp"
#include "src/structures/hashtable.hpp"
#include "blazingio/blazingio.min.hpp"

using namespace std;
using namespace sqalg;

i32 main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    hashtable ht;
    i32 q; cin >> q;
    while (q--) {
        i8 c; cin >> c;
        if (c == '0') {
            u64 k, v; cin >> k >> v;
            ht[k] = v;
        }
        else if (c == '1') {
            u64 k; cin >> k;
            cout << ht[k] << "\n";
        }
    }
}

