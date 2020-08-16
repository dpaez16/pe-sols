#include <bits/stdc++.h>

using namespace std;

#define N pow(10, 6)
#define N_THREADS 8

mutex ans_mtx, curr_n_mtx;
bool found_ans = false;
unsigned int num_most_consecutive_primes = 0;
unsigned int optimal_p = 0;
unsigned int curr_n = N;

bool is_prime(unsigned int & n) {
	if (n <= 1) return false;
	if (n == 2) return true;
	if (n % 2 == 0) return false;

	for (unsigned int d = 3; d <= floor(sqrt(n)) + 1; d++) {
		if (n % d == 0) return false;
	}

	return true;
}

void set_answer(unsigned n, unsigned p, unsigned i, unsigned j) {
	ans_mtx.lock();

	if (n > num_most_consecutive_primes) {
		num_most_consecutive_primes = n;
		optimal_p = p;
		found_ans = true;
		printf("%d consecutive primes (%d - %d) sum to %d\n", n, i, j, p);
	}

	ans_mtx.unlock();
}

unsigned int get_n() {
	unsigned int n;

	curr_n_mtx.lock();
	n = curr_n--;
	curr_n_mtx.unlock();
	
	return n;
}

void consecutive_prime_sums(vector<unsigned int> & primes, set<unsigned int> & primes_set) {
	while (!found_ans) {
		unsigned int n = get_n();
		unsigned n_primes = primes.size();

		if (n > n_primes) continue;
		if (found_ans) return;

		unsigned long long sum = 0;
		unsigned int i = 0, j = 0;

		while (j < n) {
			if (found_ans) return;
			sum += primes[j++];
		}

		j--;

		while (true) {
			if (found_ans) return;
			if (sum >= N) break;
			if (primes_set.find(sum) != primes_set.end()) {
				set_answer(n, sum, i, j);
			}

			if (j + 1 == n_primes) break;

			sum += primes[++j];
			sum -= primes[i++];
		}
	}
}

vector<unsigned int> get_primes() {
	vector<unsigned int> primes = {2};

	for (unsigned int p = 3; p < N; p += 2) {
		if (!is_prime(p)) continue;
		primes.push_back(p);
	}

	return primes;
}

int main() {
	vector<unsigned int> primes = get_primes();
	set<unsigned int> primes_set(primes.begin(), primes.end());

	thread threads[N_THREADS];
	for (int idx = 0; idx < N_THREADS; idx++) {
		threads[idx] = thread(consecutive_prime_sums, ref(primes), ref(primes_set));
	}

	for (int idx = 0; idx < N_THREADS; idx++) {
		threads[idx].join();
	}

	return 0;
}

