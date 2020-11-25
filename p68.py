from itertools import product
from collections import defaultdict, deque
from copy import deepcopy

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

def get_sols(triples_group, triples_map):
    sols = []

    for start in triples_group:
        queue = deque([(start, set(), list())])

        while len(queue) != 0:
            curr, visited, sol = queue.popleft()

            if curr in visited or len(sol) > N:
                continue

            visited.add(curr)
            sol.append(curr)

            if len(sol) == N:
                if is_valid(sol): 
                    sol_c = convert_sol(sol)
                    sols.append(sol_c)

                continue
            
            _, _, c = curr
            neighbors = triples_group.intersection(triples_map[c])

            for neighbor in neighbors:
                if neighbor == curr or neighbor[0] <= sol[0][0]:
                    continue
 
                visited_copy = deepcopy(visited)
                sol_copy = deepcopy(sol)

                queue.append((neighbor, visited_copy, sol_copy))

    return sols

triples = get_triples()
triples_sum_map = defaultdict(set)
triples_map = defaultdict(set)

for triple in triples:
    _, b, _ = triple
    s = sum(triple)
    triples_sum_map[s].add(triple)
    triples_map[b].add(triple)

max_sol = ""

for s in triples_sum_map:
    triples_group = triples_sum_map[s]

    if len(triples_group) < N:
        continue

    sols = get_sols(triples_group, triples_map)

    if len(sols) == 0:
        continue

    max_sol = max(max_sol, max(sols))

print(max_sol)
