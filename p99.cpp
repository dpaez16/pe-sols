#include <bits/stdc++.h>

using namespace std;

#define FILE_PATH "files/p099_base_exp.txt"

long double process_line(string & line) {
	stringstream ss(line);
	string base_str, exponent_str;
	
	getline(ss, base_str, ',');
	getline(ss, exponent_str, ',');

	long double base = stold(base_str);
	long double exponent = stold(exponent_str);

	return exponent * logl(base);
}

vector<long double> process_file() {
	string line;
	ifstream file;
	file.open(FILE_PATH);
	vector<long double> nums;

	while(getline(file, line)) {
		long double num = process_line(line);
		nums.push_back(num);
	}

	file.close();
	return nums;
}

int main() {
	vector<long double> nums = process_file();
	
	long double max_num = 0;
	unsigned max_line_num = 0;

	for (unsigned i = 0; i < nums.size(); i++) {
		long double num = nums[i];
		if (num > max_num) {
			max_num = num;
			max_line_num = i + 1;
		}
	}

	cout << max_line_num << endl;
	return 0;
}
