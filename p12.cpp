#include <bits/stdc++.h>

using namespace std;

long long tri_num(long long n) {
	return n * (n + 1) / 2;
}

unsigned num_divisors(long long n) {
	unsigned n_divisors = 0;
	long long high = n;

	for (long long low = 1; low < high; low++) {
		if (n % low == 0) {
			high = n / low;
			n_divisors += 2;
		}
	}

	return n_divisors;
}

int main() {
	unsigned n_divs = 0;
	long long N = 2;

	while (n_divs <= 500) {
		long long n = tri_num(N++);
		n_divs = num_divisors(n);
	}

	cout << tri_num(--N) << endl;
	return 0;
}
