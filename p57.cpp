#include <bits/stdc++.h>

using namespace std;

typedef pair<long double, long double> fraction;

#define ZERO fraction(0, 1)
#define N 1000

fraction inverse(fraction f) {
	return fraction(f.second, f.first);
}

fraction add_num(unsigned n, fraction & f) {
	long double top = f.first;
	long double bottom = f.second;
	
	return fraction(top + (n * bottom), bottom);
}

bool top_has_more_digits(fraction f) {
	string top = to_string(f.first);
	string bottom = to_string(f.second);
	
	return top.size() > bottom.size();
}

fraction calc_frac_helper(int n) {
	if (n == 0) return ZERO;

	fraction f = calc_frac_helper(n - 1);
	return inverse(add_num(2, f));
}

fraction calc_frac(int n_iterations) {
	fraction f = calc_frac_helper(n_iterations);
	return add_num(1, f);
}

int main() {
	int count = 0;

	for (int n = 1; n <= N; n++) {
		fraction f = calc_frac(n);
		if (top_has_more_digits(f)) count++;

	}

	cout << count << endl;
	return 0;
}

