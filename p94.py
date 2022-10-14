from multiprocessing import Pool
from math import ceil, isqrt

UPPER = 10 ** 9

def is_square_number(n):
    n_sqrt = isqrt(n)
    return n_sqrt * n_sqrt == n

def has_integral_area(x, dx):
    """
    Heron's formula:
    
    a = x, b = x, c = x + dx
    16 * area^2 = (a + b + c)(-a + b + c)(a - b + c)(a + b - c)
                = -dx^4 - 4x * dx^3 - 2(x * dx)^2 + 4 * dx * x^3 + 3 * x^4
    """
    rhs = -pow(dx, 4) - 4 * x * pow(dx, 3) - 2 * pow(dx * x, 2) + 4 * dx * pow(x, 3) + 3 * pow(x, 4)
    return is_square_number(rhs) and isqrt(rhs) % 4 == 0

def almost_equilateral_triangle_check(x, upper_bound):
    perimeter_sum = 0
    for dx in [-1, 1]:
        p = 3 * x + dx
        if has_integral_area(x, dx) and p <= upper_bound:
            perimeter_sum += p

    return perimeter_sum

def f(x):
    return almost_equilateral_triangle_check(x, UPPER)


upper = ceil(1 + UPPER / 3) + 1
total = 0

with Pool() as p:
    for perimeter_sum in p.imap_unordered(f, range(2, upper + 1), chunksize = 2 ** 16):
        total += perimeter_sum

print(total)