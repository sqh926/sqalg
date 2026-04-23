---
title: Fenwick Tree (Binary Indexed Tree)
documentation_of: ../src/structures/fenwick.hpp
---

## Fenwick Tree

**Reference:** [CP-Algorithms — Fenwick Tree](https://cp-algorithms.com/data_structures/fenwick.html)

Given an array $a_0, a_1, \ldots, a_{n-1}$ and an associative binary operation $+$
with a known inverse, we want to support:

- apply $a_i \mathrel{+}= v$,
- compute $a_l + a_{l+1} + \cdots + a_r$.

Both operations are required to run in $O(\log n)$ time.

### Main Idea

Define some function $p(i) \leq i$.
Each node $i$ stores the sum over the range $[p(i), i]$:

$$
f[i] = \sum_{} a[p(i)..i]
$$

### Range Query

To compute a range sum $[l, r]$, first observe that since the operation has an inverse:

$$
a_l + a_{l+1} + \cdots + a_r = \text{pref}(r) - \text{pref}(l - 1).
$$

This reduces the problem to prefix queries.
To compute $\text{pref}(r)$, accumulate $f[r]$,
then jump to $r = p(r) - 1$ and repeat while $r \geq 0$:

```
pref(r):
    res = 0
    while r >= 0:
        res += f[r]
        r = p(r) - 1
    return res
```

> **Note:** if the operation has no inverse, range queries $[l, r]$ are not supported —
> only prefix queries $\text{pref}(r)$.

### Point Update

When $a_i$ changes, all nodes whose range contains $a_i$ must be updated —
that is, all $j$ with $p(j) \leq i \leq j$:

```
add(i, delta):
    for all j with p(j) <= i <= j:
        f[j] += delta
```

### Choosing $p(i)$

The choice of $p(i)$ determines the efficiency of both operations.
For example, $p(i) = 0$ yields a prefix sum array ($O(n)$ update, $O(1)$ query),
and $p(i) = i$ yields a plain array ($O(1)$ update, $O(n)$ query).
We need something better.

There might be a logical way to derive the right $p(i)$, but we will just use magic.
The idea is to look at the binary representation of $i$ and zero out all trailing set bits:

![p(i) example](https://raw.githubusercontent.com/sqh926/sqalg/main/docs/fenwick_pf.png)

Some values:

| $i$ | $p(i)$ |
|-----|--------|
| 0   | 0      |
| 1   | 0      |
| 2   | 2      |
| 3   | 0      |
| 4   | 4      |
| 5   | 4      |
| 6   | 6      |

To compute $p(i)$, note that $i + 1$ clears all trailing 1-bits of $i$ and sets the next 0-bit to 1.
Therefore $i \mathbin{\text{&}} (i+1)$ keeps the prefix and zeros the trailing 1-bits,
giving exactly $p(i)$.

### Finding all $j$ covering $i$

Since $p(j)$ zeros the trailing set bits of $j$, the range $[p(j), j]$ consists of all integers
that share the same prefix as $j$ up to $j$'s lowest 0-bit, with the lower bits arbitrary.
Therefore $p(j) \leq i \leq j$ if and only if $i$ and $j$ share that common prefix
and $j$'s bits below that position are all 1s:

![add example](https://raw.githubusercontent.com/sqh926/sqalg/main/docs/fenwick_add.png)

To enumerate all such $j$, start with $j = i$.
Each subsequent $j$ must have a strictly longer trailing-ones region —
otherwise $p(j)$ would not reach far enough left to include $i$.
The smallest such extension sets $j$'s lowest 0-bit to 1,
growing the trailing-ones region by exactly one position.
Repeating this gives all nodes covering $i$ in increasing order:

![inc example](https://raw.githubusercontent.com/sqh926/sqalg/main/docs/fenwick_inc.png)

Setting the lowest 0-bit is equivalent to $j \leftarrow j \mathbin{\vert} (j+1)$,
since $j + 1$ clears the trailing 1-bits and sets the next 0-bit,
so $j \mathbin{\vert} (j+1)$ preserves the trailing 1-bits and additionally sets that 0-bit.

### Build

Given an initial array, the tree can be built in $O(n)$ by propagating each $f[i]$
directly to its nearest ancestor $h(i) = i \mathbin{\vert} (i+1)$:

$$
f[h(i)] \mathrel{+}= f[i] \quad \text{for } i = 0, 1, \ldots, n-1.
$$

Each node is visited exactly once, giving $O(n)$ total work.

### Complexity

**$\text{pref}(r)$:** Each iteration sets $r \leftarrow p(r) - 1 = (r \mathbin{\text{&}} (r+1)) - 1$,
which clears the lowest set bit of $r+1$.
Since $r+1$ has at most $\lfloor \log_2 n \rfloor + 1$ bits, the loop runs $O(\log n)$ times.

**$\text{add}(i)$:** Each iteration sets $j \leftarrow j \mathbin{\vert} (j+1)$,
which sets one new bit in $j$.
Since $j < n$ has at most $\lfloor \log_2 n \rfloor + 1$ bits, the loop runs $O(\log n)$ times.

| Operation | Time | Space |
|-----------|------|-------|
| Build | $O(n)$ | $O(n)$ |
| `pref(r)` | $O(\log n)$ | $O(1)$ |
| `add(i, v)` | $O(\log n)$ | $O(1)$ |
| `range(l, r)` | $O(\log n)$ | $O(1)$ |
