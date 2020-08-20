#include <bits/stdc++.h>

using namespace std;

#define N 80
#define FILE_PATH "files/p081_matrix.txt"
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

int main() {
    vector<vector<int>> matrix = process_file();
    unordered_map<pair<int, int>, int, pair_hash> mps;

    for (int r = N - 1; r >= 0; r--) {
        for (int c = N - 1; c >= 0; c--) {
            pair<int, int> curr(r, c);

            if (curr == PAIR(N - 1, N - 1)) mps[curr] = matrix[r][c];
            else if (r == N - 1) mps[curr] = matrix[r][c] + mps[PAIR(r, c + 1)];
            else if (c == N - 1) mps[curr] = matrix[r][c] + mps[PAIR(r + 1, c)];
            else mps[curr] = matrix[r][c] + min(mps[PAIR(r + 1, c)], mps[PAIR(r, c + 1)]);

        }
    }

    cout << mps[PAIR(0, 0)] << endl;
    return 0;
}