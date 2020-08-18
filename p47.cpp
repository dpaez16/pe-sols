#include <bits/stdc++.h>

using namespace std;

#define FIRST_N_NUMBERS 4

bool is_prime(unsigned int & n) {
	if (n <= 1) return false;
	if (n == 2) return true;
	if (n % 2 == 0) return false;

	for (unsigned int d = 3; d <= floor(sqrt(n)) + 1; d++) {
		if (n % d == 0) return false;
	}

	return true;
}

vector<pair<unsigned int, unsigned int>> prime_factorization(unsigned int n) {
	vector<pair<unsigned int, unsigned int>> factor_exp_pairs;

	unsigned int factor = 2;
	unsigned int exponent = 0;
	while (n != 1) {
		if (n % factor == 0) {
			n /= factor;
			exponent++;
		} else {
			if (exponent != 0) {
				pair<unsigned int, unsigned int> factor_exp_pair(factor, exponent);
				factor_exp_pairs.push_back(factor_exp_pair);
			}

			factor++;
			exponent = 0;
		}
	}

	if (exponent != 0) {
		pair<unsigned int, unsigned int> factor_exp_pair(factor, exponent);
		factor_exp_pairs.push_back(factor_exp_pair);
	}

	return factor_exp_pairs;
}

int main() {
	unsigned int n = 1;
	unsigned int count = 0;

	while (count != FIRST_N_NUMBERS) {
		vector<pair<unsigned int, unsigned int>> factor_exp_pairs = prime_factorization(n++);
		if (factor_exp_pairs.size() == FIRST_N_NUMBERS) count++;
		else count = 0;
	}

	n -= FIRST_N_NUMBERS;

	cout << n << endl;
	return 0;
}
