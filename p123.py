from math import ceil, sqrt

UPPER_BOUND = 10 ** 10
MOD = UPPER_BOUND * 10
N = ceil(sqrt(MOD))


def gen_primes(n):
    primes = []
    prime = [True] * (n + 1)
    prime[0] = False
    prime[1] = False

    for p in range(2, n + 1):
        if not prime[p]:
            continue

        primes.append(p % MOD)
        for k in range(2 * p, n + 1, p):
            prime[k] = False

    return primes

primes = gen_primes(N)

idx = 0
for n, p in enumerate(primes):
    if p ** 2 > (MOD // 2):
        idx = n
        break

primes = primes[idx:]
for n, p in enumerate(primes):
    n += idx + 1

    p_sq = p ** 2
    a1 = (p - 1) ** n
    a2 = (p + 1) ** n
    b1 = a1 % p_sq
    b2 = a2 % p_sq
    r = (b1 + b2) % p_sq

    if r > UPPER_BOUND:
        print(n)
        break

