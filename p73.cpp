#include <bits/stdc++.h>

using namespace std;

#define UPPER       12000
#define LEFT_N      1
#define LEFT_D      3
#define RIGHT_N     1
#define RIGHT_D     2

class Fraction {
public:
    double n;
    double d;

    Fraction(int n, int d) {
        this->n = n;
        this->d = d;
    }

    bool operator==(const Fraction & rhs) const {
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

    double val() const {
        return this->n / this->d;
    }
};

struct frac_hash {
    size_t operator() (const Fraction & f) const {
        return hash<double>()(f.val());
    }
};

bool eq_fracs(Fraction & lhs, Fraction & rhs) {
    return lhs == rhs;
}

int main() {
    Fraction left(LEFT_N, LEFT_D);
    Fraction right(RIGHT_N, RIGHT_D);
    unordered_set<Fraction, frac_hash> fracs;

    for (int d = 0; d <= UPPER; d++) {
        int begin_n = int((left.n * d) / left.d);
        for (int n = begin_n; n < d; n++) {
            Fraction frac(n, d);
            if (frac <= left) continue;
            if (frac >= right) break;

            fracs.insert(frac);
        }
    }

    cout << fracs.size() << endl;

    return 0;
}