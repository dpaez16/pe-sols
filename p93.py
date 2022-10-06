from itertools import combinations, product, permutations


class Fraction:
    def __init__(self, x, y = 1):
        self.numerator = x
        self.denominator = y

    def __add__(self, rhs):
        if self.denominator == rhs.denominator:
            return Fraction(self.numerator + rhs.numerator, self.denominator)
        
        return Fraction(
            self.numerator * rhs.denominator + rhs.numerator * self.denominator,
            self.denominator * rhs.denominator
        )
    
    def __sub__(self, rhs):
        if self.denominator == rhs.denominator:
            return Fraction(self.numerator - rhs.numerator, self.denominator)
        
        return Fraction(
            self.numerator * rhs.denominator - rhs.numerator * self.denominator,
            self.denominator * rhs.denominator
        )
    
    def __mul__(self, rhs):
        return Fraction(
            self.numerator * rhs.numerator,
            self.denominator * rhs.denominator
        )
    
    def __truediv__(self, rhs):
        return Fraction(
            self.numerator * rhs.denominator,
            self.denominator * rhs.numerator
        )
    
    def to_int(self):
        if self.denominator == 0:
            return 0
        if self.numerator % self.denominator == 0:
            return self.numerator // self.denominator
        
        return 0

ops = [
    lambda x, y: x + y,
    lambda x, y: x - y,
    lambda x, y: x * y,
    lambda x, y: x / y
]

def process(perm, op_perm):
    x = perm[0]
    for i in range(1, len(perm)):
        op = op_perm[i - 1]
        y = perm[i]
        x = op(x, y)

    return x.to_int()

def process2(perm, op_perm):
    x = op_perm[1](perm[1], perm[2])
    x = op_perm[0](perm[0], x)
    x = op_perm[2](x, perm[3])
    
    return x.to_int()

def process3(perm, op_perm):
    x = op_perm[1](perm[1], perm[2])
    x = op_perm[2](x, perm[3])
    x = op_perm[0](perm[0], x)
    
    return x.to_int()

def gen_results(nums):
    results = set()
    for perm in permutations(nums):
        for op_perm in product(ops, repeat = len(perm) - 1):
            result = process(perm, op_perm)
            result2 = process2(perm, op_perm)
            result3 = process3(perm, op_perm)
            results.add(result)
            results.add(result2)
            results.add(result3)

    return results

def get_largest_run(results):
    i = 1
    while i in results:
        i += 1

    return i - 1


N = 9
num_set_perm = combinations(range(1, N + 1), 4)
largest_run = 0
num_set = None

for perm in num_set_perm:
    run = get_largest_run(gen_results(Fraction(x) for x in perm))
    if run > largest_run:
        largest_run = run
        num_set = perm

print("".join(map(str, num_set)))