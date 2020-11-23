from math import factorial as f

UPPER_BOUND = 10 ** 6
N_TERMS = 60


def chain_length(n, chain_length_map):
    past_nums = list()
    past_nums_set = set()
    curr = n

    while curr not in past_nums_set and curr not in chain_length_map:
        past_nums.append(curr)
        past_nums_set.add(curr)
        curr = sum(map(lambda x: f(int(x)), str(curr)))

    if curr in chain_length_map:
        length = chain_length_map[curr]
    
        for idx in range(len(past_nums)):
            chain_length_map[past_nums[len(past_nums) - idx - 1]] = length + idx + 1

        return chain_length_map[n]

    curr_idx = past_nums.index(curr)
    length = len(past_nums) - curr_idx
    
    for idx in range(curr_idx):
        chain_length_map[past_nums[curr_idx - idx - 1]] = length + idx + 1

    for idx in range(curr_idx, len(past_nums)):
        chain_length_map[past_nums[idx]] = length

    return chain_length_map[n]


count = 0
chain_length_map = {}
for n in range(UPPER_BOUND):
    chain_len = chain_length(n, chain_length_map)

    if chain_len == N_TERMS:
        count += 1

print(count)
