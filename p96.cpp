#include <bits/stdc++.h>

using namespace std;

#define FILE_PATH "files/p096_sudoku.txt"
#define N 9

typedef vector<vector<int>> Matrix;

vector<int> process_line(string & line) {
	vector<int> nums;

	for (unsigned idx = 0; idx < N; idx++) {
		int num = line[idx] - '0';
		nums.push_back(num);
	}

	return nums;
}

Matrix get_matrix(ifstream & file) {
	Matrix m;
	string nums_str;

	for (int i = 0; i < N; i++) {
		getline(file, nums_str);
		vector<int> nums = process_line(nums_str);
		m.push_back(nums);
	}

	return m;
}

vector<Matrix> process_file() {
	ifstream file;
	string line;
	file.open(FILE_PATH);
	vector<Matrix> puzzles;

	while(getline(file, line)) {
		Matrix puzzle = get_matrix(file);
		puzzles.push_back(puzzle);
	}

	file.close();
	return puzzles;
}

void print_puzzle(Matrix & m) {
	for (unsigned r = 0; r < N; r++) {
		for (unsigned c = 0; c < N; c++) {
			cout << m[r][c];
		}
		cout << endl;
	}
	cout << endl;
}

void solve_puzzle(Matrix puzzle) {
	return;
}

int main() {
	vector<Matrix> puzzles = process_file();

	for (Matrix puzzle : puzzles) {
		solve_puzzle(puzzle);
		break;
	}

	return 0;
}
