#include <cstdio>
#define maxn 20
int dp[maxn][maxn];
int main(){
    int m,n,ans=0;
    scanf("%d%d",&m,&n);
    for(int i=0;i<=m;i++)
        dp[i][0]=1;
    for(int i=1;i<=m;i++)
        for(int j=1;j<=i;j++)
            dp[i][j] = dp[i-1][j] + dp[i][j-1];
    printf("%d\n",dp[m][n]);
    return 0;
}
/*
一列长度为m+n队伍买5元门票,其中m人持5元,n人持10元,初始无零钱,求能找开的排队数(持同样钱的人互换视为同一方案)
讨论: 设此m+n人的队伍合法
	如果最后一人为5元,则其前有m-1个5元,n个10元
	如果最后一人为10元,则前有m个5元,n-1个10元
dp[m][n] = dp[m-1][n] + dp[m][n-1];
dp[i][0] = 1; dp[m][m+i] = 0;
*/