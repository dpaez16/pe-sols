#include <bits/stdc++.h>

using namespace std;

#define N 100

int main() {
    int dp[N + 1];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;

    for (int smallerNum = 1; smallerNum < N; smallerNum++) {
        for (int num = smallerNum; num <= N; num++) {
            dp[num] += dp[num - smallerNum];
        }
    }

    cout << dp[N] << endl;
    return 0;
}