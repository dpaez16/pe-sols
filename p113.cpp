#include <bits/stdc++.h>

using namespace std;

#define N_DIGITS 100
#define PAIR(x, y) pair<long double, int>(x, y)

struct pair_hash {
	size_t operator() (const pair<long double, int> & p) const {
		ostringstream out;
		out << p.first << ',' << p.second;
		return hash<string>()(out.str());
	}
};

string format_ans(long double & ans) {
    string ans_str = to_string(ans);
    size_t pos = ans_str.find('.');
    if (pos != ans_str.npos) ans_str = ans_str.substr(0, pos);

    return ans_str;
}


int main() {
    unordered_map<pair<long double, int>, long double, pair_hash> num_increasing;

    for (long double num_digits = 1; num_digits <= N_DIGITS; num_digits++) {
        for (int starting_digit = 1; starting_digit <= 9; starting_digit++) {
            pair<long double, int> curr(num_digits, starting_digit);
            unsigned num_choices = 9 - starting_digit + 1;

            if (num_digits == 1) num_increasing[curr] = num_choices;
            else {
                long double total = 0;

                for (int digit = starting_digit; digit <= 9; digit++) {
                    total += num_increasing[PAIR(num_digits - 1, digit)];
                }

                num_increasing[curr] = total + num_choices;
            }
        }
    }

    unordered_map<pair<long double, int>, long double, pair_hash> num_decreasing;

    for (long double num_digits = 1; num_digits <= N_DIGITS; num_digits++) {
        for (int starting_digit = 0; starting_digit <= 9; starting_digit++) {
            pair<long double, int> curr(num_digits, starting_digit);
            unsigned num_choices = 9 - starting_digit + 1;

            if (num_digits == 1) num_decreasing[curr] = num_choices;
            else {
                long double total = 0;

                for (int digit = starting_digit; digit <= 9; digit++) {
                    total += num_decreasing[PAIR(num_digits - 1, digit)];
                }

                num_decreasing[curr] = total + num_choices;
            }
        }

        // remove n-digit "0"
        num_decreasing[PAIR(num_digits, 0)]--;
    }

    long double n_increasing = num_increasing[PAIR(N_DIGITS, 1)];
    long double n_decreasing = num_decreasing[PAIR(N_DIGITS, 0)];
    long double n_increasing_and_decreasing = 9 * N_DIGITS;
    long double num_not_bouncy = n_increasing + n_decreasing - n_increasing_and_decreasing;

    cout << format_ans(num_not_bouncy) << endl;

    return 0;
}