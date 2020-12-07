A_MIN = 3
A_MAX = 10 ** 3

N = 10 ** 4

def get_r(a):
    a_sq = a ** 2
    r_max = 2 % a_sq

    for n in range(1, N + 1, 2):
        num = 2 * n * a
        r = num % a_sq
        r_max = max(r_max, r)

    return r_max

rs = map(get_r, range(A_MIN, A_MAX + 1))
ans = sum(rs)

print(ans)

