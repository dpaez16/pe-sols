#include <bits/stdc++.h>

using namespace std;

#define MIN_N 285

unsigned long long triangular_num(unsigned long long n) {
    return n * (n + 1) / 2;
}

unsigned long long pentagonal_num(unsigned long long n) {
    return n * (3 * n - 1) / 2;
}

unsigned hexagonal_num(unsigned long long n) {
    return n * (2 * n - 1);
}

unsigned long long is_pentagonal_num(unsigned long long a, unsigned long long n) {
    unsigned long long j = n;
    
    while (pentagonal_num(j) > a) j--;

    if (pentagonal_num(j) == a) return j;
    else return 0;
}

unsigned long long is_hexagonal_num(unsigned long long a, unsigned long long n) {
    unsigned long long j = n;
    
    while (hexagonal_num(j) > a) j--;

    if (hexagonal_num(j) == a) return j;
    else return 0;
}

int main() {
    unsigned long long n_triangular = MIN_N + 1;
    
    while (true) {
        unsigned long long tri_num = triangular_num(n_triangular);
        unsigned long long n_pentagonal = is_pentagonal_num(tri_num, n_triangular);

        if (n_pentagonal == 0) {
            n_triangular++;
            continue;
        }

        unsigned long long pent_num = pentagonal_num(n_pentagonal);
        unsigned long long n_hexagonal = is_hexagonal_num(pent_num, n_pentagonal);

        if (n_hexagonal != 0) {
            cout << tri_num << endl;
            break;
        }

        n_triangular++;
    }

    return 0;
}