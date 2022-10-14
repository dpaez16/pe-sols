from itertools import product, combinations
from multiprocessing import Pool
from math import comb

class Cube:
    def __init__(self, digits):
        self.digits = sorted([d for d in digits])
        self.unique_digits = set([d for d in digits])
        
        if 6 in self.unique_digits:
            self.unique_digits.add(9)
        if 9 in self.unique_digits:
            self.unique_digits.add(6)

    def __contains__(self, n):
        return n in self.unique_digits
    
    def __str__(self):
        digits_ = [d for d in self.digits]
        if 6 in digits_ and 9 not in digits_:
            digits_.append(9)
        if 9 in digits_ and 6 not in digits_:
            digits_.append(9)
        
        return str(sorted(digits_))

class CubePair:
    def __init__(self, left_digits, right_digits):
        self.left_cube = Cube(left_digits)
        self.right_cube = Cube(right_digits)

    def has_square_nums(self):
        for n in range(1, 10):
            if pow(n, 2) not in self:
                return False

        return True

    def __contains__(self, n):
        a = n // 10
        b = n % 10
        
        return (
            a in self.left_cube and b in self.right_cube or
            b in self.left_cube and a in self.right_cube
        )
    
    def __str__(self):
        return f"{self.left_cube}{self.right_cube}"

def check_cube_config(nums):
    left = nums[0]
    right = nums[1]
    
    cubePair = CubePair(left, right)
    if not cubePair.has_square_nums():
        return None
    
    return str(cubePair)


arrangements_set = set()

prod = product(combinations(range(10), 6), repeat = 2)
n_iters = comb(10, 6) ** 2
for nums in prod:
    arrangement = check_cube_config(nums)
    if arrangement is not None:
        arrangements_set.add(arrangement)

ans = len(arrangements_set) // 2
print(ans)