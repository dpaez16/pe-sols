#include <bits/stdc++.h>

using namespace std;

#define AMOUNT_PENCE 200
#define PAIR(r, c) pair<int, int>(r, c)

// coin amounts in pence
vector<int> coins = {1, 2, 5, 10, 20, 50, 100, 200};

struct pair_hash {
	size_t operator() (const pair<int, int> & p) const {
		ostringstream out;
		out << p.first << ',' << p.second;
		return hash<string>()(out.str());
	}
};

int main() {
    unordered_map<pair<int, int>, int, pair_hash> num_ways;
    int n = coins.size();

    for (int i = n; i >= 0; i--) {
        for (int amount = 0; amount <= AMOUNT_PENCE; amount++) {
            pair<int, int> p(i, amount);

            if (amount == 0) num_ways[p] = 1;
            else if (i == n && amount > 0) num_ways[p] = 0;
            else {
                int k = 0;
                
                while (amount - k * coins[i] >= 0) {
                    num_ways[p] += num_ways[PAIR(i + 1, amount - k * coins[i])];
                    k++;
                }
            }
        }
    }

    cout << num_ways[PAIR(0, AMOUNT_PENCE)] << endl;

    return 0;
}
