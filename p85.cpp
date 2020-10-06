#include <bits/stdc++.h>

using namespace std;

#define TARGET_N_RECTS 2000000
#define M 100
#define N 100


int num_rects(int m, int n) {
	int n_rects = 0;

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			n_rects += (m - i) * (n - j);
		}
	}

	return n_rects;
}


int main() {
	int best_area = 0, smallest_abs_diff = INT_MAX;

	for (int m = 1; m < M; m++) {
		for (int n = 1; n < N; n++) {
			int n_rects = num_rects(m, n);
			int area = m * n;
			int abs_diff = abs(n_rects - TARGET_N_RECTS);

			if (smallest_abs_diff > abs_diff) {
				smallest_abs_diff = abs_diff;
				best_area = area;
			}
		}
	}

	cout << best_area << endl;

	return 0;
}
