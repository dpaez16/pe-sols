#include <bits/stdc++.h>

using namespace std;
using ull = unsigned long long;

ull get_n_value(ull n) {
    for (ull x = 1; x <= pow(10, 3); x++) {
        ull smaller_n = n / pow(5, x);
        if (smaller_n * pow(5, x) == n) {
            if (smaller_n % 2500 != 0) {
                return n / pow(5, x - 1);
            }
        }
    }

    return 0;
}

ull f(ull n) {
    ull x = 1;
    ull m = pow(10, 7);

    for (ull d = 1; d <= n; d++) {
        x *= d;
        while (x % 10 == 0) {
            x /= 10;
        }

        x = fmod(x, m);
    }

    return fmod(x, pow(10, 5));
}

int main() {
    ull n = get_n_value(pow(10, 12));
    cout << f(n) << endl;

    return 0;
}