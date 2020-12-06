A_MIN = 3
A_MAX = 10 ** 3

N = 10 ** 4

def get_r(a):
    r_max = 0
    a_sq = a ** 2

    for n in range(N + 1):
        b1 = pow(a - 1, n, a_sq)
        b2 = pow(a + 1, n, a_sq)
        r = pow(b1 + b2, 1, a_sq)

        r_max = max(r_max, r)

    return r_max

rs = map(get_r, range(A_MIN, A_MAX + 1))
ans = sum(rs)

print(ans)

