#include <bits/stdc++.h>

using namespace std;

#define N 30

struct tuple_hash {
	size_t operator() (const tuple<unsigned, unsigned, unsigned, unsigned> & t) const {
		ostringstream out;
		out << get<0>(t) << ',' << get<1>(t) << ',' << get<2>(t) << ',' << get<3>(t);
		return hash<string>()(out.str());
	}
};

int main() {
    unordered_map<tuple<int, int, int, int>, unsigned, tuple_hash> dp;
	for (int n = N; n >= 0; n--) {
		for (int prev_l = -1; prev_l < n; prev_l++) {
			for (int n_m_1 = 0; n_m_1 <= 2; n_m_1++) {
				for (int n_m_2 = 0; n_m_2 <= 2; n_m_2++) {
					const tuple<int, int, int, int> t(n, prev_l, n_m_1, n_m_2);
					if (n == N) {
						dp[t] = 1;
						continue;
					}

					vector<unsigned> choices = {0, 1};
					if (n_m_1 == 1 && n_m_2 == 1) {
						choices.pop_back();
					}
					if (prev_l == -1) {
						choices.push_back(2);
					}

					dp[t] = 0;
					for (unsigned choice : choices) {
						dp[t] += dp[{n + 1, choice == 2 ? n : prev_l, choice, n_m_1}];
					}
				}
			}
		}
	}

	cout << dp[{0, -1, 0, 0}] << endl;

    return 0;
}