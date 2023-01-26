#include <bits/stdc++.h>

using namespace std;

#define N 20
#define PAIR_TO_KEY(a, b) (10 * (a) + (b))

unsigned long long *** createDPArray() {
	unsigned long long *** dp = (unsigned long long ***)calloc(10, sizeof(unsigned long long **));

	for (int i = 0; i < 10; i++) {
		dp[i] = (unsigned long long **)calloc(10, sizeof(unsigned long long *));

		for (int j = 0; j < 10; j++) {
			dp[i][j] = (unsigned long long *)calloc(N + 1, sizeof(unsigned long long));
			dp[i][j][N] = 1;
		}
	}

	return dp;
}

void destroyDPArray(unsigned long long *** dp) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			free(dp[i][j]);
		}
		
		free(dp[i]);
	}

	free(dp);
}

vector<vector<int>> getTuples() {
	vector<vector<int>> tuples;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			for (int k = 0; k < 10; k++) {
				int s = i + j + k;
				
				if (s > 9) continue;

				tuples.push_back({i, j, k});
			}
		}
	}

	return tuples;
}

unordered_map<int, vector<int>> getMap(vector<vector<int>> & tuples) {
	unordered_map<int, vector<int>> digitsMap;

	for (vector<int> t : tuples) {
		int key = PAIR_TO_KEY(t[0], t[1]);

		if (digitsMap.find(key) == digitsMap.end()) digitsMap[key] = vector<int>();

		digitsMap[key].push_back(t[2]);
	}

	return digitsMap;
}

int main() {
	unsigned long long *** dp = createDPArray();
	vector<vector<int>> tuples = getTuples();
	unordered_map<int, vector<int>> digitsMap = getMap(tuples);

	for (int k = N - 1; k >= 0; k--) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				int key = PAIR_TO_KEY(i, j);
				vector<int> digits = digitsMap[key];

				for (int d : digits) {
					dp[i][j][k] += dp[j][d][k + 1];
				}
			}
		}
	}

	unsigned long long total = 0;

	for (vector<int> t : tuples) {
		if (t[0] == 0) continue;

		total += dp[t[1]][t[2]][3];
	}

	cout << total << endl;

	destroyDPArray(dp);
	return 0;
}
