#include <bits/stdc++.h>

using namespace std;

#define N 1000000

void add_num(string & s, unsigned long long & n) {
    string n_str = to_string(n);
    s += n_str;
}

int main() {
    string buff = "";
    unsigned long long n = 1;

    while (buff.size() <= N) {
        add_num(buff, n);
        n++;
    }

    int idx = 1;
    int prod = 1;

    while (idx <= N) {
        prod *= buff[idx - 1] - '0';
        idx *= 10;
    }
    
    cout << prod << endl;
    return 0;
}