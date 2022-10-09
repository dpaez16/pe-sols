#include <bits/stdc++.h>

using namespace std;

#define N powl(10, 12)

double get_quadratic_sol(double a, double b, double c) {
    return (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
}

double get_nb(double n) {
    return get_quadratic_sol(1, -1, -0.5 * n * (n - 1));
}

double a(int n) {
    if (n == 0) {
        return 1;
    }

    double a_n_m_2 = 1;
    double a_n_m_1 = 4;

    for (int i = 1; i <= n; i++) {
        double a_n = 6 * a_n_m_1 - a_n_m_2 - 2;
        a_n_m_2 = a_n_m_1;
        a_n_m_1 = a_n;
    }

    return a_n_m_1;
}

string format_ans(double & n) {
	string ans_str = to_string(n);
	size_t pos = ans_str.find('.');
	if (pos != ans_str.npos) ans_str = ans_str.substr(0, pos);

	return ans_str;
}

int main() {
    int i = 0;
    while (a(i) <= N) {
        i++;
    }

    double n = a(i);
    double nb = get_nb(n);
    cout << format_ans(nb) << endl;

    return 0;
}