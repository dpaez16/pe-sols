#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;

#define N 4

int index_acc(int r, int c, int acc) {
    int idx = r * N + c;
    int val = (acc & (1 << idx));
    return val != 0 ? 1 : 0;
}

int find_neighbor(int r, int c, int dr, int dc, int acc) {
    if (dr == 0 && dc == 0) {
        return -1;
    }

    while (0 <= r && r < N && 0 <= c && c < N && index_acc(r, c, acc) == 1) {
        r += dr;
        c += dc;
    }

    if (0 <= r && r < N && 0 <= c && c < N) {
        return r * N + c;
    }

    return -1;
}

vector<int> construct_dc_vals(int dr_val) {
    vector<int> dc_vals;

    for (int dc = 1; dc < dr_val; dc++) {
        dc_vals.push_back(dc);
        dc_vals.push_back(-dc);
    }

    return dc_vals;
}

vector<int> get_neighbors(int digit, int acc) {
    int r = digit / N;
    int c = digit % N;

    vector<int> neighbors;

    // N = 2
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            int neighbor = find_neighbor(r, c, dr, dc, acc);
            if (neighbor != -1) {
                neighbors.push_back(neighbor);
            }
        }
    }

    // N >= 3
    for (int dr_val = 2; dr_val < N; dr_val++) {
        vector<int> dr_vals = {-dr_val, dr_val};
        for (auto dr : dr_vals) {
            auto dc_vals = construct_dc_vals(dr_val);

            for (auto dc : dc_vals) {
                int neighbor = find_neighbor(r, c, dr, dc, acc);
                if (neighbor != -1) {
                    neighbors.push_back(neighbor);
                }

                neighbor = find_neighbor(r, c, dc, dr, acc);
                if (neighbor != -1) {
                    neighbors.push_back(neighbor);
                }
            }
        }
    }

    return neighbors;
}

int main() {
    const int max_digit = N * N;
    const int max_acc = (1 << max_digit) - 1;
    ull ** dp = new ull * [max_digit];

    for (int i = 0; i < max_digit; i++) {
        dp[i] = new ull [max_acc + 1];
        for (int j = 0; j <= max_acc; j++) {
            dp[i][j] = 0;
        }
    }

    for (int acc = max_acc - 1; acc >= 0; acc--) {
        for (int digit = 0; digit < max_digit; digit++) {
            auto neighbors = get_neighbors(digit, acc);
            for (auto neighbor : neighbors) {
                dp[digit][acc] += 1 + dp[neighbor][acc | (1 << neighbor)];
            }
        }
    }

    ull ans = 0;
    for (int digit = 0; digit < max_digit; digit++) {
        ans += dp[digit][1 << digit];
    }

    cout << ans << endl;

    for (int i = 0; i < max_digit; i++) {
        delete [] dp[i];
    }

    delete [] dp;
    return 0;
}