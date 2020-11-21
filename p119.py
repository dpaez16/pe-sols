N = 30
BASE_MAX = 100
EXP_MAX = 100

a = set()
for base in range(2, BASE_MAX + 1):
    for exponent in range(2, EXP_MAX + 1):
        n = base ** exponent
        dsum = sum(map(int, str(n)))

        if dsum == base:
            a.add(n)

a = sorted(a)
print(a[N - 1])
