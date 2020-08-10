#include <bits/stdc++.h>

using namespace std;

#define UPPER_BOUND 1000000

unordered_map<long long, long long> collatz_map;

long long collatz(long long n) {
	if (collatz_map.find(n) != collatz_map.end()) return collatz_map[n];
	else if (n == 1) collatz_map[n] = 1;
	else if (n % 2 == 0) collatz_map[n] = 1 + collatz(n / 2);
	else collatz_map[n] = 1 + collatz(3 * n + 1);

	return collatz_map[n];
}

int main() {
	long long max_chain_length = 0;
	long long starting_number = 0;

	for (long long n = 1; n < UPPER_BOUND; n++) {
		long long chain_length = collatz(n);

		if (chain_length > max_chain_length) {
			max_chain_length = chain_length;
			starting_number = n;
		}
	}

	cout << starting_number << endl;

	return 0;
}
