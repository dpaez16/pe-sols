#include <bits/stdc++.h>

using namespace std;

#define UPPER_BOUND 4000000

int main() {
	int f_n_m_2 = 0, f_n_m_1 = 1;
	int f_n;
	int sum = 0;

	while ((f_n = f_n_m_2 + f_n_m_1) < UPPER_BOUND) {
		if (f_n % 2 == 0) {
			sum += f_n;
		}

		f_n_m_2 = f_n_m_1;
		f_n_m_1 = f_n;
	}

	cout << sum << endl;

	return 0;
}
