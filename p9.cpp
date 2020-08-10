#include <bits/stdc++.h>

using namespace std;

#define SUM 1000

int main() {
	for (int a = 1; a < 1000; a++) {
		for (int b = a + 1; b < 1000; b++) {
			int c = SUM - b - a;
			if (pow(a, 2) + pow(b, 2) == pow(c, 2)) {
				cout << a * b * c << endl;
				break;
			}
		}
	}

	return 0;
}
