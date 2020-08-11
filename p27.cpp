#include <bits/stdc++.h>

using namespace std;

#define N 1000

long long quad(int a, int b, long long n) {
    return pow(n, 2) + a * n + b;
}

bool is_prime(long long n) {
	if (n == 1) return false;
	if (n == 2) return true;
	if (n % 2 == 0) return false;

	for (long long d = 3; d < floor(sqrt(n)) + 1; d++) {
		if (n % d == 0) return false;
	}

	return true;
}

long long num_consecutive_primes(int a, int b) {
    long long n = 0;
    
    while (true) {
        long long quad_eval = quad(a, b, n);
        if (!is_prime(quad_eval)) break;
        n++;
    }

    return n;
}

int main() {
    long long most_consecutive_primes = 0;
    long long opt_a = 0, opt_b = 0;

    for (int a = -N + 1; a < N; a++) {
        for (int b = -N; b <= N; b++) {
            long long consecutive_primes = num_consecutive_primes(a, b);
            if (consecutive_primes > most_consecutive_primes) {
                most_consecutive_primes = consecutive_primes;
                opt_a = a;
                opt_b = b;
            }
        }
    }

    cout << opt_a * opt_b << endl;
    return 0;
}
