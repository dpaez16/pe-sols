from math import floor
from decimal import *

N_DIGITS = 24
getcontext().prec = N_DIGITS + 1

def gen_seq(theta, n):
    a = [floor(theta)]
    b = [theta]
    
    for i in range(n):
        next_b = floor(b[i]) * (b[i] - floor(b[i]) + 1)
        b.append(next_b)
        a.append(floor(next_b))
    
    s = str(a[0]) + "." + "".join(map(str, a[1:]))
    return s

theta = "2."
for i in range(N_DIGITS):
    s = gen_seq(Decimal(theta), N_DIGITS)
    theta += s[2 + i]

print(theta)
