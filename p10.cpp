#include <bits/stdc++.h>

using namespace std;

#define N 2000000

bool is_prime(long long n) {
	if (n == 1) return false;
	if (n == 2) return true;
	if (n % 2 == 0) return false;

	for (long long d = 3; d <= floor(sqrt(n)); d++) {
		if (n % d == 0) return false;
	}

	return true;
}

int main() {
	long long sum = 0;

	for (long long n = 1; n < N; n++) {
		if (is_prime(n)) sum += n;
	}

	cout << sum << endl;

	return 0;
}
