MOD = 10 ** 9 + 7
N = 90

def get_a_coeff(n):
    # coefficient is of the form: 5 * 10^(n - 1)
    return (5 * pow(10, n - 1, MOD)) % MOD

def get_b_coeff(n):
    # coefficient is of the form: (14 * 10^(n - 1)) + (10^(n - 1) - 1)

    a = (14 * pow(10, n - 1, MOD)) % MOD
    b = (pow(10, n - 1, MOD) - 1) % MOD
    return (a + b) % MOD

def get_c_coeff(n):
    # coefficient is of the form: (6 * 10^n) - (9n + 6)

    a = (6 * pow(10, n, MOD)) % MOD
    b = (9 * n + 6) % MOD
    return (a - b) % MOD

def get_func(k):
    if k < 9:
        return lambda x: x * (x + 1) // 2
    
    n = k // 9
    
    # we form a quadratic: ax^2 + bx + c
    a = get_a_coeff(n)
    b = get_b_coeff(n)
    c = get_c_coeff(n)
    
    return lambda x: (((a * pow(x, 2, MOD)) % MOD) + ((b * (x % MOD)) % MOD) + c) % MOD

def get_fib_nums(n):
    a, b = 0, 1
    for _ in range(2, n + 1):
        yield a + b
        a, b = b, a + b

total = 0

for f_n in get_fib_nums(N):
    f = get_func(f_n)
    total += f(f_n % 9)
    total %= MOD

print(total)