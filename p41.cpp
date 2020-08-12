#include <bits/stdc++.h>

using namespace std;

#define MIN_N_DIGIT_PANDIGITAL 1
#define MAX_N_DIGIT_PANDIGITAL 987654321

bool is_prime(unsigned long long & n) {
	if (n <= 1) return false;
	if (n == 2) return true;
	if (n % 2 == 0) return false;

	for (unsigned long long d = 3; d <= floor(sqrt(n)); d++) {
		if (n % d == 0) return false;
	}

	return true;
}

bool is_n_digit_pandigital(unsigned long long d) {
    string d_str = to_string(d);
    unsigned n = d_str.size();

    unordered_set<int> digits;
    int min_digit = 1, max_digit = n;
    
    for (char c : d_str) {
        int digit = c - '0';
        if (digits.find(digit) != digits.end()) return false;
        else if (digit < min_digit || max_digit < digit) return false;

        digits.insert(digit);
    }

    return true;
}

int main() {
    for (unsigned long long d = MAX_N_DIGIT_PANDIGITAL; d >= MIN_N_DIGIT_PANDIGITAL; d-= 2) {
        if (is_n_digit_pandigital(d) && is_prime(d)) {
            cout << d << endl;
            break;
        }
    }

    return 0;
}