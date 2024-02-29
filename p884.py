from math import floor

N = pow(10, 17)

def largest_fitting_cube(n):
    cube_root_n = floor(pow(n, 1 / 3))

    while pow(cube_root_n, 3) <= n:
        cube_root_n += 1

    return pow(cube_root_n - 1, 3)

def is_cube(n):
    return largest_fitting_cube(n) == n

def d(n):
    if n < 8:
        return n

    count = 0
    while n > 0:
        n -= largest_fitting_cube(n)
        count += 1

    return count

def s(n):
    return sum(d(k) for k in range(n))

def f(n, memo):
    if n in memo:
        return memo[n]
    elif n <= 64:
        memo[n] = s(n)
        return memo[n]

    l = largest_fitting_cube(n - 1) if is_cube(n) else largest_fitting_cube(n)

    a = memo[l] if l in memo else f(l, memo)
    b = memo[n - l] if (n - l) in memo else f(n - l, memo)

    memo[n] = a + b + (n - l)
    return memo[n]

def solve(n):
    max_base = 0

    while pow(max_base, 3) < n:
        max_base += 1

    max_base -= 1
    memo = {}

    for k in range(max_base + 1):
        f(pow(k, 3), memo)

    return f(n, memo)

ans = solve(N)
print(ans)