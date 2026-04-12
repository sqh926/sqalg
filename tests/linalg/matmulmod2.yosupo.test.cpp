// @brief Matrix Product (Mod 2)
#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product_mod_2"
#define SQALG_MAXN 1 << 12

#include <iostream>
#include "src/util/common.hpp"
#include "src/structures/bitvector.hpp"
// #include "blazingio/blazingio.min.hpp"

using namespace std;
using namespace sqalg;

bitvector<maxn> a[maxn], b[maxn], c[maxn];
string s;

void from_string(bitvector<maxn>& bv) {
    cin >> s;
    for (i32 i = 0; i < s.size(); i++)
	if (s[i] == '1')
	    bv.set(i);	        
}


i32 main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    i16 n, m, k;
    cin >> n >> m >> k;
    
    for (i32 i = 0; i < n; i++) {
	from_string(a[i]);	
    }
    for (i32 i = 0; i < m; i++) {
	from_string(b[i]);
    }
    for (i32 i = 0; i < n; i++)
	for (i32 j = 0; j < m; j++)
	    if (a[i][j])
		c[i] ^= b[j];
    for (i32 i = 0; i < n; i++) {
	for (i32 j = 0; j < k; j++) {
	    cout << c[i][j];
	}
	cout << "\n";
    }
}


