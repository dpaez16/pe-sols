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
		if (temp_str == "-") goto END_LOOP;

		unsigned elem = stoi(temp_str);
		neighbors.push_back(elem);

		END_LOOP:
			c++;
	}

	return neighbors;
}

unordered_map<pair<int, int>, unsigned, pair_hash> process_file() {
	string line;
	ifstream file;
	file.open(FILE_PATH);

	unordered_map<pair<int, int>, unsigned, pair_hash> edge_weights;

	while (getline(file, line)) {
		process_line(line, edge_weights);
		edges.push_back(neighbors);
	}

	file.close();
	return matrix;
}


int main() {
	vector<vector<unsigned>> matrix = process_file();
	return 0;
}
