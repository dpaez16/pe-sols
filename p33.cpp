#include <bits/stdc++.h>

using namespace std;

#define LOWER_BOUND 10
#define UPPER_BOUND 99

vector<int> convert_to_vec(int a) {
    string a_str = to_string(a);
    vector<int> digits;

    for (char c : a_str) {
        int digit = c - '0';
        digits.push_back(digit);
    }

    return digits;
}

int convert_to_int(vector<int> & digits) {
    string digits_str = "";
    for (int digit : digits) {
        digits_str += to_string(digit);
    }

    if (digits_str.size() == 0) return 1;

    return stoi(digits_str);
}

bool has_property(int a, int b) {
    if (a % 10 == 0 && b % 10 == 0) return false;

    vector<int> a_digits = convert_to_vec(a);
    vector<int> b_digits = convert_to_vec(b);
    bool cancel_was_done = false;

    for (int i = 0; i <= 9; i++) {
        auto digit_in_a = find(a_digits.begin(), a_digits.end(), i);
        auto digit_in_b = find(b_digits.begin(), b_digits.end(), i);
        
        if (digit_in_a == a_digits.end() || digit_in_b == b_digits.end()) continue;

        a_digits.erase(digit_in_a);
        b_digits.erase(digit_in_b);
        cancel_was_done = true;
    }

    if (!cancel_was_done) return false;

    int a_rem = convert_to_int(a_digits);
    int b_rem = convert_to_int(b_digits);
    double div_rem = 1.0 * a_rem / b_rem;
    double div = 1.0 * a / b;

    return div == div_rem;
}

int main() {
    int numerator = 1;
    int denominator = 1;

    for (int a = LOWER_BOUND; a < UPPER_BOUND; a++) {
        for (int b = a + 1; b <= UPPER_BOUND; b++) {
            if (has_property(a, b)) {
                numerator *= a;
                denominator *= b;
            }
        }
    }

    double div = 1.0 * numerator / denominator;
    int ans = 1 / div;
    cout << numerator << " / " << denominator << " = ";
    cout << div << " = 1 / " << ans << endl;
    return 0;
}
