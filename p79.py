from collections import defaultdict

FILE_PATH = "files/p079_keylog.txt"


def dfs(u, visited, edgeMap, acc, pathLength, end):
    visited.add(u)
    
    if u == end:
        if len(visited) == pathLength:
            print("".join(acc))
        return
    
    for v in edgeMap[u]:
        if v not in visited:
            visited.add(v)
            acc.append(v)

            dfs(v, visited, edgeMap, acc, pathLength, end)
            
            visited.remove(v)
            acc.pop()

def getGraph():
    edgeMap = defaultdict(set)
    vertices = set()

    with open(FILE_PATH, 'r') as f:
        for line in f:
            line = line.strip()

            for i in range(len(line)):
                vertices.add(line[i])

                for j in range(i + 1, len(line)):
                    edgeMap[line[i]].add(line[j])

    return vertices, edgeMap

def getSource(vertices, edgeMap):
    isSource = {v: True for v in vertices}
    for u in vertices:
        for v in edgeMap[u]:
            isSource[v] = False

    return [v for v in vertices if isSource[v]][0]

def getSink(vertices, edgeMap):
    return [v for v in vertices if len(edgeMap[v]) == 0][0]

vertices, edgeMap = getGraph()
start = getSource(vertices, edgeMap)
end = getSink(vertices, edgeMap)


dfs(start, set(), edgeMap, [start], len(vertices), end)