from collections import defaultdict
from math import floor, sqrt

N = 100000
K = 10000

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

def rad(n):
    prime_facts = prime_factorization(n)
    ans = 1
    
    for p in prime_facts:
        ans *= p

    return ans

nums = range(1, N + 1)
pairs = list(zip(nums, map(rad, nums)))

pairs.sort(key=lambda p: p[1])
print(pairs[K - 1][0])
