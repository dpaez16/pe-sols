#include <bits/stdc++.h>

using namespace std;

#define N 678910
#define TARGET 123

double get_special_float(int num) {
    string num_str = to_string(num);
    string special_str = num_str.substr(0, 1) + "." + num_str.substr(1);

    return stod(special_str);
}

int main() {
    const double left = log10(get_special_float(TARGET));
    const double right = log10(get_special_float(TARGET + 1));
    const double coeff = log10(2);

    int count = 0;
    int i = 0;
    while (count != N) {
        double x = i * coeff;
        x = x - floor(x);
        if (left < x && x < right) {
            count++;
        }

        i++;
    }

    cout << i - 1 << endl;

    return 0;
}