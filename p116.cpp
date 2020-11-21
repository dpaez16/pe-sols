#include <bits/stdc++.h>

using namespace std;

#define N       50 
#define M_RED   2
#define M_GREEN 3
#define M_BLUE  4

long double f(int n, int m) {
	long double dp[n + 1];
	for (int i = 0; i <= n; i++) {
		if (i == 0) {
			dp[i] = 1;
			continue;
		}

		if (i < m) {
			dp[i] = 0;
			continue;
		}

		if (i == m) {
			dp[i] = 1;
			continue;
		}

		dp[i] = dp[i - 1] + dp[i - m] + 1;
	}

	return dp[n];
}

long double p(int n) {
	return f(n, M_RED) + f(n, M_GREEN) + f(n, M_BLUE);
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
	long double ans = p(N);
	string formatted_ans = format_ans(ans);
	cout << formatted_ans << endl;

	return 0;
}
