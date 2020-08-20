#include <bits/stdc++.h>

using namespace std;

#define N 80
#define INFTY (unsigned)-1
#define FILE_PATH "files/p083_matrix.txt"
#define PAIR(r, c) pair<int, int>(r, c)


struct pair_hash {
	size_t operator() (const pair<int, int> & p) const {
		ostringstream out;
		out << p.first << ',' << p.second;
		return hash<string>()(out.str());
	}
};

vector<int> process_line(string & line) {
	stringstream ss(line);
	string temp_str;
	vector<int> row;
	
	while(getline(ss, temp_str, ',')) {
		int elem = stoi(temp_str);
		row.push_back(elem);
	}

	return row;
}

vector<vector<int>> process_file() {
	string line;
	ifstream file;
	file.open(FILE_PATH);

	vector<vector<int>> matrix;

	while (getline(file, line)) {
		vector<int> row = process_line(line);
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
    vector<vector<int>> matrix = process_file();
	vector<pair<int, int>> vertices = get_vertices();
	unordered_map<pair<int, int>, unordered_set<pair<int, int>, pair_hash>, pair_hash> edges = get_edges();

	unordered_map<pair<int, int>, unsigned, pair_hash> dist;
	vector<pair<int, int>> q;
	pair<int, int> source(-1, -1);

	for (auto vertex : vertices) {
		dist[vertex] = INFTY;
		q.push_back(vertex);
	}

	dist[source] = 0;

	while (q.size() != 0) {
		pair<int, int> u = get_min_vertex(q, dist);

		auto neighbors = edges[u];
		for (auto v : neighbors) {
			int i = v.first, j = v.second;
			unsigned alt = dist[u] + matrix[i][j];
			if (dist[u] == INFTY) alt = INFTY;

			dist[v] = min(dist[v], alt);
		}
	}

	auto end_vertex = vertices[vertices.size() - 1];
	cout << dist[end_vertex] << endl;
    return 0;
}