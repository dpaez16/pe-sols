#include <bits/stdc++.h>

using namespace std;

#define N 600851475143

vector<pair<long long, long long>> prime_factorization(long long n) {
	vector<pair<long long, long long>> factor_exp_pairs;

	long long factor = 2;
	long long exponent = 0;
	while (n != 1) {
		if (n % factor == 0) {
			n /= factor;
			exponent++;
		} else {
			if (exponent != 0) {
				pair<long long, long long> factor_exp_pair(factor, exponent);
				factor_exp_pairs.push_back(factor_exp_pair);
			}

			factor++;
			exponent = 0;
		}
	}

	if (exponent != 0) {
		pair<long long, long long> factor_exp_pair(factor, exponent);
		factor_exp_pairs.push_back(factor_exp_pair);
	}

	return factor_exp_pairs;
}

int main() {
	vector<pair<long long, long long>> factor_exp_pairs = prime_factorization(N);
	reverse(factor_exp_pairs.begin(), factor_exp_pairs.end());

	for (auto factor_exp_pair : factor_exp_pairs) {
		long long factor = factor_exp_pair.first;
		long long exponent = factor_exp_pair.second;
		if (exponent == 1) {
			cout << factor << endl;
			break;
		}
	}

	return 0;
}
