---
title: Integer Factorization (Pollard's Rho)
documentation_of: ../src/number_theory/factorize.hpp
---

## Pollard's Rho Algorithm

**Reference:** [Wikipedia — Pollard's rho algorithm](https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm)

Given a composite integer $n$, we want to find a non-trivial divisor $1 < g < n$.

### Main Idea

Suppose $p$ is a prime factor of $n$.
Consider a sequence of random integers $x_1, x_2, \ldots \in \mathbb{Z}_n$.
By the birthday paradox, after roughly $O(\sqrt{p})$ elements we expect a collision modulo $p$:
two indices $i \neq j$ such that $x_i \equiv x_j \pmod{p}$.
Then $p \mid x_i - x_j$ but likely $n \nmid x_i - x_j$,
so $1 < \gcd(x_i - x_j, n) < n$ gives a non-trivial factor.

Instead of generating truly random sequence (which would require $O(\sqrt{p})$ memory to detect a collision),
Pollard replaced them with the pseudorandom recurrence

$$
x_{i+1} = x_i^2 + c \pmod{n}
$$

### Cycle Detection (Floyd's Algorithm)

The sequence $x_0, x_1, x_2, \ldots$ reduced modulo $p$ is eventually periodic:
there is some number of elements in the sequence before we cycle, call it $\mu$ and a cycle length, call it $\lambda$ such that

$$
x_i \equiv x_j \pmod{p} \iff i, j \geq \mu \text{ and } \lambda \mid i - j.
$$

Both $\mu$ and $\lambda$ are $O(\sqrt{p})$ by the birthday paradox.

Floyd's two-pointer method detects this cycle with $O(1)$ extra memory.
Maintain a slow pointer $a = x_i$ and a fast pointer $b = x_{2i}$.
After $i$ iterations, the pointers are at positions $i$ and $2i$ in the sequence.

**Claim.** The pointers meet modulo $p$ (i.e. $p \mid a - b$) after at most $\mu + \lambda$ iterations.

**Proof.**
Once $i \geq \mu$, both positions $i$ and $2i$ lie inside the cycle.
Two positions inside the cycle give equal elements exactly when
the distance between their indices is divisible by $\lambda$, i.e. $\lambda \mid 2i - i = i$.

So we need the smallest $i \geq \mu$ with $\lambda \mid i$, which is $\lambda \lceil \mu / \lambda \rceil$.
Since $\lceil \mu / \lambda \rceil \leq \mu / \lambda + 1$, we get $\lambda \lceil \mu / \lambda \rceil \leq \mu + \lambda$.
Both $\mu$ and $\lambda$ are $O(\sqrt{p})$, so the pointers meet after $O(\sqrt{p})$ iterations.

When they meet we have $p \mid x_{2i} - x_i = b - a$, so $\gcd(|a - b|, n)$ gives a non-trivial factor.

If $\gcd$ returns $n$, the chosen $c$ was unlucky.
In that case restart the algorithm with new $c$.

### Batch GCD Optimization

Computing $\gcd$ every iteration is expensive.
Instead, accumulate the product

$$
q = \prod_{i=1}^{B} |a_i - b_i| \pmod{n}
$$

over a batch of $B$ steps, then compute a single $\gcd(q, n)$.
This works because $p \mid |a_i - b_i|$ for some $i$ implies $p \mid q$.
If the batch returns $\gcd = n$ (a collision was missed because all terms became $0 \pmod{p}$),
fall back to the saved state at the start of the batch.
In practice this cuts the running time by roughly $9$ times compared to computing $\gcd$ every step.

After some testing $B = 1024$ seemed to be the optimal choice.

### Complexity

For a composite $n$ with smallest prime factor $p$,
`get_divisor` finds a factor in expected $O(\sqrt{p} \cdot \log n)$ time and $O(1)$ space.
Since $p \leq \sqrt{n}$, the worst case is $O(n^{1/4} \log n)$.

Full factorization `factorize(n)` calls `get_divisor` recursively.
Since each call finds at least one prime factor, there are at most $O(\log n)$ calls in total,
giving an overall expected complexity of $O(n^{1/4} \log^2 n)$.
In practice, 100 numbers up to $10^{18}$ can be factored in roughly 40 ms.
