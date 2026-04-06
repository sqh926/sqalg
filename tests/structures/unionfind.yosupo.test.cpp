#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"
#include <iostream>
#include "src/util/common.hpp"
#include "src/structures/unionfind.hpp"
#include "blazingio/blazingio.min.hpp"
using namespace std;

i32 main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 n, q;
    cin >> n >> q;
    unionfind uf(n);
    while (q-->0) {
	i16 kind; cin >> kind;
	i32 u, v;
	cin >> u >> v;
	if (kind == 0 ) {	  
	    uf.unite(u, v);
	}
	else {
	    cout << (uf.find(u) == uf.find(v) ? "1" : "0") << "\n";  
	}	
    }    
} 
