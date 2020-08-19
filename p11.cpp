#include <bits/stdc++.h>

using namespace std;

#define STRIDE 4
#define N 20
#define FILE_PATH "files/p11.txt"

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
	vector<vector<int>> grid;

	while(getline(file, line)) {
		vector<int> row = process_line(line);
		grid.push_back(row);
	}

	file.close();
	return grid;
}

long long largest_prod(vector<vector<int>> & grid) {
	long long max_prod = 0;
	
	// max product along horizontal axis
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N - STRIDE; c++) {
			long long prod = grid[r][c] * \
					 grid[r][c + 1] * \
					 grid[r][c + 2] * \
					 grid[r][c + 3];
			max_prod = max(max_prod, prod);
		}
	}
	
	// max product along vertical axis
	for (int r = 0; r < N - STRIDE; r++) {
		for (int c = 0; c < N; c++) {
			long long prod = grid[r][c] * \
					 grid[r + 1][c] * \
					 grid[r + 2][c] * \
					 grid[r + 3][c];
			max_prod = max(max_prod, prod);
		}
	}

	// max product along diagonal (\)
	for (int r = 0; r < N - STRIDE; r++) {
		for (int c = 0; c < N - STRIDE; c++) {
			long long prod = grid[r][c] * \
					 grid[r + 1][c + 1] * \
					 grid[r + 2][c + 2] * \
					 grid[r + 3][c + 3];
			max_prod = max(max_prod, prod);
		}
	}
	
	// max product along diagonal (/)
	for (int r = 0; r < N - STRIDE; r++) {
		for (int c = STRIDE; c < N; c++) {
			long long prod = grid[r][c] * \
					 grid[r + 1][c - 1] * \
					 grid[r + 2][c - 2] * \
					 grid[r + 3][c - 3];
			max_prod = max(max_prod, prod);
		}
	}


	return max_prod;
}

int main() {
	vector<vector<int>> grid = process_file();
	long long max_prod = largest_prod(grid);

	cout << max_prod << endl;

	return 0;
}
