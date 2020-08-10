#include <bits/stdc++.h>

using namespace std;

#define N 10000

int sum_proper_divisors(int n) {
    if (n == 1) return 0;

    int sum_divisors = 1;
    int upper_bound = n;

    for (int d = 2; d < upper_bound; d++) {
        if (n % d == 0) {
            sum_divisors += d + (n / d);
            upper_bound = n / d;
        }
    }

    return sum_divisors;
}

int main() {
    unordered_map<int, int> sum_proper_divisors_map;
    for (int n = 1; n < N; n++) {
        sum_proper_divisors_map[n] = sum_proper_divisors(n);
    }

    int sum = 0;
    for(int a = 1; a < N; a++) {
        int b = sum_proper_divisors_map[a];
        if (b <= a) continue;
        if (sum_proper_divisors_map[b] == a) sum += a + b;
    }

    cout << sum << endl;

    return 0;
}