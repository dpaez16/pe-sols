#include <bits/stdc++.h>

using namespace std;

#define N 25

struct hash_pair {
    size_t operator()(const pair<int, int> & p) const {
        auto hash1 = hash<int>{}(p.first);
        auto hash2 = hash<int>{}(p.second);

        if (hash1 != hash2) {
            return hash1 ^ hash2;
        }

        return hash1;
    }
};

double num_winning_games(int n) {
    unordered_map<pair<int, int>, double, hash_pair> dp;

    for (int k = 0; k <= n; k++) {
        for (int acc = -n; acc <= n; acc++) {
            auto p = make_pair(k, acc);
            if (k == 0) {
                dp[p] = acc > 0 ? 1 : 0;
            } else {
                auto choose_blue = make_pair(k - 1, acc + 1);
                auto choose_red = make_pair(k - 1, acc - 1);
                dp[p] = dp[choose_blue] + k * dp[choose_red];
            }
        }
    }

    return dp[make_pair(n, 0)];
}

double num_games(int n) {
    double ans = 1;
    for (int k = 1; k <= n + 1; k++) {
        ans *= k;
    }

    return ans;
}

double winning_prob(int n) {
    return num_winning_games(n) / num_games(n);
}

string format_ans(double & n) {
	string ans_str = to_string(n);
	size_t pos = ans_str.find('.');
	if (pos != ans_str.npos) ans_str = ans_str.substr(0, pos);

	return ans_str;
}

int main() {
    double p = winning_prob(N);
    double winnings = floor(1.0d / p);
    cout << format_ans(winnings) << endl;

    return 0;
}