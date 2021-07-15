from math import floor, sqrt
from collections import defaultdict

N = 10 ** 6

def gen_primes(n):
    is_prime = [True] * (n + 1)
    is_prime[0] = False
    is_prime[1] = False

    for i in range(n + 1):
        if not is_prime[i]:
            continue

        for j in range(i * 2, n + 1, i):
            is_prime[j] = False

    return is_prime

def prime_factorization(n):
    assert n >= 0
    
    factors = defaultdict(lambda: 0)
    if n <= 1:
        return factors
    
    while n % 2 == 0:
        factors[2] += 1
        n = n // 2

    end = floor(sqrt(n))
    for factor in range(3, end+1, 2):
        while n % factor == 0:
            factors[factor] += 1
            n = n // factor
    
    if n > 2:
        factors[n] += 1

    return factors

def phi(n, is_prime):
    if is_prime:
        return n - 1

    prime_fact = prime_factorization(n)
    ans = 1
    for p in prime_fact:
        k = prime_fact[p]
        ans *= (p ** (k - 1)) * (p - 1)

    return ans

is_prime = gen_primes(N)
best = 0
best_n = 0

for p in range(2, len(is_prime)):
    curr = p / phi(p, is_prime[p])
    if curr > best:
        best = curr
        best_n = p

print(best_n)
