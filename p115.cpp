#include <bits/stdc++.h>

using namespace std;

#define M 50
#define UPPER_BOUND pow(10, 6)

long double f(int n) {
	long double dp[n + 1];

	for (int i = 0; i <= n; i++) {
		if (i < M) {
			dp[i] = 1;
			continue;
		}

		long double acc = 0;
		int block_size = M;

		while (i - block_size - 1 >= 0) {
			acc += dp[i - block_size - 1];
			block_size++;
		}

		dp[i] = dp[i - 1] + acc + 1;
	}

	return dp[n];
}

int main() {
	int n = M;
	
	while (f(n) < UPPER_BOUND) {
		n++;
	}

	cout << n << endl;

	return 0;
}
