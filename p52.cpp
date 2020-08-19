#include <bits/stdc++.h>

using namespace std;

#define MAX_MULTIPLIER 2

bool num_has_property(unsigned long long & n) {
    vector<string> multiples;
    for (int f = 1; f <= MAX_MULTIPLIER; f++) {
        string f_times_n_str = to_string(f * n);
        sort(f_times_n_str.begin(), f_times_n_str.end());

        multiples.push_back(f_times_n_str);
    }

    for (unsigned idx = 1; idx < multiples.size(); idx++) {
        if (multiples[0] != multiples[idx]) return false;
    }

    return true;
}

int main() {
    unsigned long long n = 1;

    while (!num_has_property(n)) n++;

    cout << n << endl;
    return 0;
}