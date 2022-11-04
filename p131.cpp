#include <bits/stdc++.h>

using namespace std;

const unsigned N = pow(10, 6);
const unsigned CUBE_LIMIT = pow(6, 3) * N + N;

vector<unsigned> sieve(unsigned n) {
    unsigned length = n + 1;
    bool * is_prime = (bool *)calloc(length, sizeof(bool));
    memset(is_prime, true, length * sizeof(bool));
    is_prime[0] = false;
    is_prime[1] = false;
    vector<unsigned> primes;

    for (unsigned p = 0; p < length; p++) {
        if (!is_prime[p]) continue;

        primes.push_back(p);
        for (unsigned k = 2 * p; k < length; k += p) {
            is_prime[k] = false;
        }
    }

    primes.shrink_to_fit();
    return primes;
}

unordered_set<unsigned> get_cubes(unsigned n) {
    unordered_set<unsigned> cubes;
    unsigned i = 1;

    while (true) {
        unsigned i_3 = pow(i++, 3);
        if (i_3 > n) break;

        cubes.insert(i_3);
    }

    return cubes;
}

/**
 *      n^3 + n^2 * p is a cube  <==>  n is a cube
 *      n = k^3
 *      ==> n^3 + n^2 * p = (k^3)^3 + (k^3)^2 * p
 *                        = k^6(k^3 + p)
 * 
 *      k^6(k^3 + p) is a cube  <==>  (k^3 + p) is a cube
 * 
 *      for each p, k \in [cbrt(p), 6 * cbrt(p)]
 *      ==> max cube needed is (6 * cbrt(N))^3 + N
*/
int main() {
    vector<unsigned> primes = sieve(N);
    unordered_set<unsigned> cubes = get_cubes(CUBE_LIMIT);

    unsigned count = 0;
    for (unsigned p : primes) {
        unsigned left = cbrt(p);
        unsigned right = 6 * left;

        for (unsigned k = left; k <= right; k++) {
            unsigned val = pow(k, 3) + p;
            if (cubes.find(val) != cubes.end()) {
                count++;
                break;
            }
        }
    }

    cout << count << endl;
    return 0;
}