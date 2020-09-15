#include <bits/stdc++.h>

using namespace std;

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

bool eligible_prime(unsigned & prime, unsigned mask) {
	string prime_str = to_string(prime);
	char curr_digit = 0;

	for (unsigned i = 0; i < prime_str.size(); i++, mask >>= 1) {
		if ((mask & 1) == 0) continue;

		char old_digit = prime_str[prime_str.size() - 1 - i];

		if (curr_digit == 0) curr_digit = old_digit;
		if (curr_digit != old_digit) return false;
	}

	return true;
	
}

unsigned apply_mask(unsigned & prime, int & digit, unsigned mask) {
	string prime_str = to_string(prime);

	for (unsigned i = 0; i < prime_str.size(); i++, mask >>= 1) {
		if ((mask & 1) == 0) continue;

		char c = '0' + digit;

		prime_str[prime_str.size() - 1 - i] = c;
	}

	return stoul(prime_str);
}

unsigned get_family_size(set<unsigned> & primes, unsigned & test_prime, unsigned & mask) {
	unsigned family_size = 0;

	for (int d = 0; d <= 9; d++) {
		unsigned masked_prime = apply_mask(test_prime, d, mask);
			
		if (primes.find(masked_prime) == primes.end()) continue;
		
		family_size++;
	}

	return family_size;
}

int main() {
	unsigned n_digits = 1;
	unsigned p = 0;
	unsigned min_prime;

	while (true) {
		set<unsigned> primes;

		while (++p != pow(10, n_digits)) {
			if (!is_prime(p)) continue;

			primes.insert(p);
		}

		for (unsigned test_prime : primes) {
			for (unsigned mask = 1; mask < pow(2, n_digits); mask++) {
				if (!eligible_prime(test_prime, mask)) continue;

				unsigned family_size = get_family_size(primes, test_prime, mask);

				if (family_size != PRIME_FAMILY_SIZE) continue;

				min_prime = test_prime;
				goto END;
			}
		}
		
		n_digits++;
	}

	END:
	cout << min_prime << endl;
	
	return 0;
}

