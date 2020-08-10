from math import factorial
N = 100

n_factorial_str = str(factorial(N))
sum_digits = sum(map(int, n_factorial_str))

print(sum_digits)
