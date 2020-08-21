#include <bits/stdc++.h>

using namespace std;

#define N 40
#define INFTY (unsigned)-1
#define FILE_PATH "files/p107_network.txt"
#define PAIR(r, c) pair<int, int>(r, c)


struct pair_hash {
	size_t operator() (const pair<int, int> & p) const {
		ostringstream out;
		out << p.first << ',' << p.second;
		return hash<string>()(out.str());
	}
};

void process_line(string & line, int r, unordered_map<pair<int, int>, unsigned, pair_hash> & edge_weights) {
	stringstream ss(line);
	string temp_str;
	int c = 0;
	
	while(getline(ss, temp_str, ',')) {
		if (temp_str == "-"  || c <= r) {
			c++;
			continue;
		};

		unsigned edge_weight = stoi(temp_str);
		edge_weights[PAIR(r, c)] = edge_weight;
		edge_weights[PAIR(c, r)] = edge_weight;

		c++;
	}
}

unordered_map<pair<int, int>, unsigned, pair_hash> process_file() {
	string line;
	ifstream file;
	file.open(FILE_PATH);

	unordered_map<pair<int, int>, unsigned, pair_hash> edge_weights;
	int r = 0;

	while (getline(file, line)) {
		process_line(line, r, edge_weights);
		r++;
	}

	file.close();
	return edge_weights;
}

unordered_set<int> get_vertices() {
	unordered_set<int> vertices;

	for (int i = 1; i < N; i++) {
		vertices.insert(i);
	}

	return vertices;
}

unsigned get_graph_weight(unordered_map<pair<int, int>, unsigned, pair_hash> & edge_weights) {
	unsigned graph_weight = 0;

	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			if (edge_weights.find(PAIR(i, j)) == edge_weights.end()) continue;

			graph_weight += edge_weights[PAIR(i, j)];
		}
	}

	return graph_weight;
}

pair<int, unsigned> get_next_vertex_and_weight(unordered_map<pair<int, int>, unsigned, pair_hash> & edge_weights, vector<int> & mst_vertices, unordered_set<int> & vertices) {
	unsigned min_edge_weight = INFTY;
	int optimal_adj_vertex = -1;	

	for (int vertex_a : mst_vertices) {
		for (int vertex_b : vertices) {
			if (edge_weights.find(PAIR(vertex_a, vertex_b)) == edge_weights.end()) continue;

			unsigned edge_weight = edge_weights[PAIR(vertex_a, vertex_b)];

			if (min_edge_weight > edge_weight) {
				min_edge_weight = edge_weight;
				optimal_adj_vertex = vertex_b;
			}
		}
	}

	pair<int, unsigned> next_vertex_and_weight(optimal_adj_vertex, min_edge_weight);
	return next_vertex_and_weight;
}


int main() {
	unordered_map<pair<int, int>, unsigned, pair_hash> edge_weights = process_file();
	vector<int> mst_vertices = {0};
	unordered_set<int> vertices = get_vertices();
	unsigned mst_total = 0;

	while (mst_vertices.size() != N) {
		pair<int, unsigned> next_step = get_next_vertex_and_weight(edge_weights, mst_vertices, vertices);
		int optimal_adj_vertex = next_step.first;
		unsigned min_edge_weight = next_step.second;

		mst_vertices.push_back(optimal_adj_vertex);
		vertices.erase(optimal_adj_vertex);

		mst_total += min_edge_weight;
	}

	unsigned total_graph_weight = get_graph_weight(edge_weights);
	unsigned weight_saved = total_graph_weight - mst_total;

	cout << weight_saved << endl;
	return 0;
}
