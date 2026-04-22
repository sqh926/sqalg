// @Brief Point Add Range Sum
#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include "src/util/common.hpp"
#include "src/structures/fenwick.hpp"
#include <bits/stdc++.h>
#include "blazingio/blazingio.min.hpp"


using namespace std;
using namespace sqalg;

void solve() {
    i32 n,q;
    cin >> n >> q;
    std::vector<i64> a(n);
    for (auto& it : a) cin >> it;
    fenwick<i64> fw(a);
    while (q--) {
	i32 kind;
	cin >> kind;
	if (kind == 0) {
	    i32 i;
	    i64 val;
	    cin >> i >> val;
	    fw.update(i, val);
	}
	else {
	    i32 l, r; cin >> l >> r;
	    cout << fw.range(l, r) << "\n";
	}
    }
    
}

i32 main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    i32 t = 1;
    // cin >> t;
    while (t--) {
	solve();
    }
}
