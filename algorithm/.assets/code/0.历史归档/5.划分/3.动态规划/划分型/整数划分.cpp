#include<iostream>
#include<vector>

using namespace std;
/**
 * 将N分成最多M个数相加的和，相同数交换位置算同一种方案
 */
int dfs(int m, int n) {
    if (m == 1) return 1;
    if (n == 1) return 1;
    if (n < m) return dfs(n, n);
    if (m == n) return 1 + dfs(n - 1, n);
    return dfs(m, n - m) + dfs(m - 1, n);
}

int dp(int m, int n) {
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++)
        dp[1][i] = 1;
    for (int i = 1; i <= m; i++)
        dp[i][1] = dp[i][0] = 1;

    for (int i = 2; i <= m; i++) {
        for (int j = 2; j <= n; j++) {
            dp[i][j] = dp[i - 1][j] + (j >= i ? dp[i][j - i] : 0);
        }
    }
    return dp[m][n];
}

int main() {
    int m = 2, n = 4;
    cout << dfs(m, n) << endl;
    cout << dp(m, n) << endl;
    return 0;
}
