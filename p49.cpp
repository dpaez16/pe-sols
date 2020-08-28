#include <bits/stdc++.h>

using namespace std;

#define N_DIGITS 4
#define LOWER_BOUND pow(10, N_DIGITS - 1)
#define UPPER_BOUND pow(10, N_DIGITS)
#define FORBIDDEN_PRIME 1487

bool is_prime(int & n) {
	if (n <= 1) return false;
	if (n == 2) return true;
	if (n % 2 == 0) return false;

	for (int d = 3; d <= floor(sqrt(n)); d++) {
		if (n % d == 0) return false;
	}

	return true;
}

bool is_permutation(int a, int b) {
    string a_str = to_string(a);
    string b_str = to_string(b);

    sort(a_str.begin(), a_str.end());
    sort(b_str.begin(), b_str.end());

    return a_str == b_str;
}

void print_vector(vector<int> & v) {
    string v_str = "";
    for (int elem : v) {
        v_str += to_string(elem) + ", ";
    }

    v_str = v_str.substr(0, v_str.size() - 2);
    cout << v_str << endl;
}

void print_ans(vector<int> & v, int i, int j, int k) {
    string ans = to_string(v[i]) + to_string(v[j]) + to_string(v[k]);
    cout << ans << endl;
}

int main() {
    vector<int> primes;
    set<int> used_primes;

    for (int n = LOWER_BOUND; n < UPPER_BOUND; n++) {
        if (is_prime(n)) primes.push_back(n);
    }

    vector<vector<int>> grouped_primes;
    for (unsigned i = 0; i < primes.size(); i++) {
        int prime = primes[i];

        if (used_primes.find(prime) != used_primes.end()) continue;

        used_primes.insert(prime);
        vector<int> group_primes = {prime};

        for (unsigned j = i + 1; j < primes.size(); j++) {
            int other_prime = primes[j];

            if (used_primes.find(other_prime) != used_primes.end()) continue;
            if (!is_permutation(prime, other_prime)) continue;

            used_primes.insert(other_prime);
            group_primes.push_back(other_prime);
        }

        sort(group_primes.begin(), group_primes.end());
        grouped_primes.push_back(group_primes);
    }

    for (auto group_primes : grouped_primes) {
        if (group_primes[0] == FORBIDDEN_PRIME) continue;

        for (unsigned i = 0; i < group_primes.size(); i++) {
            for (unsigned j = i + 1; j < group_primes.size(); j++) {
                for (unsigned k = j + 1; k < group_primes.size(); k++) {
                    int diff = group_primes[k] - group_primes[j];
                    int diff2 = group_primes[j] - group_primes[i];

                    if (diff != diff2) continue;

                    print_ans(group_primes, i, j, k);
                }
            }
        }
    }

    return 0;
}
