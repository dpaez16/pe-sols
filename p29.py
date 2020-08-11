LOWER_POW = 2
UPPER_POW = 100

distinct_nums = set()
for a in range(LOWER_POW, UPPER_POW + 1):
    for b in range(LOWER_POW, UPPER_POW + 1):
        distinct_nums.add(a ** b)

print(len(distinct_nums))