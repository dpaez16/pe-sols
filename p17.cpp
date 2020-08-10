#include <bits/stdc++.h>

using namespace std;

#define N 1000
#define FILE_PATH "files/p17.txt"

unordered_map<int, int> number_counts;

void process_line(string & line) {
	stringstream ss(line);
	string temp_str;
	
	getline(ss, temp_str, ',');
	int number = stoi(temp_str);

	getline(ss, temp_str, ',');
	int number_count = temp_str.size();

	number_counts[number] = number_count;
}

void process_file() {
	string line;
	ifstream file;
	file.open(FILE_PATH);

	while (getline(file, line)) {
		process_line(line);
	}

	file.close();
}

void process_numbers() {
	for (int n = 1; n < 100; n++) {
		if (number_counts.find(n) != number_counts.end())
			continue;

		number_counts[n] = number_counts[(n / 10) * 10] + number_counts[n % 10];
	}

	for (int n = 101; n < N; n++) {
		if (n % 100 == 0) {
			number_counts[n] = number_counts[n / 100] + number_counts[100];
		} else {
			number_counts[n] = number_counts[n / 100] + number_counts[100] + 3 + number_counts[n % 100];
		}
	}

	number_counts[100] = strlen("onehundred");
}

int main() {
	process_file();
	process_numbers();

	int total = 0;
	for (int n = 1; n <= N; n++) {
		total += number_counts[n];
	}

	cout << total << endl;
	return 0;
}
	
