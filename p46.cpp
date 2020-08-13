#include <bits/stdc++.h>

using namespace std;

bool is_prime(unsigned long long & n) {
	if (n <= 1) return false;
	if (n == 2) return true;
	if (n % 2 == 0) return false;

	for (unsigned long long d = 3; d <= floor(sqrt(n)); d++) {
		if (n % d == 0) return false;
	}

	return true;
}

bool goldbach(unsigned long long & n) {
    unsigned long long j = 1;

    while (2 * pow(j, 2) < n) {
        unsigned long long p = n - 2 * pow(j, 2);
        if (is_prime(p)) return true;
        j++;
    }

    return false;
}

int main() {
    unsigned long long n = 9;

    while (true) {
        if (is_prime(n)) goto END_LOOP;
        if (!goldbach(n)) break;

        END_LOOP:
            n += 2;
    }

    cout << n << endl;
    return 0;
}