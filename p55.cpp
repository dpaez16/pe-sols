#include <bits/stdc++.h>

using namespace std;

#define MAX_ITERATIONS 50
#define N pow(10, 4)

string fix_string(string & str) {
    size_t pos = str.find(".");
    if (pos == str.npos) return str;

    return str.substr(0, pos);
}

long double reverse_num(long double & n) {
    string n_str = to_string(n);
    n_str = fix_string(n_str);
    reverse(n_str.begin(), n_str.end());

    return stold(n_str);
}

bool is_palindrome(long double & n) {
    string n_str = to_string(n);
    n_str = fix_string(n_str);
    if (n_str.size() <= 1) return true;

    for (unsigned i = 0; i < n_str.size() / 2; i++) {
        if (n_str[i] != n_str[n_str.size() - 1 - i]) return false;
    }

    return true;
}

bool is_lychrel_number(long double & n) {
    long double curr = n;

    for (int i = 1; i < MAX_ITERATIONS; i++) {
        curr = curr + reverse_num(curr);
        if (is_palindrome(curr)) return false;
    }

    return true;
}

int main() {
    long double count = 0;

    for (long double n = 1; n < N; n++) {
        if (is_lychrel_number(n)) count++;
    }

    cout << count << endl;
    return 0;
}