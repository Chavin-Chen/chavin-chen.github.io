#include <algorithm>
#include <cstdio>
int dp[301][301], a[301];
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        a[n + i] = a[i];
    }
    for (int j = 1; j <= 2 * n; j++)
        for (int i = j - 1; i > 0 && j - i < n; i--)
            for (int k = i; k < j; k++)
                dp[i][j] = std::max(dp[i][j], dp[i][k] + dp[k + 1][j] + a[i] * a[k + 1] * a[j + 1]);
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = std::max(dp[i][i + n - 1], ans);
    printf("%d\n", ans);
    return 0;
}
/*
https://www.luogu.com.cn/problem/P1063
珠子i头标记为ai,m*r,r*n结合生成m*n的珠子,释放m*r*n的能量
input:
4
2 3 5 10
output:
710

*/
