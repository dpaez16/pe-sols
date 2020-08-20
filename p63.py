N = 100

def num_digits(x):
    x_str = str(x)
    return len(x_str)

def n_digit_n_powers(n):
    x = 1
    count = 0

    while num_digits(x ** n) <= n:
        if num_digits(x ** n) == n: count += 1
        x += 1

    return count

count = 0
	
for n in range(1, N + 1):
    count += n_digit_n_powers(n)

print(count)
