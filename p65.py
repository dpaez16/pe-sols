CONVERGENT_LENGTH = 100
terms = [1, 1, 2]

class Fraction:
    def __init__(self, n, d):
        self.n = n
        self.d = d

    def flip(self):
        self.n, self.d = self.d, self.n

    def __add__(self, other):
        return Fraction(
            self.n * other.d + other.n * self.d,
            self.d * other.d
        )

    def __repr__(self):
        return f"{self.n}/{self.d}"

def helper(i, end, idx):
    if i == end:
        return Fraction(0, 1)

    num = terms[idx]
    if idx + 1 == len(terms):
        terms[idx] += 2

    bottom = Fraction(num, 1) + helper(i + 1, end, (idx + 1) % len(terms))
    bottom.flip()
    return bottom

f = Fraction(2, 1) + helper(1, CONVERGENT_LENGTH, 1)
top = f.n
s = 0

while top > 0:
    s += top % 10
    top = top // 10

print(s)
