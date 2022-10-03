from multiprocessing import Pool
from math import isqrt

N = 10 ** 12

def helper(i, s, k, n, digits):
    if i == len(digits):
        if k < 2:
            return False
        return s == n

    for idx in range(i, len(digits)):
        num = int(''.join(digits[i:idx + 1]))
        if helper(idx + 1, s + num, k + 1, n, digits):
            return True

    return False

def is_s_number(n, sqrt_n):
    digits = str(n)
    if len(digits) == 1:
        return False

    return helper(0, 0, 0, sqrt_n, digits)

def f(n):
    n_sq = n * n
    if n % 9 <= 1 and is_s_number(n_sq, n):
        return n_sq

    return 0

total = 0
with Pool(processes=None) as p:
    for elem in p.imap_unordered(f, range(isqrt(N) + 1), chunksize=2 ** 8):
        total += elem

print(total)