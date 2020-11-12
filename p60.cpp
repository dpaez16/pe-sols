#include <bits/stdc++.h>

using namespace std;

#define N 5
#define UPPER_BOUND 3000

typedef unordered_map<int, unordered_set<int>> edge_map;
typedef struct {
    unordered_set<int> vertices;
    edge_map edges;
} graph;

bool is_prime(int n) {
	if (n == 1) return false;
	if (n == 2) return true;
	if (n % 2 == 0) return false;

	for (int d = 3; d <= floor(sqrt(n)); d++) {
		if (n % d == 0) return false;
	}

	return true;
}

void update_subgraph(int left_int, int right_int, edge_map & edges, graph & subgraph) {
    auto left_incoming_vertices = edges[right_int];
    
    if (left_incoming_vertices.find(left_int) == left_incoming_vertices.end()) {
        return;
    }

    subgraph.vertices.insert(left_int);
    subgraph.vertices.insert(right_int);
    
    int a = min(left_int, right_int);
    int b = max(left_int, right_int);
    subgraph.edges[a].insert(b);
    subgraph.edges[b].insert(a);
}

void iterate_through_splits(int p, unordered_set<int> & primes, edge_map & edges, graph & subgraph) {
    string p_str = to_string(p);

    for (unsigned idx = 0; idx + 1 < p_str.size(); idx++) {
        string left = p_str.substr(0, idx + 1);
        string right = p_str.substr(idx + 1);

        if (right[0] == '0') continue;

        int left_int = stoi(left);
        int right_int = stoi(right);

        if (primes.find(left_int) == primes.end()) continue;
        if (primes.find(right_int) == primes.end()) continue;

        // a -> b <==> ab forms prime
        edges[left_int].insert(right_int);

        update_subgraph(left_int, right_int, edges, subgraph);
    }
}

void remove_vertex(int v, graph & g) {
    auto neighbors = g.edges[v];
    for (int neighbor : neighbors) {
        g.edges[neighbor].erase(v);
        g.edges[v].erase(neighbor);
    }

    g.vertices.erase(v);
    g.edges.erase(v);
}

bool is_clique(unordered_set<int> & subset, graph & g) {
    for (int v : subset) {
        auto neighbors = g.edges[v];
        for (int u : subset) {
            if (u == v) continue;
            if (neighbors.find(u) == neighbors.end()) return false;
        }
    }

    return true;
}

int find_subset_sum(graph g) {
    vector<int> vertices(g.vertices.begin(), g.vertices.end());
    sort(vertices.begin(), vertices.end());
    reverse(vertices.begin(), vertices.end());

    for (int v : vertices) {
        auto neighbors = g.edges[v];

        if (neighbors.size() >= (N - 1)) continue;

        remove_vertex(v, g);
    }

    vector<int> reduced_vertices(g.vertices.begin(), g.vertices.end());
    sort(reduced_vertices.begin(), reduced_vertices.end());
    unsigned n = reduced_vertices.size();

    for (unsigned i = 0; i < n; i++) {
        for (unsigned j = i + 1; j < n; j++) {
            for (unsigned k = j + 1; k < n; k++) {
                for (unsigned l = k + 1; l < n; l++) {
                    for (unsigned m = l + 1; m < n; m++) {
                        unordered_set<int> subset = {
                            reduced_vertices[i],
                            reduced_vertices[j],
                            reduced_vertices[k],
                            reduced_vertices[l],
                            reduced_vertices[m]
                        };
                        
                        if (!is_clique(subset, g)) continue;

                        int sum = 0;
                        for (int v : subset) {
                            cout << v << ' ';
                            sum += v;
                        }

                        cout << endl;
                        return sum;
                    }
                }
            }
        }
    }

    return 0;
}

int main() {
    unordered_set<int> primes;
    edge_map edges;
    graph subgraph;

    int p = 0;
    while (subgraph.vertices.size() != UPPER_BOUND) {
        if (!is_prime(p)) {
            p++;
            continue;
        }

        primes.insert(p);
        edges[p] = unordered_set<int>();
        iterate_through_splits(p, primes, edges, subgraph);

        p++;
    }

    cout << p << endl;
    int sum = find_subset_sum(subgraph);
    cout << sum << endl;

    return 0;
}