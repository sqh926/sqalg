// @brief Inverse Matrix (Mod 2)
#define PROBLEM "https://judge.yosupo.jp/problem/inverse_matrix_mod_2"
#define SQALG_MAXN 1 << 12
#include "src/util/common.hpp"
#include "src/structures/bitvector.hpp"
#include <iostream>
#include "blazingio/blazingio.min.hpp"

using namespace std;
using namespace sqalg;

bitvector<2 * maxn> a[maxn];

string s;
void read_from_string(bitvector<2 * maxn>& bv) {
    cin >> s;
    for (i32 i = 0; i < s.size(); i++)
	if (s[i] == '1')
	    bv.set(i);
}

i32 main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    i32 n; cin >> n;
    vector<i32> lead(n);
    for (i32 i = 0; i < n; i++) {
	read_from_string(a[i]);
	a[i].set(n + i);	
	for (i32 j = 0; j < i; j++) {
	    if (a[i][lead[j]])
		a[i].xor_from(a[j], lead[j]);
	}
	lead[i] = a[i].ctz();
	if (lead[i] >= n) {
	    cout << "-1\n";
	    return 0;
	}
	for (i32 j = 0; j < i; j++) {
	    if (a[j][lead[i]])
		a[j].xor_from(a[i], lead[i]);
	}	
    }
    vector<i32> order(n);
    for (i32 i = 0; i < n; i++)
	order[lead[i]] = i;

    for (i32 i = 0; i < n; i++) {
	for (i32 j = n; j < 2 * n; j++)
	    cout << a[order[i]][j];
	cout << "\n";
    }
}
