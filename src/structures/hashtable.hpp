#ifndef SQALG_STRUCTURES_HASHTABLE_HPP
#define SQALG_STRUCTURES_HASHTABLE_HPP

#include "src/util/common.hpp"
#include <chrono>
#include <ext/pb_ds/assoc_container.hpp>

namespace sqalg {
    struct splitmix64 {
	static u64 hash(u64 x) {
	    // http://xorshift.di.unimi.it/splitmix64.c
	    x += 0x9e3779b97f4a7c15;
	    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
	    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
	    return x ^ (x >> 31);
	}
	std::size_t operator()(u64 x) const {
	    static const u64 FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
	    return hash(x + FIXED_RANDOM);
	}
    };
    typedef __gnu_pbds::gp_hash_table<u64, u64, splitmix64> hashtable;
};

#endif // SQALG_STRUCTURES_HASHTABLE_HPP
