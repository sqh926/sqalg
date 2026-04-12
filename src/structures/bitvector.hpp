#ifndef SQALG_STRUCTURES_BITVECTOR_HPP
#define SQALG_STRUCTURES_BITVECTOR_HPP

#include "src/util/common.hpp"
#include <array>
#include <vector>
#include <algorithm>
#include <bit>
#include <cassert>

namespace sqalg {

    template<typename Container>
    concept Resizable = requires(Container& c, std::size_t n) { c.resize(n); };

    template<typename Container>
    struct _bitvector {
	using word_t = typename Container::value_type;
	using size_t = std::size_t;
	static constexpr u16 bits = sizeof(word_t) * 8;
	size_t blocks, n;
	Container data;
	constexpr void resize(size_t N) {
	    n = N;
	    blocks = (n + bits - 1) / bits;
	    if constexpr (Resizable<Container>) {
		data.resize(blocks);
	    }
	    else assert(std::size(data) >= blocks);
	}

	constexpr _bitvector() : data() {
	    if constexpr (!Resizable<Container>) {
		resize(std::size(data) * bits);
	    }
	    else resize(0);
	}

	constexpr _bitvector(size_t N) : data() {
	    resize(N);
	}
	constexpr void set() {
	    if (blocks == 0) return;
	    word_t val = -1;
	    for (size_t i = 0; i < blocks; i++)
		data[i] = val;
	    if (n % bits) data[blocks-1] &= (word_t(1) << (n % bits)) - 1;
	}
	constexpr void reset() {
	    word_t val = 0;
	    for (size_t i = 0; i < blocks; i++)
		data[i] = val;
	}
	constexpr void set(size_t i) {
	    data[i / bits] |= word_t(1) << (i % bits);
	}
	constexpr void reset(size_t i) {
	    data[i / bits] &= ~(word_t(1) << (i % bits));
	}
	constexpr void flip(size_t i) {
	    data[i / bits] ^= word_t(1) << (i % bits);
	}
	constexpr bool test(size_t i) const {
	    return (data[i / bits] >> (i % bits)) & 1;
	}
	constexpr bool any() const {
	    for (size_t i = 0; i < blocks; i++)
		if (data[i]) return true;
	    return false;
	}
	constexpr bool none() const { return !any(); }
	constexpr bool all() const {
	    if (blocks == 0) return true;
	    for(size_t i = 0; i < blocks - 1; i++)
		if (data[i] != word_t(-1)) return false;
	    if (n % bits) return data[blocks - 1] == (word_t(1) << (n % bits)) - 1;
	    return data[blocks - 1] == word_t(-1);
	}	
	constexpr size_t count() const {
	    size_t res = 0;
	    for (size_t i = 0; i < blocks; i++)
		res += std::popcount(data[i]);
	    return res;
	}
	constexpr void flip() {
	    if (blocks == 0) return;
	    for(size_t i = 0; i < blocks; i++) {
		data[i] ^= word_t(-1);
	    }
	    if (n % bits) data[blocks - 1] &= (word_t(1) << (n % bits)) - 1;
	}
	constexpr bool operator[](size_t i) const {
	    return test(i);
	}
	constexpr _bitvector& operator ^= (const _bitvector& t) {
	    for (size_t i = 0; i < blocks; i++)
		data[i] ^= t.data[i];
	    return *this;
	}
	constexpr _bitvector operator ^ (const _bitvector& t) const {
	    return _bitvector(*this) ^= t;	    
	}

	constexpr _bitvector& operator <<= (size_t shift) {
	    if (shift >= n) { reset(); return *this; }
	    size_t block_shift = shift / bits;
	    size_t bit_shift = shift % bits;

	    if (block_shift > 0) {
		std::rotate(data.begin(), data.end() - block_shift, data.end());
		std::fill(data.begin(), data.begin() + block_shift, word_t(0));
	    }

	    if (bit_shift > 0) {
		for (i32 i = blocks - 1; i >= 0; i--) {
		    data[i] <<= bit_shift;
		    if (i > 0) data[i] |= data[i - 1] >> (bits - bit_shift);
		}		  
	    }
	    if (n % bits) data[blocks - 1] &= (word_t(1) << (n % bits)) - 1;
	    return *this;
	}
	constexpr _bitvector& operator >>= (size_t shift) {
	    if (shift >= n) { reset(); return *this; }
	    size_t block_shift = shift / bits;
	    size_t bit_shift = shift % bits;

	    if (block_shift > 0) {
		std::rotate(data.begin(), data.begin() + block_shift, data.end());
		std::fill(data.end() - block_shift, data.end(), word_t(0));
	    }

	    if (bit_shift > 0) {
		for (size_t i = 0; i < blocks; i++) {
		    data[i] >>= bit_shift;
		    if (i + 1 < blocks) data[i] |= data[i+1] << (bits - bit_shift);
		}
	    }
	    return *this;
	}
	constexpr _bitvector& operator|=(const _bitvector& t) {
	    for (size_t i = 0; i < blocks; i++)
		data[i] |= t.data[i];
	    return *this;
	}
	constexpr _bitvector& operator&=(const _bitvector& t) {
	    for (size_t i = 0; i < blocks; i++)
		data[i] &= t.data[i];
	    return *this;
	}
	constexpr _bitvector operator|(const _bitvector& t) const { return _bitvector(*this) |= t; }
	constexpr _bitvector operator&(const _bitvector& t) const { return _bitvector(*this) &= t; }
	constexpr _bitvector operator~() const {
	    _bitvector r(*this);
	    r.flip();
	    return r;
	}
	constexpr _bitvector operator << (size_t shift) const {
	    return _bitvector(*this) <<= shift;
	}
	constexpr _bitvector operator >> (size_t shift) const {
	    return _bitvector(*this) >>= shift;
	}

	
    };
    template<std::size_t N>
    using bitvector = _bitvector<std::array<u64, (N + 63) / 64>>;
    using dynamic_bitvector = _bitvector<std::vector<u64>>;
    
    
} // namespace sqalg

#endif // SQALG_STRUCTURES_BITVECTOR_HPP
