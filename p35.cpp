#include <bits/stdc++.h>

using namespace std;

#define N pow(10, 6)

bool is_prime(unsigned int & n) {
	if (n <= 1) return false;
	if (n == 2) return true;
	if (n % 2 == 0) return false;

	for (unsigned int d = 3; d <= floor(sqrt(n)) + 1; d++) {
		if (n % d == 0) return false;
	}

	return true;
}

unsigned int rotate_num(unsigned int n) {
	unsigned int last_digit = n % 10;
	string n_rot_str = to_string(last_digit) + to_string(n / 10);
	return stoi(n_rot_str);
}

bool is_circular_prime(unsigned int & n) {
	if (!is_prime(n)) return false;
	if (n < 10) return true;

	unsigned int n_rot = n;
	while ((n_rot = rotate_num(n_rot)) != n) {
		if (!is_prime(n_rot)) return false;
	}

	return true;
}

int main() {
	unsigned int n_circular_primes = 1;

	for (unsigned int p = 3; p < N; p += 2) {
		if (is_circular_prime(p)) n_circular_primes++;
	}

	cout << n_circular_primes << endl;
	return 0;
}

