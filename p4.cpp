#include <bits/stdc++.h>

using namespace std;

bool is_palindrome(long long n) {
	if (n < 10) return true;
	string n_str = to_string(n);

	for (unsigned idx = 0; idx < n_str.size() / 2; idx++) {
		if (n_str[idx] != n_str[n_str.size() - 1 - idx]) {
			return false;
		}
	}

	return true;
}

int main() {
	long long max_palindrome = 0;

	for (int a = 100; a <= 999; a++) {
		for (int b = 100; b <= 999; b++) {
			long long prod = a * b;
			if (is_palindrome(prod)) {
				max_palindrome = max(max_palindrome, prod);
			}
		}
	}

	cout << max_palindrome << endl;
	return 0;
}
