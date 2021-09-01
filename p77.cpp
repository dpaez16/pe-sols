#include <bits/stdc++.h>

using namespace std;

#define N 100
#define UPPER_BOUND 5000

vector<int> prime_sieve(int n) {
    bool is_prime[n + 1];
    memset(is_prime, true, sizeof(is_prime));
    is_prime[0] = false;
    is_prime[1] = false;

    vector<int> primes;
    for (int p = 0; p <= n; p++) {
        if (!is_prime[p]) continue;
        
        primes.push_back(p);
        for (int k = 2 * p; k <= n; k += p) {
            is_prime[k] = false;
        }
    }

    return primes;
}

int num_ways(int n, vector<int> primes) {
    int dp[n + 1];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;

    for (int p : primes) {
        for (int k = p; k <= n; k++) {
            dp[k] += dp[k - p];
        }
    }

    return dp[n];
}

int main() {
    vector<int> primes = prime_sieve(N);
    int n = 1;

    while (num_ways(n, primes) <= UPPER_BOUND) {
        n++;
    }

    cout << n << endl;
    return 0;
}