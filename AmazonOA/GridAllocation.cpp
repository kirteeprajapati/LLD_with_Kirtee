#include <iostream>
#include <vector>
using namespace std;

const long long MOD = 998244353;

long long power(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

int findAllocationWays(int p1, int q1, int p2, int q2) {
    int r = p2 - p1;  // rows to add
    int c = q2 - q1;  // columns to add

    // Edge case: no operations needed
    if (r == 0 && c == 0) return 1;

    // dp[i][j] = number of distinct valid configurations
    // when adding i rows and j columns to p1 x q1 grid
    vector<vector<long long>> dp(r + 1, vector<long long>(c + 1, 0));

    // Base case: no rows/columns to add
    dp[0][0] = 1;

    // Base case: only rows to add (no new columns)
    // Each row can mark in any of q1 original columns independently
    for (int i = 1; i <= r; i++) {
        dp[i][0] = power(q1, i, MOD);
    }

    // Base case: only columns to add (no new rows)
    // Each column can mark in any of p1 original rows independently
    for (int j = 1; j <= c; j++) {
        dp[0][j] = power(p1, j, MOD);
    }

    // Fill DP table using inclusion-exclusion principle
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            // Term 1: configs where row i-1 can be added last
            long long term1 = dp[i-1][j] * ((q1 + j) % MOD) % MOD;

            // Term 2: configs where col j-1 can be added last
            long long term2 = dp[i][j-1] * ((p1 + i) % MOD) % MOD;

            // Term 3: configs counted twice (both can be added last)
            long long term3 = dp[i-1][j-1] * ((q1 + j - 1) % MOD) % MOD;
            term3 = term3 * ((p1 + i - 1) % MOD) % MOD;

            dp[i][j] = ((term1 + term2 - term3) % MOD + MOD) % MOD;
        }
    }

    return (int)dp[r][c];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int p1, q1, p2, q2;
    cin >> p1 >> q1 >> p2 >> q2;

    cout << findAllocationWays(p1, q1, p2, q2) << endl;

    return 0;
}
