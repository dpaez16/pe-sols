#include <bits/stdc++.h>

using namespace std;

#define MAX_N 2500

unsigned long long pentagonal_num(unsigned long long n) {
    return n * (3 * n - 1) / 2;
}

bool is_pentagonal_num(unsigned long long n) {
    unsigned long long j = 0;
    while (pentagonal_num(j) < n) j++;

    return pentagonal_num(j) == n;
}

int main() {
    unsigned long long min_diff = -1;

    for (unsigned long long j = 1; j <= MAX_N; j++) {
        for (unsigned long long k = j + 1; k <= MAX_N; k++) {
            unsigned long long p_j = pentagonal_num(j);
            unsigned long long p_k = pentagonal_num(k);

            if (is_pentagonal_num(p_k + p_j) && is_pentagonal_num(p_k - p_j)) {
                unsigned long long diff = p_k - p_j;
                min_diff = min(min_diff, diff);
            }
        }
    }

    cout << min_diff << endl;
    return 0;
}