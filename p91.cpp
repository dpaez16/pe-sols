#include <bits/stdc++.h>

using namespace std;

#define N 50

int gcd(int x, int y) {
    while (y != 0) {
        int temp = x;
        x = y;
        y = temp % y;
    }

    return abs(x);
}

// http://oeis.org/A155154
int a(int n) {
    int s = 3 * n * n;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int g = gcd(i, j);
            s += 2 * min(j * g / i, (n - i) * g / j);
        }
    }

    return s;
}

int main() {
    cout << a(N) << endl;
    return 0;
}