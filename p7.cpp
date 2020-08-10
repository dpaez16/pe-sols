#include <bits/stdc++.h>

using namespace std;

#define N 10001

bool is_prime(long long n) {
	if (n == 1) return false;
	if (n == 2) return true;
	if (n % 2 == 0) return false;

	for (long long d = 3; d < floor(sqrt(n)) + 1; d++) {
		if (n % d == 0) return false;
	}

	return true;
}

int main() {
	int n = 1;
	int count = 0;

	while (count != N) {
		if (is_prime(n)) {
			count++;
		}

		n++;
	}

	cout << --n << endl;

	return 0;
}
