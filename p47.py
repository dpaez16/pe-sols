N = 1000
N_DIGITS = 10

last_n_digits = sum([i ** i for i in range(1, N + 1)]) % 10 ** N_DIGITS
print(last_n_digits)