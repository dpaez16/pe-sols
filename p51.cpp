#include <bits/stdc++.h>

using namespace std;

#define N_DIGITS 6
//#define N_DIGITS 7
#define PRIME_FAMILY_SIZE 8


bool is_prime(unsigned int & n) {
	if (n <= 1) return false;
	if (n == 2) return true;
	if (n % 2 == 0) return false;

	for (unsigned int d = 3; d <= floor(sqrt(n)) + 1; d++) {
		if (n % d == 0) return false;
	}

	return true;
}

int main() {
	vector<set<unsigned>> group_primes;
	unsigned exp = 1;
	unsigned n = 0;

	while (exp <= N_DIGITS) {
		set<unsigned> primes;

		while (true) {
			if (!is_prime(n)) goto END_INNER_LOOP;

			primes.insert(n);

			END_INNER_LOOP:
			if (++n == pow(10, exp)) break;
		}

		if (primes.size() >= PRIME_FAMILY_SIZE)
			group_primes.push_back(primes);

		exp++;
	}

	for (auto primes : group_primes) {
		cout << primes.size() << endl;
	}

	return 0;
}

