from decimal import *

N_DIGITS    = 100
N_NAT_NUMS  = 100
getcontext().prec = N_DIGITS * 2

def get_digital_sum(d):
    d_sqrt = Decimal(d).sqrt()
    d_sqrt_str = str(d_sqrt)
    s = 0
    count = 0

    for i in range(len(d_sqrt_str)):
        if count == N_DIGITS:
            break
        if d_sqrt_str[i] == '.':
            continue

        s += int(d_sqrt_str[i])
        count += 1

    return s

def is_square(n):
    return Decimal(n).sqrt().__floor__() ** 2 == Decimal(n)

total = 0
for i in range(1, N_NAT_NUMS + 1):
    if is_square(i):
        continue

    total += get_digital_sum(i)

print(total)
