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

vector<unsigned> process_line(string & line) {
	stringstream ss(line);
	string temp_str;
	vector<unsigned> row;
	
	while(getline(ss, temp_str, ',')) {
		unsigned elem = temp_str == "-" ? INFTY : stoui(temp_str);
		row.push_back(elem);
	}

	return row;
}

vector<vector<unsigned>> process_file() {
	string line;
	ifstream file;
	file.open(FILE_PATH);

	vector<vector<unsigned>> matrix;

	while (getline(file, line)) {
		vector<unsigned> row = process_line(line);
		matrix.push_back(row);
	}

	file.close();
	return matrix;
}

vector<pair<int, int>> get_vertices() {
	vector<pair<int, int>> vertices = {PAIR(-1, -1)};

	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			pair<int, int> vertex(r, c);
			vertices.push_back(vertex);
		}
	}

	return vertices;
}

unordered_set<pair<int, int>, pair_hash> get_neighbors(int r, int c) {
	unordered_set<pair<int, int>, pair_hash> neighbors;

	if (r - 1 >= 0) neighbors.insert(PAIR(r - 1, c));
	if (r + 1 < N) neighbors.insert(PAIR(r + 1, c));
	if (c + 1 < N) neighbors.insert(PAIR(r, c + 1));
	if (c - 1 >= 0) neighbors.insert(PAIR(r, c - 1));
	
	return neighbors;
}

unordered_map<pair<int, int>, unordered_set<pair<int, int>, pair_hash>, pair_hash> get_edges() {
	unordered_map<pair<int, int>, unordered_set<pair<int, int>, pair_hash>, pair_hash> edges;
	unordered_set<pair<int, int>, pair_hash> setinel_vertex_neighbors = {PAIR(0, 0)};

	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			pair<int, int> vertex(r, c);
			unordered_set<pair<int, int>, pair_hash> neighbors = get_neighbors(r, c);
			edges[vertex] = neighbors;
		}
	}

	edges[PAIR(-1, -1)] = setinel_vertex_neighbors;

	return edges;
}

bool is_edge(pair<int, int> & vertex_a, pair<int, int> & vertex_b, unordered_map<pair<int, int>, unordered_set<pair<int, int>, pair_hash>, pair_hash> & edges) {
	auto neighbors_a = edges[vertex_a];
	return neighbors_a.find(vertex_b) != neighbors_a.end();
}

pair<int, int> get_min_vertex(vector<pair<int, int>> & q, unordered_map<pair<int, int>, unsigned, pair_hash> & dist) {
	unsigned min_i = 0;
	unsigned min_dist = INFTY;

	for (unsigned i = 0; i < q.size(); i++) {
		auto vertex = q[i];
		if (min_dist > dist[vertex]) {
			min_i = i;
			min_dist = dist[vertex];
		}
	}

	auto min_vertex = q[min_i];
	q.erase(q.begin() + min_i);

	return min_vertex;
}

int main() {
	vector<vector<unsigned>> matrix = process_file();
	return 0;
}
