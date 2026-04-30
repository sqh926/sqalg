---
title: Number Theoretic Transform (NTT)
documentation_of: ../src/convolution/ntt.hpp
---

## Number Theoretic Transform

Given two polynomials $A$ and $B$ of degrees $n - 1$ and $m - 1$, we want to compute
their product $C = A \cdot B$ of degree $n + m - 2$.

The naive approach takes $O(nm)$ time. We will show how to do it in $O(n \log n)$.

### Main Idea

By the fundamental theorem of algebra, a polynomial of degree $d$ is uniquely determined
by its values at $d + 1$ distinct points. This gives a three-step algorithm for multiplication:

1. **Evaluate** $A$ and $B$ at $n$ points $x_0, x_1, \ldots, x_{n-1}$ (where $n \geq \deg C + 1$).
2. **Multiply pointwise:** $c_i = A(x_i) \cdot B(x_i)$.
3. **Interpolate** polynomial $C$ from the values $c_0, c_1, \ldots, c_{n-1}$.

The bottleneck is steps 1 and 3: evaluating at $n$ arbitrary points takes $O(n \log^2 n)$
in the best case, and Lagrange interpolation — $O(n^3)$ with a naive implementation.
The key is to choose the evaluation points cleverly so that both steps become $O(n \log n)$.

### Choosing the Evaluation Points

Suppose we have a special element $\omega$ satisfying two conditions:

$$
\omega^n = 1, \qquad \omega^i \neq \omega^j \text{ for } 0 \leq i < j < n.
$$

That is, all $n$ powers $1, \omega, \omega^2, \ldots, \omega^{n-1}$ are distinct.
We call such $\omega$ a **primitive $n$-th root of unity**.

We choose the evaluation points $x_i = \omega^i$.

### DFT

Define the operator $\text{DFT}$ that maps a polynomial $A$ to the vector of its values
at the $n$-th roots of unity:

$$
\text{DFT}(A) = \bigl(A(\omega^0),\, A(\omega^1),\, \ldots,\, A(\omega^{n-1})\bigr).
$$

It is linear since for any polynomials $A$, $B$ and scalars $\alpha$, $\beta$:

$$
\text{DFT}(\alpha A + \beta B)_j = (\alpha A + \beta B)(\omega^j) = \alpha A(\omega^j) + \beta B(\omega^j) = (\alpha\,\text{DFT}(A) + \beta\,\text{DFT}(B))_j.
$$

With this notation, step 1 is computing $\text{DFT}(A)$ and $\text{DFT}(B)$,
and step 3 is computing $\text{DFT}^{-1}$.

### Cooley-Tukey Algorithm

Take $n = 2^k$ and write:

$$
A(x) = A_0(x^2) + x \cdot A_1(x^2),
$$

where $A_0(y) = a_0 + a_2 y + a_4 y^2 + \cdots$ and $A_1(y) = a_1 + a_3 y + a_5 y^2 + \cdots$
collect the even and odd indexed coefficients respectively.

The squares $(\omega^i)^2 = \omega^{2i}$ for $i = 0, \ldots, n-1$ take only $n/2$
distinct values — they are $1, \omega^2, \omega^4, \ldots, \omega^{n-2}$, each appearing twice
(from $i$ and $i + n/2$, since $\omega^n = 1$).

In other words, $\omega^2$ is a primitive $n/2$-th root of unity, and evaluating
$A_0$ and $A_1$ at the $n/2$-th roots of unity is a problem of half the size.
After solving it recursively, we combine for $i = 0, \ldots, n/2 - 1$:

$$
A(\omega^i) = A_0(\omega^{2i}) + \omega^i \cdot A_1(\omega^{2i}),
$$

$$
A(\omega^{i+n/2}) = A_0(\omega^{2i}) - \omega^i \cdot A_1(\omega^{2i}).
$$

The minus sign follows from $\omega^{n/2} = -1$ (since $\omega^{n/2}$ has order $2$ and is not $1$),
so $\omega^{i+n/2} = -\omega^i$.

This gives $O(\log n)$ levels of $O(n)$ work each — $O(n \log n)$ total.

### Inverse Transform

Since $\text{DFT}$ is linear, it can be written as $F \cdot a = y$ for some matrix $F$.
We know what each $y_i$ must equal:

$$
\begin{aligned}
y_0 &= a_0 + a_1 + a_2 + \cdots + a_{n-1}, \\
y_1 &= a_0 + a_1\omega + a_2\omega^2 + \cdots + a_{n-1}\omega^{n-1}, \\
y_i &= a_0 + a_1\omega^i + a_2\omega^{2i} + \cdots + a_{n-1}\omega^{(n-1)i}.
\end{aligned}
$$

So the $i$-th row of $F$ is $(1,\, \omega^i,\, \omega^{2i},\, \ldots,\, \omega^{(n-1)i})$, giving:

$$
F = \begin{pmatrix}
1 & 1 & 1 & \cdots & 1 \\
1 & \omega & \omega^2 & \cdots & \omega^{n-1} \\
1 & \omega^2 & \omega^4 & \cdots & \omega^{2(n-1)} \\
\vdots & \vdots & \vdots & \ddots & \vdots \\
1 & \omega^{n-1} & \omega^{2(n-1)} & \cdots & \omega^{(n-1)^2}
\end{pmatrix}.
$$

It can be shown that:

$$
F^{-1} = \frac{1}{n}\begin{pmatrix}
1 & 1 & 1 & \cdots & 1 \\
1 & \omega^{-1} & \omega^{-2} & \cdots & \omega^{-(n-1)} \\
1 & \omega^{-2} & \omega^{-4} & \cdots & \omega^{-2(n-1)} \\
\vdots & \vdots & \vdots & \ddots & \vdots \\
1 & \omega^{-(n-1)} & \omega^{-2(n-1)} & \cdots & \omega^{-(n-1)^2}
\end{pmatrix}.
$$

The inverse transform is therefore:

$$
a_j = \frac{1}{n} \sum_{k=0}^{n-1} y_k \cdot \omega^{-jk}.
$$

In other words, $\text{DFT}^{-1}(y) = \tfrac{1}{n}\,\text{DFT}^{\ast}(y)$, where $\text{DFT}^{\ast}$ is simply $\text{DFT}$ with $\omega$ replaced by $\omega^{-1}$.

### Finding $\omega$ in $\mathbb{Z}_p$

We need an algebraic structure where a primitive $n$-th root of unity exists.
We work modulo a prime $p$ such that $n \mid p - 1$.

By Fermat's little theorem, every element of $\mathbb{Z}_p^{\ast}$ satisfies $a^{p-1} \equiv 1$,
so $\left(g^{(p-1)/n}\right)^n \equiv 1$. If $g$ is a primitive root of $\mathbb{Z}_p^{\ast}$,
then $\omega = g^{(p-1)/n}$ has order exactly $n$, making it a primitive $n$-th root of unity.

Common choices that support $n$ up to large powers of $2$:

| $p$ | primitive root $g$ | largest supported $n$ |
|-----|-------------------|----------------------|
| $998244353 = 119 \cdot 2^{23} + 1$ | $3$ | $2^{23}$ |
| $985661441 = 235 \cdot 2^{22} + 1$ | $3$ | $2^{22}$ |
| $754974721 = 45 \cdot 2^{24} + 1$ | $11$ | $2^{24}$ |

### Complexity

Overall time complexity is $O(n \log n)$.

### Optimizations

**Iterative implementation.** The recursive formulation incurs $O(n)$ function call overhead and lots of memory allocations.
The straightforward recursive implementation follows directly from the Cooley-Tukey split:

```
ntt(a[0..n-1]):
    if n == 1: return

    A0 = a[0], a[2], a[4], ..., a[n-2]
    A1 = a[1], a[3], a[5], ..., a[n-1]

    ntt(A0), ntt(A1)

    wlen = g^((p-1)/n) mod p
    w = 1
    for j = 0..n/2-1:
        u = A0[j]
        v = A1[j] * w
        a[j]       = u + v
        a[j+n/2]   = u - v
        w *= wlen
```

Consider what this does for $n = 8$: it splits into even and odd indices,
then recurses on each half, and so on until reaching single elements:

![recursion tree](https://raw.githubusercontent.com/sqh926/sqalg/main/docs/ntt_bitrev.png)

The leaves — the order in which single elements are processed — are: $0, 4, 2, 6, 1, 5, 3, 7$.
Writing each in binary (3 bits) and reversing the bits:

| index $i$ | binary | reversed | value |
|-----------|--------|----------|-------|
| 0 | 000 | 000 | 0 |
| 1 | 001 | 100 | 4 |
| 2 | 010 | 010 | 2 |
| 3 | 011 | 110 | 6 |
| 4 | 100 | 001 | 1 |
| 5 | 101 | 101 | 5 |
| 6 | 110 | 011 | 3 |
| 7 | 111 | 111 | 7 |

Element originally at index $i$ ends up at position $\text{bit\_reverse}(i)$.
After this reordering, single-element subarrays are trivially done (base case $n=1$).
Now consider how to assemble the final answer from the two half-results.
Suppose positions $0\ldots3$ already hold $\text{DFT}$ of the even coefficients $[a_0, a_2, a_4, a_6]$,
and positions $4\ldots7$ hold $\text{DFT}$ of the odd coefficients $[a_1, a_3, a_5, a_7]$.
The formula for $i = 0, 1, 2, 3$ gives:

$$
a[i] \leftarrow a[i] + \omega^i \cdot a[i+4], \qquad a[i+4] \leftarrow a[i] - \omega^i \cdot a[i+4].
$$

This is exactly one pass with $\text{len} = 8$ over the array.
The same logic applies at every level — combining size-1 into size-2, size-2 into size-4, and so on —
so iterating $\text{len} = 2, 4, \ldots, n$ bottom-up covers all levels, giving the following implementation:

```
ntt(a[0..n-1], invert):
    for i in 0..n-1:
        j = bit_reverse(i)
        if i < j: swap(a[i], a[j]) // to not swap the same elements 2 times

    for len = 2, 4, ..., n:
        wlen = g^((p-1)/len) mod p
        for i = 0, len, 2*len, ..., n-len:
            w = 1
            for j = 0..len/2-1:
                u = a[i+j]
                v = a[i+j+len/2] * w
                a[i+j]         = u + v
                a[i+j+len/2]   = u - v
                w *= wlen
```

**Precomputed roots.** In the inner loop `w *= wlen` computes a modular multiplication on every step.
The naive fix — precompute $\text{rt}[j] = \omega^j$ and access $\text{rt}[j \cdot n/\text{len}]$ at level $\text{len}$ —
introduces cache misses: for small $\text{len}$ the stride $n/\text{len}$ is large,
so accesses jump far apart in memory.

Instead, build $\text{rt}$ so that level $\text{len}$ reads a contiguous block.
The needed powers at level $\text{len}$ are $\omega^{j \cdot n/\text{len}}$ for $j = 0, \ldots, \text{len}/2 - 1$.
Store them at positions $\text{len}/2, \ldots, \text{len} - 1$:

```
rt[n/2] = 1
for i in 1..n/2-1:       rt[n/2 + i] = rt[n/2 + i - 1] * g
for i in n/2-1 downto 1: rt[i] = rt[2*i]
```

The second loop propagates values down via $\text{rt}[i] = \text{rt}[2i]$.
At level $\text{len}$, the needed power for position $j$ is then `rt[j + len/2]` —
a contiguous read from a block of size $\text{len}/2$ that fits in cache.