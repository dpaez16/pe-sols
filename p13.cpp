#include <bits/stdc++.h>

using namespace std;

#define N_DIGITS_SUM 10
#define FILE_PATH "files/p13.txt"


string process_file() {
	string line;
	ifstream file;
	file.open(FILE_PATH);
	long double sum = 0;

	while (getline(file, line)) {
		long double num = stold(line);
		sum += num;
	}

	file.close();
	string first_n_digits = to_string(sum).substr(0, N_DIGITS_SUM);

	return first_n_digits;
}

int main() {
	string first_n_digits = process_file();
	cout << first_n_digits << endl;
	return 0;
}
