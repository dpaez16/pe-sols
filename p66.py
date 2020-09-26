from decimal import *
from math import sqrt, floor


getcontext().prec = 100
MAX_LIST_SIZE = 100
D = 1000
EPS = Decimal(1e-3)


def is_square(n):
    sqrt_n = floor(sqrt(n))
    return sqrt_n ** 2 == n

def get_cfe_sqrt_d(d):
    a = []
    x = Decimal(d) ** Decimal(0.5)

    for _ in range(MAX_LIST_SIZE):
        a.append(floor(x))
        x = x - Decimal(a[-1])
        
        if x < EPS:
            break
        
        x = Decimal(1) / x

    return a

def get_convergents(a):
    h, k = [], []

    h.append(a[0])
    k.append(1)

    h.append(a[1] * a[0] + 1)
    k.append(a[1])

    for i in range(2, len(a)):
        h.append(a[i] * h[i - 1] + h[i - 2])
        k.append(a[i] * k[i - 1] + k[i - 2])

    return h, k

def get_sol(h, k, d):
    for x, y in zip(h, k):
        lhs = Decimal(x) ** Decimal(2)
        rhs = Decimal(1) + Decimal(d) * (Decimal(y) ** Decimal(2))

        if lhs == rhs:
            return x, y

    return


def main():
    max_x, optimal_d = 0, 0

    for d in range(1, D + 1):
        if is_square(d):
            continue
        
        a = get_cfe_sqrt_d(d)
        h, k = get_convergents(a)
        x, y = get_sol(h, k, d)

        if x > max_x:
            max_x = x
            optimal_d = d

    print(optimal_d)
    return


if __name__ == "__main__":
    main()
