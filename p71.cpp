#include <bits/stdc++.h>

using namespace std;

#define UPPER   pow(10, 6)
#define N       3
#define D       7

class Fraction {
public:
    double n;
    double d;

    Fraction(int n, int d) {
        this->n = n;
        this->d = d;
    }

    bool operator==(Fraction & rhs) {
        return this->n * rhs.d == rhs.n * this->d;
    }

    bool operator<(Fraction & rhs) {
        return this->n * rhs.d < rhs.n * this->d;
    }

    bool operator>(Fraction & rhs) {
        return this->n * rhs.d > rhs.n * this->d;
    }

    bool operator<=(Fraction & rhs) {
        return *this < rhs || *this == rhs;
    }

    bool operator>=(Fraction & rhs) {
        return *this > rhs || *this == rhs;
    }

    string to_str() {
        return to_string((int)this->n) + "/" + to_string((int)this->d);
    }
};

int main() {
    Fraction left(0, 1);
    Fraction right(N, D);
    for (int d = 0; d <= UPPER; d++) {
        int begin_n = int((left.n * d) / left.d);
        for (int n = begin_n; n < d; n++) {
            Fraction frac(n, d);
            if (frac <= left) continue;
            if (frac >= right) break;

            left = frac;
            break;
        }
    }

    cout << left.to_str() << endl;

    return 0;
}