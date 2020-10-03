from decimal import *
from math import floor, ceil
from tqdm import tqdm


getcontext().prec = 1000
MAX_LIST_SIZE = 1000
N = 10000


def sqrt(n):
    return Decimal(n) ** Decimal(0.5)

def get_cfe(n):
    cfe = []
    EPS = Decimal(1e-3)

    for _ in range(MAX_LIST_SIZE):
        cfe.append(floor(n))
        n -= Decimal(cfe[-1])
        
        if n < EPS:
            break
        
        n = Decimal(1.0) / n

    return cfe

def period_length_check(period_length, digits):
    num_matches = 0
    num_slices = ceil(len(digits) / period_length)
    slices = [digits[i*period_length:(i+1)*period_length] for i in range(num_slices)]

    for i in range(1, len(slices)):
        if slices[i-1] != slices[i]:
            break

        num_matches += 1

    return num_matches, num_slices

def get_period_length(cfe):
    if len(cfe) == 1:
        return 0
    
    digits = cfe[1:]
    matches = []

    for period_length in range(1, len(digits)):
        num_matches, num_slices = period_length_check(period_length, digits)

        if num_matches == num_slices:
            return period_length

        matches.append([period_length, num_matches])

    period_length, _ = max(matches, key=lambda x: x[1])
    return period_length


def main():
    count = 0
    max_period_length = 0

    for num in tqdm(range(1, N + 1)):
        n = sqrt(num)
        cfe = get_cfe(n)
        period_length = get_period_length(cfe)
        max_period_length = max(max_period_length, period_length)

        if period_length % 2 == 1:
            count += 1

    print(count == 1322)
    print(max_period_length)
    return


if __name__ == "__main__":
    main()
