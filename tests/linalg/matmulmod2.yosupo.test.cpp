// @brief Matrix Product (Mod 2)
#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product_mod_2"
#define SQALG_MAXN 1 << 12
#include <iostream>
#include "src/util/common.hpp"
#include "src/structures/bitvector.hpp"
#include "blazingio/blazingio.min.hpp"



using namespace std;
using namespace sqalg;
constexpr i32 K = 8;

bitvector<maxn> a[maxn], b[maxn], c[maxn], table[1 << K];

// table[i] stores all combinations of xors of b[i], ... b[i + K - 1]
void calc(i32 i) {
    for(size_t j = 0; j < K; j++) {
        i32 step = 1 << j;
	memcpy(table + step, table, step * sizeof(table[0]));
	for (i32 k = 0; k < step; k++)
	    table[k + step] ^= b[i + j];
    }
}


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
    const u16 bits = bitvector<maxn>::bits;
    for (i32 j = 0; j < m; j += bits) {
	for (i32 offset = 0; offset < bits; offset += K) {
	    calc(offset + j);
	    for (i32 i = 0; i < n; i++)
		c[i] ^= table[u8(a[i].data[j / bits] >> offset)];
	}
    }

    for (i32 i = 0; i < n; i++) {
	for (i32 j = 0; j < k; j++) {
	    cout << c[i][j];
	}
	cout << "\n";
    }
}


