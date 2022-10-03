from multiprocessing import Pool
from math import isqrt

LOWER_BOUND = isqrt(1020304050607080900)
UPPER_BOUND = isqrt(1929394959697989990)

def f(n):
    n_sq = n * n
    n_sq //= 10

    for i in range(9, 0, -1):
        n_sq //= 10
        if n_sq % 10 != i:
            return None

        n_sq //= 10

    return n

with Pool(processes=None) as p:
    for elem in p.imap_unordered(f, range(LOWER_BOUND, UPPER_BOUND + 1, 10), chunksize=2 ** 16):
        if elem is not None:
            print(elem)