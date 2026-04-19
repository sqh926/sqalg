---
title: Primality Test (Miller-Rabin)
documentation_of: ../src/number_theory/primality.hpp
---

## Miller-Rabin Primality Test

**Reference:** [Wikipedia — Miller–Rabin primality test](https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test)

Given an integer $n$, we want to determine whether $n$ is prime.

By Fermat's little theorem, $a^{n-1} \equiv 1 \pmod{n}$ for any prime $n$ and $\gcd(a, n) = 1$. However, composite Carmichael numbers also satisfy this for all bases $a$, making the Fermat test unreliable in case of non-random input.

Write $n - 1 = d \cdot 2^s$ with $d$ odd and expand by difference of squares:

$$
a^{n-1} - 1 = (a^d - 1)(a^d + 1)(a^{2d} + 1)\cdots(a^{2^{s-1}d} + 1).
$$

If $n$ is prime, at least one of the factors must be divisible by $n$, that is:

$$
a^d \equiv 1 \pmod{n}, \qquad \text{or} \qquad a^{2^r d} \equiv -1 \pmod{n} \text{ for some } 0 \leq r < s.
$$

If neither holds, $n$ is composite. This strictly strengthens Fermat: Carmichael numbers satisfy $n \mid a^{n-1} - 1$ but fail to have $n$ divide any single factor.

By fixing specific bases the test becomes deterministic up to given bounds:

| $n <$ | bases |
|---|---|
| $2{,}047$ | $\{2\}$ |
| $1{,}373{,}653$ | $\{2, 3\}$ |
| $25{,}326{,}001$ | $\{2, 3, 5\}$ |
| $3{,}215{,}031{,}751$ | $\{2, 3, 5, 7\}$ |
| $4{,}759{,}123{,}141$ | $\{2, 7, 61\}$ |
| $1{,}122{,}004{,}669{,}633$ | $\{2, 13, 23, 1{,}662{,}803\}$ |
| $2^{64}$ | $\{2, 325, 9375, 28178, 450775, 9780504, 1795265022\}$ |
