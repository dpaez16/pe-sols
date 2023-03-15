from functools import lru_cache

@lru_cache(maxsize=None)
def mat_mult(n):
    if n <= 1:
        return [[1, 1], [1, 0]]

    a = mat_mult(n // 2)
    b = mat_mult(n - n // 2)
    c = [[0, 0], [0, 0]]

    for i in range(2):
        for j in range(2):
            for k in range(2):
                c[i][j] += a[i][k] * b[k][j]

    return c

def f_bin(n):
    m = mat_mult(n - 1)
    return m[1][0] + m[1][1]

def is_pandigital(n):
    nums = set()

    while n != 0:
        d = n % 10
        if d in nums or d == 0:
            return False

        nums.add(n % 10)
        n //= 10

    return len(nums) == 9

def pandigital_check(a, n):
    if not is_pandigital(a):
        return False

    v = f_bin(n)
    v = str(v)[:9]
    v = int(v)
    return is_pandigital(v)


a, b = 1, 1
n = 1
MOD = pow(10, 9)

while True:
    if pandigital_check(a, n):
        print(n)
        break

    a, b = b, a + b
    a %= MOD
    b %= MOD
    n += 1
