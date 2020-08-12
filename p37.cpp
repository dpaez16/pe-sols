#include <bits/stdc++.h>

using namespace std;

#define N 11

bool is_prime(unsigned long long & n) {
	if (n <= 1) return false;
	if (n == 2) return true;
	if (n % 2 == 0) return false;

	for (unsigned long long d = 3; d <= floor(sqrt(n)); d++) {
		if (n % d == 0) return false;
	}

	return true;
}

unsigned long long trunc_right(unsigned long long & n) {
    return n / 10;
}

unsigned long long trunc_left(unsigned long long & n) {
    string n_str = to_string(n);
    n_str = n_str.substr(1, n_str.size() - 1);
    return stoull(n_str);
}

bool is_truncatable_prime(unsigned long long n, bool from_left) {
    if (n < 10 || !is_prime(n)) return false;
    
    while (n >= 10) {
        n = from_left ? trunc_left(n) : trunc_right(n);
        
        if (!is_prime(n)) return false;
    }

    return is_prime(n);
}

int main() {
    unsigned long long sum = 0;
    int n_truncatable_primes = 0;
    unsigned long long n = 0;

    while (n_truncatable_primes != N) {
        if (is_truncatable_prime(n, true) && is_truncatable_prime(n, false)) {
            sum += n;
            n_truncatable_primes++;
        }

        n++;
    }
    
    cout << sum << endl;

    return 0;
}