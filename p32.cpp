#include <bits/stdc++.h>

using namespace std;

#define N pow(10, 5)

bool is_pandigital(string & n_str) {
    if (n_str.size() != 9) return false;

    unordered_set<char> digits;
    
    for (char c : n_str) {
        if (digits.find(c) != digits.end() || c == '0') return false;
        digits.insert(c);
    }

    return true;
}

int main() {
    unsigned long long sum = 0;
    set<int> prods;
    
    for (int a = 1; a < N; a++) {
        for (int b = a + 1; b < N; b++) {
            int c = a * b;

            string a_str = to_string(a);
            string b_str = to_string(b);
            string c_str = to_string(c);

            string n_str = a_str + b_str + c_str;

            if (prods.find(c) != prods.end()) continue;
            if (n_str.size() > 9) break;
            if (is_pandigital(n_str)) {
                prods.insert(c);
                sum += c;
            }
        }
    }

    cout << sum << endl;
    return 0;
}