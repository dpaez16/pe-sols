#include <bits/stdc++.h>

using namespace std;

#define N 1000

bool proper_right_triangle(int a, int b, int c) {
    if (c < b) return false;

    return (
        a < b + c &&
        b < c + a &&
        c < a + b && 
        pow(a, 2) + pow(b, 2) == pow(c, 2)
    );
}

int num_solutions(int p) {
    if (p == 0) return 0;
    
    int n_sols = 0;

    for (int a = 1; a < p; a++) {
        for (int b = a; b < p; b++) {
            int c = p - a - b;
            if (proper_right_triangle(a, b, c)) n_sols++;
        }
    }

    return n_sols;
}

int main() {
    int max_sols = 0;
    int opt_p = 0;

    for (int p = 1; p <= N; p++) {
        int n_sols = num_solutions(p);
        if (n_sols > max_sols) {
            max_sols = max(max_sols, n_sols);
            opt_p = p;
        }
    }

    cout << opt_p << endl;
    return 0;
}