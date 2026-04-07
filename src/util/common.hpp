#ifndef SQALG_UTIL_COMMON_HPP
#define SQALG_UTIL_COMMON_HPP




#include <cstdint>

using i8 = int8_t;
using u8 = uint8_t;
using i16 = int16_t;
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


#endif // SQALG_UTIL_COMMON_HPP
