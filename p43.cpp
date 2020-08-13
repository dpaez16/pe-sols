#include <bits/stdc++.h>

using namespace std;

#define MIN_PANDIGITAL 2345689017
#define MAX_PANDIGITAL 9876543210

vector<int> primes = {2, 3, 5, 7, 11, 13, 17};

bool is_pandigital(unsigned long long & n) {
    string n_str = to_string(n);

    if (n_str.size() != 10) return false;
    
    unordered_set<int> digits;
    for (char c : n_str) {
        int digit = c - '0';
        if (digits.find(digit) != digits.end()) return false;

        digits.insert(digit);
    }

    return true;
}

bool has_property(unsigned long long n) {
    for (int idx = primes.size() - 1; idx >= 0; idx--) {
        int substring = n % 1000;

        if (substring % primes[idx] != 0) return false;

        n /= 10;
    }

    return true;
}

int main() {
    unsigned long long sum = 0;
    unsigned long long n = 17;
    int acc = 0;

    while (n <= MAX_PANDIGITAL) {
        if (has_property(n) && is_pandigital(n)) sum += n;

        n += 17;
        acc += 17;
        if (acc >= 1000) {
            n -= 3;
            acc = 0;
        }
    }

    cout << sum << endl;
    return 0;
}