#include <bits/stdc++.h>

using namespace std;

#define FILE_PATH "files/p18.txt"
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
	
	while(getline(ss, temp_str, ' ')) {
		int elem = stoi(temp_str);
		row.push_back(elem);
	}

	return row;
}

vector<vector<int>> process_file() {
	string line;
	ifstream file;
	file.open(FILE_PATH);

	vector<vector<int>> triangle;

	while (getline(file, line)) {
		vector<int> row = process_line(line);
		triangle.push_back(row);
	}

	file.close();
	return triangle;
}

int main() {
	vector<vector<int>> triangle = process_file();
	unordered_map<pair<int, int>, int, pair_hash> max_path_sum;
	
	for (size_t r = 0; r < triangle.size(); r++) {
		int r_temp = r;
		r = triangle.size() - 1 - r;

		for (size_t c = 0; c < triangle[r].size(); c++) {
			pair<int, int> coord(r, c);
			
			if (r == triangle.size() - 1)
				max_path_sum[coord] = triangle[r][c];
			else
				max_path_sum[coord] = triangle[r][c] + max(max_path_sum[PAIR(r + 1, c)], max_path_sum[PAIR(r + 1, c + 1)]);
		}
		
		r = r_temp;
	}

	cout << max_path_sum[PAIR(0, 0)] << endl;
	return 0;
}
