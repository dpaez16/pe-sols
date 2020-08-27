#include <bits/stdc++.h>

using namespace std;

#define N pow(10, 5)

vector<unsigned long long> f;

unsigned long long factorial(int n) {
    if (n <= 1) return 1;

    unsigned long long prod = 1;
    
    for (int d = 2; d <= n; d++) prod *= d;

    return prod;
}

bool has_property(unsigned long long n) {
    string n_str = to_string(n);
    unsigned long long sum = 0;

    for (char c : n_str) {
        int digit = c - '0';
        sum += f[digit];
    }

    return sum == n;
}

int main() {
    for (int i = 0; i <= 9; i++) {
        f.push_back(factorial(i));
    }

    unsigned long long sum = 0;
    
    for (unsigned long long n = 3; n < N; n++) {
        if (has_property(n)) sum += n;
    }

    cout << sum << endl;
    return 0;
}
