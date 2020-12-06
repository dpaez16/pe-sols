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
    if p * p > MOD:
        idx = n
        break

primes = primes[idx:]
for n, p in enumerate(primes):
    n += idx + 1

    p_sq = p * p
    b1 = pow(p - 1, n, p_sq)
    b2 = pow(p + 1, n, p_sq)
    r = pow(b1 + b2, 1, p_sq)

    if r > UPPER_BOUND:
        print(n)
        break

