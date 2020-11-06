#include <bits/stdc++.h>

using namespace std;

#define N 4

typedef unordered_map<int, set<int>> edge_map;
typedef struct {
    set<int> vertices;
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

int main() {
    unordered_set<int> primes;
    edge_map edges;
    graph subgraph;
    //int max_degree = N - 1;

    int p = 0;
    int n = 673109;
    while (p <= n) {
        if (!is_prime(p)) {
            p++;
            continue;
        }

        primes.insert(p);
        edges[p] = set<int>();
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

            auto left_incoming_vertices = edges[right_int];
            if (left_incoming_vertices.find(left_int) != left_incoming_vertices.end()) {
                subgraph.vertices.insert(left_int);
                subgraph.vertices.insert(right_int);
                
                subgraph.edges[left_int].insert(right_int);
                subgraph.edges[right_int].insert(left_int);
            }
        }

        p++;
    }

    return 0;
}