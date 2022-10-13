#include <bits/stdc++.h>

using namespace std;
using ull = unsigned long long;

const ull A = 1504170715041707;
const ull M = 4503599627370517;

int main() {
	ull left = A;
	ull right = A;
	ull total = A;

	while (left > 0) {
		ull next = (left % M + right % M) % M;
		if (next < left) {
			left = next;
			total += left;
		} else {
			right = next;
		}
	}

	cout << total << endl;

	return 0;
}