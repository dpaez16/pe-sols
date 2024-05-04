#include <bits/stdc++.h>

using namespace std;

const int N = 5 * pow(10, 6);
const int M = 27; // According to https://oeis.org/A173270/list, the 5 millionth xor prime occurs in degree 26, so 2^27 is our upper bound

int bit_length(long x) {
    if (x < 0) {
        x *= -1;
    }

    int bit_count = 0;
    while (x > 0) {
        x >>= 1;
        bit_count++;
    }

    return bit_count;
}

int main() {
    unsigned int size = pow(2, M);
    bool * is_prime = (bool *)calloc(size, sizeof(bool));
    memset(is_prime, true, size * sizeof(bool));
    
    is_prime[0] = false;
    is_prime[1] = false;

    const long upper = pow(2, M / 2 + 1);
    for (long p = 2; p < upper; p++) {
        if (!is_prime[p]) continue;

        long x = p;
        const int m = M - bit_length(p);
        const int inner_upper = 1 << (m + 1);

        for (int k = 1; k < inner_upper; k++) {
            x ^= p << __builtin_ctz(k); // gray code iteration
            
            if (x < size) {
                is_prime[x] = false;
            }
        }
    }

    int count = 0;
    for (unsigned i = 0; i < size; i++) {
        if (!is_prime[i]) continue;

        count++;
        if (count == N) {
            cout << i << endl;
            break;
        }
    }

    free(is_prime);
    return 0;
}
