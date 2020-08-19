#include <bits/stdc++.h>

using namespace std;

#define N 100
#define LOWER_BOUND pow(10, 6)

long double factorial(long double n) {
    if (n <= 1) return 1;

    long double acc = 1;
    for (long double f = 2; f <= n; f++) {
        acc *= f;
    }

    return acc;
}

long double n_choose_r(long double & n, long double & r) {
    return factorial(n) / (factorial(r) * factorial(n - r));
}

int main() {
    int count = 0;

    for (long double n = 1; n <= N; n++) {
        for (long double r = 0; r <= n; r++) {
            long double val = n_choose_r(n, r);
            if (val > LOWER_BOUND) count++;
        }
    }

    cout << count << endl;
    return 0;
}