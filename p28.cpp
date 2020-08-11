#include <bits/stdc++.h>

using namespace std;

#define N 1001

long long sum_diagonals(int n) {
    if (n == 1) return 1;

    long long sum = pow(n, 2);
    long long base = sum;

    for (int i = 1; i <= 3; i++) {
        sum += base - (n - 1) * i;
    }

    return sum;
}

int main() {
    long long sum = 0;
    for (int n = 1; n <= N; n += 2) {
        sum += sum_diagonals(n);
    }

    cout << sum << endl;

    return 0;
}