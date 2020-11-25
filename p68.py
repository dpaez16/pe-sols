from itertools import product
from collections import defaultdict

N = 5


def get_triples():
    triples = []
    upper_limit = 2 * N

    for a in range(1, upper_limit + 1):
        for b in range(1, upper_limit + 1):
            for c in range(1, upper_limit + 1):
                if a == b or b == c or a == c:
                    continue

                triple = (a, b, c)
                triples.append(triple)

    return triples

def is_valid(selection):
    a, b, c = selection[0]
    s = set([a, b, c])
    total = a + b + c
    
    if selection[-1][-1] != b:
        return False

    min_ext_node = min(selection, key=lambda t: t[0])
    
    if min_ext_node != selection[0]:
        return False

    for triple in selection[1:]:
        if triple[1] != c:
            return False

        if triple != selection[-1] and (triple[0] in s or triple[-1] in s):
            return False

        if triple == selection[-1] and triple[0] in s:
            return False

        if sum(list(triple)) != total:
            return False

        s = s.union(set(triple))
        a, b, c = triple

    return True

def convert_sol(sol):
    sol = map(lambda t: "".join(map(str, t)), sol)
    sol = "".join(sol)
    return sol


triples = get_triples()
triples_sum_map = defaultdict(list)

for triple in triples:
    s = sum(triple)
    triples_sum_map[s].append(triple)

max_sol = ""

for s in triples_sum_map:
    triples_group = triples_sum_map[s]

    if len(triples_group) < N:
        continue

    selections = [triples_group] * N
    selections = product(*selections)

    for selection in selections:
        if is_valid(selection):
            sol = convert_sol(selection)
            max_sol = max(max_sol, sol)

print(max_sol)

