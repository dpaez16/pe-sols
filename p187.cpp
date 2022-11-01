#include <bits/stdc++.h>

using namespace std;

const unsigned N = pow(10, 8);

vector<unsigned> sieve(unsigned n) {
	unsigned length = n + 1;
	bool * is_prime = (bool *)calloc(length, sizeof(bool));
	memset(is_prime, true, sizeof(bool) * length);
	is_prime[0] = false;
	is_prime[1] = false;

	vector<unsigned> primes;
	for (unsigned p = 0; p < length; p++) {
		if (!is_prime[p]) continue;

		primes.push_back(p);
		for (unsigned k = 2 * p; k < length; k += p) {
			is_prime[k] = false;
		}
	}

	free(is_prime);
	primes.shrink_to_fit();
	return primes;
}

unsigned bisect_right(const vector<unsigned> & arr, unsigned x, unsigned left) {
	unsigned i = left;
	unsigned j = arr.size();

	while (i < j) {
		unsigned m = i + (j - i) / 2;

		if (x < arr[m]) j = m;
		else i = m + 1;
	}

	return i;
}

int main() {
	const vector<unsigned> primes = sieve(N / 2);
	unsigned count = 0;

	for (unsigned i = 0; i < primes.size(); i++) {
		unsigned p = primes[i];
		unsigned j = bisect_right(primes, N / p, i);

		if (j < i) continue;
		count += j - i;
	}

	cout << count << endl;
	return 0;
}
