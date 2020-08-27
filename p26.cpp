#include <bits/stdc++.h>

using namespace std;

#define D 1000
#define MAX_PRECISION 2000

string precision_compute(int x, int y, int n) { 
	string div = "";

	int d = x / y;
	for (int i = 0; i <= n; i++) { 
		div += to_string(d);
		x = x - (y * d);
		
		if (x == 0) {
			break;
		}

		x = x * 10;
		d = x / y;

		if (i == 0) {
			div += ".";
		}
	}
	
	return div.substr(2, div.size() - 2);
}

int num_trailing_digits(string & div) {
	int i = div.size() - 1;
	char digit = div[i];
	int n = 0;

	while (i >= 0 && div[i] == digit) {
		i--;
		n++;
	}

	return n;
}

int digit_cycle_size(string & div) {
	if (div.size() < MAX_PRECISION) return div.size();
	if (num_trailing_digits(div) > 100) return 1;

	for (unsigned start = 0; start < div.size(); start++) {
		for (unsigned n = 2; n < div.size(); n++) {
			if (start + 2 * n > div.size()) break;

			string left_substr = div.substr(start, n);
			string right_substr = div.substr(start + n, n);

			if (left_substr == right_substr) return n;
		}
	}

	return -1;
}

int main() {
	int max_digit_cycle = 0;
	int optimal_d = 0;

	for (int d = 2; d < D; d++) {
		string div = precision_compute(1, d, MAX_PRECISION);
		int digit_c_size = digit_cycle_size(div);

		if (digit_c_size > max_digit_cycle) {
			max_digit_cycle = digit_c_size;
			optimal_d = d;
		}
	}

	cout << optimal_d << endl;
	return 0;
}
