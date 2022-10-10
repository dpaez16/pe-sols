#include <bits/stdc++.h>

using namespace std;

#define N pow(10, 6)

unsigned sum_proper_divisors(unsigned n) {
    unordered_set<unsigned> factors;

    unsigned upper = sqrt(n);
    for (unsigned d = 1; d <= upper; d++) {
        if (n % d != 0) continue;

        factors.insert(d);
        factors.insert(n / d);
    }

    return accumulate(factors.begin(), factors.end(), 0) - n;
}

vector<int> sieve(int n) {
    vector<int> chain_length(n + 1, -1);
    chain_length[0] = -2;

    for (unsigned i = chain_length.size() - 1; i > 0; i--) {
        if (chain_length[i] != -1) continue;

        unordered_set<unsigned> chain;
        unsigned num = i;
        while (chain.find(num) == chain.end() && chain_length[num] == -1) {
            chain.insert(num);
            unsigned next_num = sum_proper_divisors(num);
            if (next_num >= chain_length.size() || next_num == num) {
                next_num = 0;
            }

            num = next_num;
        }

        int final_chain_length = chain_length[num] == -1 ? chain.size() : chain_length[0];
        for (unsigned elem : chain) {
            chain_length[elem] = final_chain_length;
        }
    }

    return chain_length;
}

int main() {
    vector<int> chain_length = sieve(N);
    int max_chain_length = *max_element(chain_length.begin(), chain_length.end());
    
    unsigned ans = chain_length.size();
    for (unsigned i = 0; i < chain_length.size(); i++) {
        if (chain_length[i] != max_chain_length) continue;

        ans = min(ans, i);
    }

    cout << ans << endl;
    return 0;
}