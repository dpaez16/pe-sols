DIVISOR = 10 ** 6

def partition(n):
    s = 0
    
    k = 1
    while True:
        idx = n - k * (3 * k - 1) // 2

        if idx < 0: break
        
        term = p[idx] * (-1) ** (k + 1)
        s += term
        k += 1

    k = -1
    while True:
        idx = n - k * (3 * k - 1) // 2

        if idx < 0: break
        
        term = p[idx] * (-1) ** (k + 1)
        s += term
        k -= 1

    return s

p = [1]
n = 0

while p[n] % DIVISOR != 0:
    n += 1
    x = partition(n) % DIVISOR
    p.append(x)


print(n)