// @Brief Longest Increasing Subsequence
#define PROBLEM "https://judge.yosupo.jp/problem/longest_increasing_subsequence"

#include "src/util/common.hpp"
#include "src/structures/fenwick.hpp"
#include <bits/stdc++.h>
#include "blazingio/blazingio.min.hpp"

using namespace std;
using namespace sqalg;

struct maxer {
    pair<i32, i32> operator()(pair<i32, i32> a, pair<i32, i32> b) const {
        return max(a, b);
    }
};

unordered_map<i32, i32> compress(vector<i32> a) {
    sort(a.begin(), a.end());
    unordered_map<i32, i32> res;
    for (i32 i = 0, j = 1; i < a.size(); i++) {
        if (i > 0) j += (a[i] != a[i - 1]);
        res[a[i]] = j;
    }
    return res;
}

void solve() {
    i32 n; cin >> n;
    vector<i32> a(n);
    for (auto& it : a) cin >> it;
    auto mp = compress(a);

    vector<i32> ca(n);
    for (i32 i = 0; i < n; i++) ca[i] = mp[a[i]];

    fenwick<pair<i32, i32>, maxer> fw(vector<pair<i32, i32>>(mp.size() + 1, {0, 0}), maxer{});
    vector<i32> from(n, -1);
    pair<i32, i32> res = {0, -1};

    for (i32 i = 0; i < n; i++) {
        auto [len, last] = fw.pref(ca[i]);
        if (!len) last = -1;
        pair<i32, i32> cur = {len + 1, i};
        res = max(res, cur);
        fw.update(ca[i], cur);
        from[i] = last;
    }

    auto [len, last] = res;
    cout << len << "\n";
    vector<i32> ans;
    for (i32 i = last; i != -1; i = from[i])
        ans.push_back(i);
    for (auto x : ans | views::reverse) cout << x << ' ';
    cout << "\n";
}

i32 main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
}
