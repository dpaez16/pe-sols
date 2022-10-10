from math import log2, ceil

UPPER = 800800 * log2(800800)
N = ceil(UPPER)

def search(a, x, lo, hi, key):
    orig_hi = hi
    while lo <= hi:
        mid = lo + (hi - lo) // 2
        mid_val = key(a[mid])
        if mid_val == x:
            return mid
        elif mid_val < x:
            lo = mid + 1
        else:
            hi = mid - 1

    return hi

def sieve(n):
    is_prime = [True] * (n + 1)
    is_prime[0] = False
    is_prime[1] = False
    
    primes = []
    
    for p in range(len(is_prime)):
        if not is_prime[p]:
            continue

        primes.append(p)
        for k in range(2 * p, len(is_prime), p):
            is_prime[k] = False
    
    return primes


primes = sieve(N)

count = 0
upper = len(primes) - 1
for i in range(len(primes)):
    p = primes[i]
    j = search(primes, UPPER, i, upper, key = lambda q: q * log2(p) + p * log2(q))
    
    if i <= j:
        n = j - i
        count += n
        upper = j + 1

print(count)