#include <bits/stdc++.h>

using namespace std;

bool is_prime(long long n) {
	if (n == 1) return false;
	if (n == 2) return true;
	if (n % 2 == 0) return false;

	for (long long d = 3; d < floor(sqrt(n)) + 1; d++) {
		if (n % d == 0) return false;
	}

	return true;
}

int num_prime(int n) {
    if (n == 1) return 0;

    long long base = pow(n, 2);
    int count = 0;

    for (int i = 1; i <= 3; i++) {
        long long p = base - (n - 1) * i;
        if (is_prime(p)) count++;
    }

    return count;
}

int main() {
    int curr_num_prime = 0;
    int total_diagonal_elements = 1;
    int n = 3;

    while (true) {
        curr_num_prime += num_prime(n);
        total_diagonal_elements += 4;

        double ratio = 1.0 * curr_num_prime / total_diagonal_elements;
        if (ratio < 0.10) break;

        n += 2;
    }

    cout << n << endl;
    return 0;
}