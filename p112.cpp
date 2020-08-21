#include <bits/stdc++.h>

using namespace std;

#define PROPORTION 0.99

bool is_increasing_num(unsigned long long n) {
    if (n < 10) return true;

    string n_str = to_string(n);

    for (unsigned i = 1; i < n_str.size(); i++) {
        if (n_str[i - 1] > n_str[i]) return false;
    }

    return true;
}

bool is_decreasing_num(unsigned long long n) {
    if (n < 10) return true;

    string n_str = to_string(n);

    for (unsigned i = 1; i < n_str.size(); i++) {
        if (n_str[i - 1] < n_str[i]) return false;
    }

    return true;
}

bool is_bouncy(unsigned long long n) {
    return !(is_increasing_num(n) || is_decreasing_num(n));
}

int main() {
    unsigned long long n_bouncy = 0;
    unsigned long long n = 0;

    while (true) {
        n++;

        if (is_bouncy(n)) n_bouncy++;
        if (1.0 * n_bouncy / n == PROPORTION) break;
    }

    cout << n << endl;
    return 0;
}