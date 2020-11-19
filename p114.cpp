#include <bits/stdc++.h>

using namespace std;

#define N 50

long double factorial(int n) {
	if (n <= 1) {
		return 1;
	}

	long double f = 1;

	for (int k = 2; k <= n; k++) {
		f *= k;
	}

	return f;
}

long double binomial(int n, int m) {
	return factorial(n) / (factorial(m) * factorial(n - m));
}

long double a(int n) {
	long double c = 0;

	for (int k = 0; k <= floor(n / 4); k++) {
		c += binomial(n - 2 * k, 2 * k);
	}

	return c;
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
	long double ans = a(N + 1);
	string formatted_ans = format_ans(ans);
	cout << formatted_ans << endl;

	return 0;
}
