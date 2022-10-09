from functools import lru_cache

def u(n):
    return sum(pow(-1, i) * pow(n, i) for i in range(10 + 1))

# https://en.wikipedia.org/wiki/Neville%27s_algorithm
def p(x, xs, ys):
    @lru_cache(maxsize=None)
    def helper(i, j):
        if i == j:
            return ys[i]
        
        top = (x - xs[i]) * helper(i + 1, j) + (xs[j] - x) * helper(i, j - 1)
        bottom = xs[j] - xs[i]
        return top / bottom
    
    return helper(0, len(xs) - 1)

def bop(k):
    xs = [x for x in range(1, k + 1)]
    ys = [u(x) for x in xs]
    
    return p(k + 1, xs, ys)

N = 10
s = sum(bop(k) for k in range(1, N + 1))
s = int(s)

print(s)