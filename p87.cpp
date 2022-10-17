#include <bits/stdc++.h>

using namespace std;

const unsigned N = 50 * pow(10, 6);

unsigned nth_root(unsigned x, unsigned n) {
    return pow(x, 1.0 / n);
}

int bisect_right(vector<unsigned> & arr, unsigned x) {
    int i = 0;
    int j = arr.size() - 1;

    while (i <= j) {
        int m = i + (j - i) / 2;
        if (arr[m] == x) return m + 1;
        else if (arr[m] < x) i = m + 1;
        else j = m - 1;
    }

    return i;
}

vector<unsigned> sieve(unsigned n) {
    unsigned size = n + 1;
    bool * is_prime = (bool *)calloc(size, sizeof(bool));
    memset(is_prime, true, size);
    is_prime[0] = false;
    is_prime[1] = false;

    vector<unsigned> primes;
    for (unsigned p = 0; p < size; p++) {
        if (!is_prime[p]) continue;

        primes.push_back(p);
        for (unsigned k = 2 * p; k < size; k += p) {
            is_prime[k] = false;
        }
    }

    free(is_prime);
    primes.shrink_to_fit();
    return primes;
}

vector<unsigned> get_primes_to_p(vector<unsigned> & primes, unsigned p, unsigned upper_bound) {
    vector<unsigned> primes_p;
    unsigned upper_idx = bisect_right(primes, nth_root(upper_bound, p));

    for (unsigned i = 0; i < upper_idx; i++) {
        primes_p.push_back(pow(primes[i], p));
    }

    primes_p.shrink_to_fit();
    return primes_p;
}

int main() {
    vector<unsigned> primes = sieve(N);
    vector<unsigned> primes_2 = get_primes_to_p(primes, 2, N);
    vector<unsigned> primes_3 = get_primes_to_p(primes, 3, N);
    vector<unsigned> primes_4 = get_primes_to_p(primes, 4, N);

    unordered_set<unsigned> sums;

    for (unsigned p2 : primes_2) {
        for (unsigned p3 : primes_3) {
            for (unsigned p4 : primes_4) {
                unsigned sum = p2 + p3 + p4;
                if (sum > N) break;

                sums.insert(sum);
            }
        }
    }

    cout << sums.size() << endl;
    return 0;
}