#include <bits/stdc++.h>

using namespace std;

#define D pow(10, 3)

long double solve_eq(int d) {
    if (pow((int)sqrt(d), 2) == d) return 0;

    long double y = 1;
    long double x;

    while (true) {
        long double rhs = 1 + d * pow(y, 2);
        x = floor(sqrt(rhs));
        if (pow(x, 2) == rhs) break;
        y++;
    }

    return x;
}

int main() {
    long double max_x = 0;
    int optimal_d = 0;

    for (int d = 1; d <= 400; d++) {
        long double x = solve_eq(d);

        if (x > max_x) {
            max_x = x;
            optimal_d = d;
        }
        
        cout << d << ' ' << to_string(x) << endl;
    }

    return 0;
}