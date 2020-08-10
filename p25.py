N_DIGITS = 1000

idx = 3
f_n_m_2 = 1
f_n_m_1 = 1
f_n = None

while len(str(f_n)) != N_DIGITS:
    f_n = f_n_m_1 + f_n_m_2
    f_n_m_1, f_n_m_2 = f_n, f_n_m_1
    idx += 1

idx -= 1
print(idx)