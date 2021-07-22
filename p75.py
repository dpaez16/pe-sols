L = int(1.5 * 10 ** 6)

def getTriplets(limit):
    triples = set()
    c, m = 0, 2
    
    while c <= limit:
        for n in range(1, m):
            a = m ** 2 - n ** 2
            b = 2 * m * n
            c = m ** 2 + n ** 2
            
            orig = sorted([a, b, c])
            
            k = 1
            while True:
                triple = tuple([k * num for num in orig])
                if sum(triple) > limit:
                    break

                triples.add(triple)
                k += 1

        m = m + 1

    return triples

triples = getTriplets(L)

counts = [0] * (L + 1)
for triple in triples:
    idx = sum(triple)
    if idx >= len(counts):
        continue

    counts[idx] += 1

ans = sum([c == 1 for c in counts])
print(ans)
