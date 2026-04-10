#ifndef SQALG_RANDOM_RNG_HPP
#define SQALG_RANDOM_RNG_HPP

#include <chrono>
#include <random>

namespace sqalg {

    inline uint64_t rng() {
	static std::mt19937_64 gen(
	    std::chrono::steady_clock::now().time_since_epoch().count()
	    );
	return gen();
    }
}

#endif // SQALG_RANDOM_RNG_HPP
