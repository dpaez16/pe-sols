#include <bits/stdc++.h>

using namespace std;

#define A_UPPER_BOUND 10000
#define N_UPPER_BOUND 5

bool is_pandigital(unsigned long long n) {
    string n_str = to_string(n);
    if (n_str.size() != 9) return false;

    unordered_set<char> digits;
    
    for (char c : n_str) {
        if (digits.find(c) != digits.end() || c == '0') return false;
        digits.insert(c);
    }

    return true;
}

unsigned long long concat_product(unsigned long long a, int n) {
    string concat_product_str = "";
    for (int i = 1; i <= n; i++) {
        concat_product_str += to_string(a * i);
        if (concat_product_str.size() > 9) return 0;
    }

    return stoull(concat_product_str);
}

int main() {
    unsigned long long largest_pandigital_num = 0;

    for (unsigned long long a = 1; a < A_UPPER_BOUND; a++) {
        for (int n = 2; n < N_UPPER_BOUND; n++) {
            unsigned long long num = concat_product(a, n);
            if (is_pandigital(num)) {
                largest_pandigital_num = max(largest_pandigital_num, num);
            }
        }
    }

    cout << largest_pandigital_num << endl;
    return 0;
}