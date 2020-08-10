#include <bits/stdc++.h>

using namespace std;

#define N 100

long long sum_nat_nums(long long n) {
	return n * (n + 1) / 2;
}

long long sum_squares(long long n) {
	return n * (n + 1) * (2 * n + 1) / 6;
}

int main() {
	long long sum_nat_num = sum_nat_nums(N);
	long long sum_sq = sum_squares(N);
	long long diff = pow(sum_nat_num, 2) - sum_sq;

	cout << diff << endl;
	return 0;
}
