#include <bits/stdc++.h>

using namespace std;

#define N 1000

int main() {
	int sum = 0;
	for (int n = 1; n < N; n++) {
		if (n % 3 == 0 || n % 5 == 0) {
			sum += n;
		}
	}

	cout << sum << endl;

	return 0;
}
