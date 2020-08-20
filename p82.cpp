#include <bits/stdc++.h>

using namespace std;

#define N 80
#define INFTY (unsigned)-1
#define FILE_PATH "files/p082_matrix.txt"
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
	
	return neighbors;
}

unordered_map<pair<int, int>, unordered_set<pair<int, int>, pair_hash>, pair_hash> get_edges() {
	unordered_map<pair<int, int>, unordered_set<pair<int, int>, pair_hash>, pair_hash> edges;
	unordered_set<pair<int, int>, pair_hash> setinel_vertex_neighbors;

	for (int r = 0; r < N; r++) {
		setinel_vertex_neighbors.insert(PAIR(r, 0));

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

int main() {
    vector<vector<int>> matrix = process_file();
	vector<pair<int, int>> vertices = get_vertices();
	unordered_map<pair<int, int>, unordered_set<pair<int, int>, pair_hash>, pair_hash> edges = get_edges();
	
	int n_vertices = vertices.size();
	unsigned ** dist = new unsigned * [n_vertices];

	for (int r = 0; r < n_vertices; r++) {
		dist[r] = new unsigned [n_vertices];

		for (int c = 0; c < n_vertices; c++) {
			auto vertex_a = vertices[r];
			auto vertex_b = vertices[c];
			
			if (vertex_a == vertex_b) {
				dist[r][c] = 0;
			} else if (is_edge(vertex_a, vertex_b, edges)) {
				int i = vertex_b.first, j = vertex_b.second;
				dist[r][c] = matrix[i][j];
			} else {
				dist[r][c] = INFTY;
			}
		}
	}

	for (int k = 0; k < n_vertices; k++) {
		for (int i = 0; i < n_vertices; i++) {
			for (int j = 0; j < n_vertices; j++) {
				unsigned alt = dist[i][k] + dist[k][j];
				if (dist[i][k] == INFTY || dist[k][j] == INFTY) alt = INFTY;

				dist[i][j] = min(dist[i][j], alt);
			}
		}
	}

	unsigned min_dist = INFTY;
	for (int i = 0; i < n_vertices; i++) {
		auto vertex = vertices[i];
		if (vertex.second != N - 1) continue;

		min_dist = min(min_dist, dist[0][i]);
	}

	cout << min_dist << endl;

	for (int r = 0; r < n_vertices; r++) {
		delete [] dist[r];
	}

	delete [] dist;

    return 0;
}