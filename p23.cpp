#include <iostream>
#include <unordered_set>

using namespace std;

#define UPPER_BOUND 28123

bool is_abundant(int n) {
	if (n == 1) 
		return false;

	int sum_divisors = 1;
	int high = n;

	for (int d = 2; d < high; d++) {
		if (n % d == 0) {
			sum_divisors += d + (n / d != d) * (n / d);
			high = n / d;
		}
	}

	return sum_divisors > n;
}

int main() {
	unordered_set<int> abundant_nums;
	for (int n = 1; n <= UPPER_BOUND; n++) {
		if (is_abundant(n))
			abundant_nums.insert(n);
	}

	long long sum = 0;
	for (int n = 1; n <= UPPER_BOUND; n++) {
		bool num_cannot_be_expressed = true;

		for (auto abundant_num = abundant_nums.begin(); abundant_num != abundant_nums.end(); abundant_num++) {
			int diff = n - *abundant_num;
			if (abundant_nums.find(diff) != abundant_nums.end()) {
				num_cannot_be_expressed = false;
				break;
			}
		}

		if (num_cannot_be_expressed)
			sum += n;
	}

	cout << sum << endl;
	return 0;
}

