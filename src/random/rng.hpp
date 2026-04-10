#ifndef SQALG_RANDOM_RNG_HPP
#define SQALG_RANDOM_RNG_HPP

#include <chrono>
#include <random>

namespace sqalg {
    std::mt19937_64 gen(
	std::chrono::steady_clock::now().time_since_epoch().count()
    );

    uint64_t rng() {
	return gen();
    }
}

#endif // SQALG_RANDOM_RNG_HPP
