#include <iostream>
#include "src/number_theory/modint.hpp"
#define SQALG_MAXN 10000001
#include "src/math/combinatorics.hpp"
#include "blazingio/blazinio.min.hpp"


using namespace std;


i32 main() {
    i32 q, m;
    cin >> q >> m;
    dynamic_modint.set_mod(m);
    while (q-->0) {
	i32 n, k;
	cin >> n >> k;
	cout << C(n, k) << "\n";
    }
}
