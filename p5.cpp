#include <bits/stdc++.h>

using namespace std;

#define N 20

int main() {
	long long n = 1;

	while (true) {
		bool is_evenly_divisible = true;
		for (int factor = 1; factor <= N; factor++) {
			if (n % factor != 0) {
				is_evenly_divisible = false;
				break;
			}
		}

		if (is_evenly_divisible)
			break;

		n++;
	}

	cout << n << endl;

	return 0;
}
