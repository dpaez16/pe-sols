#include <bits/stdc++.h>

using namespace std;
using ull = unsigned long long;

#define NUM_L_VALS 12

/*
        k, m, n positive integers, m > n

        a = k * (m^2 - n^2)
        b = k * (2 * m * n)
        c = k * (m^2 + n^2)

        We want |a - 2 * b| = 1
        |a - 2 * b| = 1 <==> (a - 2 * b)^2 = 1
                         ==> k^2 * (m^2 - 4 * m * n - n^2)^2 = 1

                         ==> k = 1
                             Fix n and solve for m.
                         ==> (m^2 - 4 * m * n - n^2)^2 = 1
                         ==> m = {
                            -sqrt(5 * n^2 - 1) + 2 * n
                            sqrt(5 * n^2 - 1) + 2 * n
                            -sqrt(5 * n^2 + 1) + 2 * n
                            sqrt(5 * n^2 + 1) + 2 * n   // use this solution
                         }

                         Iterate process but with n = m.
*/
ull get_m(ull n) {
	return sqrt(5 * pow(n, 2) + 1) + 2 * n;
}

vector<ull> gen_triple(ull m, ull n) {
	ull m_sq = pow(m, 2);
	ull n_sq = pow(n, 2);
	return {
		m_sq - n_sq,
		2 * m * n,
		m_sq + n_sq
	};
}

int main() {
	ull ans = 0;
	ull n = 1;

	for (int it = 0; it < NUM_L_VALS; it++) {
		ull m = get_m(n);
		vector<ull> pythag_triple = gen_triple(m, n);
		ans += pythag_triple[2];
		n = m;
	}

	cout << ans << endl;
	return 0;
}
