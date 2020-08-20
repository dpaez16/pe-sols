#include <bits/stdc++.h>

using namespace std;

#define PERMUTATION_COUNT 5

unordered_map<int, int> get_digit_counts(long double & n) {
	unordered_map<int, int> digit_counts;
	string n_str = to_string(n);

	for (int i = 0; i <= 9; i++) {
		digit_counts[i] = 0;
	}

	for (char c : n_str) {
		int digit = c - '0';
		digit_counts[digit]++;
	}

	return digit_counts;
}

string convert_map_to_str(unordered_map<int, int> & digit_counts) {
	string digit_counts_str = "";

	for (int i = 0; i <= 9; i++) {
		int count = digit_counts[i];
		digit_counts_str += to_string(i) + "-" + \
				    to_string(count) + "-";
	}

	return digit_counts_str;
}

string format_ans(long double & n) {
	string ans_str = to_string(pow(n, 3));
	size_t pos = ans_str.find('.');
	if (pos != ans_str.npos) ans_str = ans_str.substr(0, pos);

	return ans_str;
}

int main() {
	long double n = 1;
	unordered_map<string, int> permutation_counts;

	while (true) {
		long double n_cubed = pow(n, 3);
		unordered_map<int, int> digit_counts = get_digit_counts(n_cubed);
		string digit_counts_str = convert_map_to_str(digit_counts);
		
		if (permutation_counts.find(digit_counts_str) == permutation_counts.end())
			permutation_counts[digit_counts_str] = 0;

		permutation_counts[digit_counts_str]++;

		if (permutation_counts[digit_counts_str] == PERMUTATION_COUNT)
			break;

		n++;
	}

	n = 1;

	while (true) {
		long double n_cubed = pow(n, 3);
		unordered_map<int, int> digit_counts = get_digit_counts(n_cubed);
		string digit_counts_str = convert_map_to_str(digit_counts);
		
		if (permutation_counts[digit_counts_str] == PERMUTATION_COUNT)
			break;
		
		n++;
	}

	string ans = format_ans(n);
	cout << ans << endl;
	return 0;
}
