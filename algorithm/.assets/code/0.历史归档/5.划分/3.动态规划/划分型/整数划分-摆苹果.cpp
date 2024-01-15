/**
 * https://www.luogu.com.cn/problem/P1025
 * 给出n个苹果，要求放入m个盘子，不能有盘子为空。求有多少中摆放方案。
 * 注：交换盘子顺序不算新的摆放方案，即 [1,2,3]和[3,2,1]是同一种方案。
 */
#include <iostream>
#include <vector>

using namespace std;

int solve(int n, int m) {
    vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
    for (int i = 0; i <= n; i++) {
        dp[1][i] = 1;
    }

    for (int j = 0; j <= n; j++) {
        for (int i = 2; i <= n; i++) {
            if (j >= i) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - i];
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    return dp[m][n - m];
}

int main() {
    cout << solve(7, 3) << endl; // 4
    return 0;
}