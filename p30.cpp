#include <bits/stdc++.h>

using namespace std;

#define N 5

long long get_digit_sum(string & s) {
    long long sum = 0;

    for (char c : s) {
        int digit = c - '0';
        sum += pow(digit, N);
    }

    return sum;
}

int main() {
    long long sum = 0;

    for (long long n = 0; n < pow(10, N + 1); n++) {
        if (n < 10) continue;
    
        string n_str = to_string(n);
        long long digit_sum = get_digit_sum(n_str);
        
        if (digit_sum == n) sum += n;
    }

    cout << sum << endl;
    return 0;
}