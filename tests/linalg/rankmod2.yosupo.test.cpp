// @brief Rank of Matrix (Mod 2)
#define PROBLEM "https://judge.yosupo.jp/problem/matrix_rank_mod_2"
#include "src/util/common.hpp"
#include "src/structures/bitvector.hpp"
#include <iostream>
#include "blazingio/blazingio.min.hpp"

using namespace std;
using namespace sqalg;

i32 main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    i32 n, m; cin >> n >> m;
    if (m == 0) {
	cout << 0;
	return 0;
    }
    vector<dynamic_bitvector> pivots;
    vector<i32> lead;

    dynamic_bitvector cur;
    cur.resize(m);

    string s;
    for (i32 i = 0; i < n; i++) {
	cur.reset();
	cin >> s;
	for (i32 j = 0; j < s.size(); j++)
	    if (s[j] == '1')
		cur.set(j);
	for (i32 j = 0; j < pivots.size(); j++)
	    if (cur[lead[j]])
		cur ^= pivots[j];
	i32 lz = cur.ctz();
	if (lz < m) {
	    pivots.push_back(cur);
	    lead.push_back(lz);
	}
    }
    cout << pivots.size();
}
