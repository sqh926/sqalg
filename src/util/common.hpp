#ifndef SQALG_UTIL_COMMON_HPP
#define SQALG_UTIL_COMMON_HPP


#include <cstdint>
using i8 = int8_t;
using u8 = uint8_t;
using i16 = int16_t;
using u16 = uint16_t;
using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using i128 = __int128_t;
using u128 = __uint128_t;


// different for every translation unit
#ifdef SQALG_MAXN
static constexpr i32 maxn = SQALG_MAXN;
#else
static constexpr i32 maxn = 1 << 19;
#endif


inline u32 mulmod32(u32 x, u32 y, u32 mod) {
    return (u64)x * y % mod;
}
inline u64 mulmod64(u64 x, u64 y, u64 mod) {
    return (u128)x * y % mod;
}

u32 bpow32(u32 a, i64 n, u32 mod) {
    u32 res = 1;
    while (n) { if (n & 1) res = mulmod32(res, a, mod); a = mulmod32(a, a, mod); n >>= 1; }
    return res;
}

u64 bpow64(u64 a, i64 n, u64 mod) {
    u64 res = 1;
    while (n) { if (n & 1) res = mulmod64(res, a, mod); a = mulmod64(a, a, mod); n >>= 1; }
    return res;       
}

#endif // SQALG_UTIL_COMMON_HPP
