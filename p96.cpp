#include <bits/stdc++.h>

using namespace std;

#define FILE_PATH "files/p096_sudoku.txt"
#define N 9

typedef vector<vector<int>> Matrix;
bool SOLVED_CURR_PUZZLE = false;

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

bool check_slice(vector<int> & arr) {
	unordered_map<int, int> counts;

	for (int val : arr) {
		if (val == 0) continue;

		if (counts.find(val) == counts.end()) {
			counts[val] = 0;
		}

		counts[val]++;

		if (counts[val] > 1) return false;
	}

	return true;
}

vector<int> slice_row(Matrix & m, int row) {
	return m[row];
}

vector<int> slice_column(Matrix & m, int col) {
	vector<int> column;

	for (unsigned row = 0; row < N; row++) {
		column.push_back(m[row][col]);
	}

	return column;
}

bool square_ok(Matrix & m, int i, int j) {
	vector<int> row = slice_row(m, i);
	vector<int> column = slice_column(m, j);

	return check_slice(row) && check_slice(column);
}

vector<pair<int, int>> find_empty_spots(Matrix & m) {
	vector<pair<int, int>> empty_spots;

	for (unsigned r = 0; r < N; r++) {
		for (unsigned c = 0; c < N; c++) {
			if (m[r][c] != 0) continue;

			pair<int, int> p(r, c);
			empty_spots.push_back(p);
		}
	}

	return empty_spots;
}

bool solve_puzzle_helper(Matrix m, int i, int j) {
	print_puzzle(m);
	if (SOLVED_CURR_PUZZLE) {
		return true;
	}

	if (i == j && i == -1) {
		puts("Solution:");
		print_puzzle(m);
		//SOLVED_CURR_PUZZLE = true;
		return true;
	}

	for (int num_choice = 1; num_choice <= N; num_choice++) {
		m[i][j] = num_choice;

		if (!square_ok(m, i, j)) continue;

		vector<pair<int, int>> empty_spots = find_empty_spots(m);

		if (empty_spots.size() == 0) {
			return solve_puzzle_helper(m, -1, -1);
		}

		for (auto p : empty_spots) {
			int r = p.first;
			int c = p.second;
			bool solved = solve_puzzle_helper(m, r, c);

			if (!solved) break;
		}
	}

	return false;
}

void solve_puzzle(Matrix & puzzle) {
	return (void)solve_puzzle_helper(puzzle, 0, 0);
}

int main() {
	vector<Matrix> puzzles = process_file();

	for (Matrix puzzle : puzzles) {
		solve_puzzle(puzzle);
		break;
	}

	return 0;
}
