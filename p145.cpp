#include <bits/stdc++.h>

using namespace std;

#define N 9

int main() {
    unsigned long long total = 0;

    for (int n = 1; n < N; n++) {
        if (n % 2 == 0) {
            int k = n / 2;
            total += 20 * pow(30, k - 1);
        } else if ((n - 1) % 4 == 0) {
            continue;
        } else if ((n - 3) % 4 == 0) {
            int k = (n - 3) / 4;
            total += 100 * pow(500, k);
        }
    }

    cout << total << endl;
    return 0;
}