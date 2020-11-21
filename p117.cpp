#include <bits/stdc++.h>

using namespace std;

#define N       50
#define M_RED   2
#define M_GREEN 3
#define M_BLUE  4

long double f(int n) {
	long double dp[n + 1];
	dp[0] = 1;

	for (int i = 1; i <= n; i++) {
		dp[i] = dp[i - 1];
		
		if (i >= M_RED) dp[i] += dp[i - M_RED];
		if (i >= M_GREEN) dp[i] += dp[i - M_GREEN];
		if (i >= M_BLUE) dp[i] += dp[i - M_BLUE];
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
