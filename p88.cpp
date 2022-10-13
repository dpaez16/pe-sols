#include <bits/stdc++.h>

using namespace std;

#define K 12000
#define N_THREADS 8
#define K_DELTA 100
#define MIN(x,y) ((x) < (y) ? (x) : (y))

mutex curr_k_mtx;
unordered_set<unsigned> a_vals = {};
unsigned curr_k = 2;

vector<unsigned> get_factors(unsigned n) {
    unordered_set<unsigned> factors;
    unsigned upper = sqrt(n);
    for (unsigned factor = 2; factor <= upper; factor++) {
        if (n % factor == 0) {
            factors.insert(factor);
            factors.insert(n / factor);
        }
    }

    vector<unsigned> sorted_factors(factors.begin(), factors.end());
    sort(sorted_factors.begin(), sorted_factors.end());
    return sorted_factors;
}

bool helper(unsigned nums_used, unsigned accProd, unsigned accSum, unsigned target, unsigned k, vector<unsigned> & factors) {
    if (nums_used == k || accProd == target) {
        unsigned ones = k >= nums_used ? k - nums_used : 0;
        return (accProd == target) && (accSum + ones == accProd);
    }

    unsigned upper = target / accProd;
    for (unsigned factor : factors) {
        if (factor > upper) break;

        if (helper(nums_used + 1, accProd * factor, accSum + factor, target, k, factors)) {
            return true;
        }
    }

    return false;
}

unsigned a(unsigned k, vector<vector<unsigned>> & factors_cache) {
    for (unsigned k_val = 1; k_val <= 2 * k; k_val++) {
        vector<unsigned> factors = factors_cache[k_val];
        if (helper(0, 1, 0, k_val, k, factors)) {
            return k_val;
        }
    }

    return 0;
}

unsigned get_k() {
	unsigned k;

	curr_k_mtx.lock();
    k = curr_k <= K ? curr_k : 0;
    curr_k += K_DELTA;
	curr_k_mtx.unlock();
	
	return k;
}

void work(vector<vector<unsigned>> & factors_cache) {
    while (true) {
        unsigned k = get_k();
        if (k == 0) break;

        unsigned upper = MIN(k + K_DELTA, K + 1);
        for (unsigned n = k; n < upper; n++) {
            a_vals.insert(a(n, factors_cache));
        }
    }
}

int main() {
    vector<vector<unsigned>> factors_cache(2 * K + 1);

    for (unsigned k = 0; k <= 2 * K; k++) {
        factors_cache[k] = get_factors(k);
    }

    thread threads[N_THREADS];
    for (int idx = 0; idx < N_THREADS; idx++) {
        threads[idx] = thread(work, ref(factors_cache));
    }

    for (int idx = 0; idx < N_THREADS; idx++) {
        threads[idx].join();
    }
    
    unsigned sum = 0;
    for (unsigned a_val : a_vals) {
        sum += a_val;
    }

    cout << sum << endl;
    return 0;
}