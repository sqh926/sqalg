#ifndef SQALG_DS_UNION_FIND_HPP
#define SQALG_DS_UNION_FIND_HPP
#include <numeric>
#include <vector>
#include "src/util/common.hpp"

struct unionfind {
    std::vector<i32> parent, rank;

    unionfind(i32 n) : parent(n), rank(n, 0) {
	std::iota(parent.begin(), parent.end(), 0);
    }
    int find(i32 u) {
	return u == parent[u] ? u : parent[u] = find(parent[u]);
    }
    void unite(i32 u, i32 v) {
	u = find(u), v = find(v);
	if (u == v) return;
	if (rank[u] < rank[v])
	    std::swap(u, v);
	parent[v] = u;
	if (rank[u] == rank[v])
	    rank[u]++;
    }
};

#endif //SQALG_DS_UNION_FIND_HPP
