#include <bits/stdc++.h>

using namespace std;

#define N 50
#define M 3

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

string format_ans(long double ans) {
	string ans_str = to_string(ans);
	size_t idx = ans_str.find(".");

	if (idx != string::npos) {
		ans_str = ans_str.substr(0, idx);
	}

	return ans_str;
}

int main() {
	long double ans = f(N);
	string formatted_ans = format_ans(ans);
	cout << formatted_ans << endl;

	return 0;
}
